#include "main.h"

#define BUFF_TOTAL 339488
#define panle_Y 412
#define panle_X 412
#define panel_X_DATA 412*2
#define panel_x_y 360*360

__attribute__((section (".RAM_D2"))) static uint16_t frame_cache[panel_x_y];

extern QSPI_HandleTypeDef QSPI_Handler;
extern QSPI_CommandTypeDef QSPI_CmdInitStructure;
extern MDMA_HandleTypeDef hmdma;


extern lv_disp_drv_t *disp_drv;
void HAL_QSPI_TxCpltCallback(QSPI_HandleTypeDef *hqspi)
{
	lv_disp_flush_ready(&disp_drv);
	//disp_enable_update();
}

//方式1
void LCD_Fill(uint16_t xs,uint16_t ys,uint16_t xe,uint16_t ye,lv_color_t *color)
{
	//disp_disable_update();
	uint32_t send_size = ((xe- xs+1) * (ye - ys+1) * sizeof(lv_color_t));
	LCD_Address_Set(xs,ys,xe,ye);
	LCD_WR_REG(0x2c);
	//SCB_CleanDCache_by_Addr((uint32_t *)0x24000000, 512*1024);
	//SCB_CleanDCache_by_Addr((uint32_t *)0x30000000, 288*1024);
	LCD_4LineTransmit_DATA_DMA(0x3c,send_size,(uint8_t *)color);
}

//void lcdqspi_draw_line(uint16_t x0, uint16_t x1, uint32_t y,uint16_t y0,uint16_t y1 ,uint16_t *pixel)
//{
//    if ((x1 < panle_X)&&(y < panle_Y)&&(x1 >= x0))
//    {
//        uint32_t  oft = x0 * 2;
//        uint16_t *dat = pixel;
//        for (uint32_t x = x0; x <= x1; x++)
//        {
//            frame_cache[y][oft + 1] = *dat & 0xff;
//            frame_cache[y][oft + 0] = (*dat & 0xff00) >> 8;
//            oft += 2;
//            dat++;
//        }
//    }
//}

//��ʽ2 
//void lcd_fill(uint16_t xs,uint16_t xe,uint16_t ys,uint16_t ye)
//{
//	disp_disable_update();
//	LCD_Address_Set(xs,ys,xe,ye);
//	LCD_WR_REG(0x2c); 
//	//SCB_CleanDCache_by_Addr((uint32_t *)0x24000000, 512*1024);
//	for(uint32_t i = 0;i<ye;i++ )
//	{
//		LCD_4LineTransmit_DATA_DMA(0x3c,panel_X_DATA,&frame_cache[i][0]);
//	} 
//	//lv_disp_flush_ready(&disp_drv);
//	//disp_enable_update();
//}

//void lcd_buf_fill(uint32_t x0, uint32_t x1, uint32_t y0, uint32_t y1,uint16_t *pixel)
//{
//	uint32_t width = x1- x0+1;
//	uint32_t height = y1-y0+1;
//	for(uint32_t y = 0;y<height;y++)
//	{
//		 for(uint32_t x=0;x<width;x++)
//		{
//			uint32_t arr_x = x0 + x;
//			uint32_t arr_y = y0 +y;
//			
//			frame_cache[arr_y][(arr_x*2) + 0] = *pixel & 0xff;
//			frame_cache[arr_y][(arr_x*2) + 1] = (*pixel & 0xff00) >> 8;
//			pixel++;
//		}
//	}
//}

//��ʽ3
 void lcd_buf_fill(uint32_t x0, uint32_t x1, uint32_t y0, uint32_t y1,uint16_t *pixel)
{
	uint32_t area_size ;
	uint32_t remain_size ;
	uint32_t index;
	
	//area_size  = ((x1 - x0 +1)*(y1 - y0 +1)*sizeof(uint16_t));
	area_size  = ((x1 - x0 +1)*(y1 - y0 +1));
	
	for(index = 0;index <= area_size;index++)
	{
		frame_cache[index] = *pixel;
		pixel++;
	}
	LCD_Address_Set(x0,y0,x1,y1);
	LCD_WR_REG(0x2c);
	//printf("area_size = %d\r\n",area_size);
	//SCB_CleanDCache_by_Addr((uint32_t *)0x24000000, 512*1024);
	LCD_4LineTransmit_DATA_DMA(0x3c,area_size*2,(uint8_t *)&frame_cache[0]); 

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//RT_Sem task test
static void lcd_buff_send()
{
	
	//LCD_Address_Set(0,0,360-1,360-1);
	LCD_WR_REG(0x2c);
	//printf("area_size = %d\r\n",area_size);
	//SCB_CleanDCache_by_Addr((uint32_t *)0x24000000, 512*1024);
	for(uint8_t i =0 ;i<(360*360)/(360*90);i++)
	{   
		delay_us(2);
		LCD_Address_Set(0,(i*90) - 1,359,((i+1)*90) - 1);
		//LCD_WR_REG(0x2c);
		LCD_4LineTransmit_DATA_DMA(0x3c,(360*90*2),(uint8_t *)&frame_cache[i*360*90]);
		//rt_thread_delay(1);
		
	}
	lv_disp_flush_ready(&disp_drv);
}


 
static void lcd_thread_entry(void* parameter)
{
    while (1)
    {   
		rt_kprintf("lcd test task1\r\n");
		//rt_sem_take(&frame_sem,RT_WAITING_FOREVER);
		lcd_buff_send();
		rt_kprintf("lcd test task\r\n");
        //rt_thread_delay(20);   /* 延时500个tick */
		//delay_us(100);
    }
}

static void lcd_send()
{ 
	//lcd 任务
	static rt_thread_t lcd_thread;
	lcd_thread = rt_thread_create(                    
            "lcd",                       /* 线程名字 */           
            lcd_thread_entry,            /* 线程入口函数 */     
            RT_NULL,                      /* 线程入口函数参数 */        
            256,						  /* 线程栈大小 */         
            21,                            /* 线程的优先级 */        
            20);
			
	rt_thread_startup(lcd_thread);
}

//INIT_APP_EXPORT(lcd_send)

