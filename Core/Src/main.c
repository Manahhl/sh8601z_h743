//QSPI_CLK   PB2
//QSPI_DATA0 PD11
//QSPI_DATA1 PD12
//QSPI_DATA2 PE2
//QSPI_DATA3 PD13
//LCD_RES    PC1   
//QSPI_NCS   PB6

/* SRAM MAP
ITCM  0x00000000~0x0000FFFF(0x10000, 64K) - 紧密耦合内存 - CPU直接访问(指令) - 速度400MHZ
DTCM  0x20000000~0x2001FFFF(0x20000,128K) - 紧密耦合内存 - CPU直接访问(数据) - 速度400MHZ

D1域, 带宽是64bit, AXI总线, D3域中的BDMA主控不能访问, 其它都可以访问此RAM区 - 速度200MHZ
SRAMA 0x24000000~0x2407FFFF(0x80000,512K) - 用途不限，可以用于用户应用数据存储或者LCD显存

D2域, 带宽是32bit, AHB总线, D3域中的BDMA主控不能访问这三块SRAM, 其它都可以访问这几个RAM区 - 速度200MHZ
SRAM1 0x30000000~0x3001FFFF(0x20000,128K) - 用途不限，可用于D2域中的DMA缓冲，也可以当D1域断电后用于运行程序代码
SRAM2 0x30020000~0x3003FFFF(0x20000,128K) - 用途不限，可用于D2域中的DMA缓冲，也可以用于用户数据存取
SRAM3 0x30040000~0x30047FFF(0x08000, 32K) - 用途不限，主要用于以太网和USB的缓冲

D3域, 带宽是32bit，AHB总线, 大部分主控都能访这块SRAM区。
SRAM4 0x38000000~0x3800FFFF(0x10000, 64K) - 用途不限，可以用于D3域中的DMA缓冲，也可以当D1和D2域进入DStandby待机方式后，继续保存用户数据

备份RAM区, D3域, 带宽是32bit, AHB总线, 大部分主控都能访问这块SRAM区
SRAMB 0x38800000~0x38800FFF(0x01000,  4K) - 用途不限，主要用于系统进入低功耗模式后，继续保存数据（Vbat引脚外接电池）

DTCM和ITCM不支持DMA1，DMA2和BDMA，仅支持MDMA
AXI SRAM，SRAM1，SRAM2，SRAM3不支持BDMA，支持MDMA，DMA1和DMA2。
SRAM4支持所有DMA，即MDMA，DMA1，DMA2和BDMA

DTCM是400MHz的，而其它的RAM都是200MHz，推荐工程的主RAM空间采用TCM，而其它需要大RAM或者DMA的场合，使用剩余RAM空间
*/

#include "main.h"

/*******************************线程控制块定义**************************/


static void led1_thread_entry(void* parameter)
{
    while (1)
    {
		  printf("led test task\r\n");
      rt_thread_delay(1000);   /* 延时500个tick */
		  HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_3);
    }
}

int main(void)
{   
	//led 移植测试
	rt_thread_t led1_thread; 
	led1_thread = rt_thread_create(                    
            "led1",                       /* 线程名字 */           
            led1_thread_entry,            /* 线程入口函数 */     
            RT_NULL,                      /* 线程入口函数参数 */        
            128, 						  /* 线程栈大小 */         
            31,                            /* 线程的优先级 */        
            20);
			
	rt_thread_startup(led1_thread);
}


#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
