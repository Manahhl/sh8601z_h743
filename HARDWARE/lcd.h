
#ifndef _LCD_H_
#define _LCD_H_
#include "lvgl.h"
#include "lcd_init.h"
void LCD_Fill1(uint16_t xs,uint16_t ys,uint16_t xe,uint16_t ye,uint32_t color);
void LCD_Fill(uint16_t xs,uint16_t ys,uint16_t xe,uint16_t ye,lv_color_t *color);

//void lcdqspi_draw_line(uint32_t x0, uint32_t x1, uint32_t y0, uint32_t y1,uint16_t *pixel);
void lcdqspi_draw_line(uint16_t x0, uint16_t x1, uint32_t y,uint16_t y0,uint16_t y1 ,uint16_t *pixel);
void lcd_fill(uint16_t xs,uint16_t xe,uint16_t ys,uint16_t ye); 
void lcd_buf_fill(uint32_t x0, uint32_t x1, uint32_t y0, uint32_t y1,uint16_t *pixel);

void obj_add_anim();
void LCD_DRAW_LINE_DMA();
void lv_example_get_started_3(void);
void lv_example_style_2(void);
void lv_example_anim_2(void);
void lv_example_list_2(void);
void lvgl_scroll_test(void);
void lv_example_gif_11(void);

void lcdqspi_wait_te(void);

//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE           	 0x011F  
#define BRED             0XF81F
#define GRED 			       0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			     0XBC40 //��ɫ
#define BRRED 			     0XFC07 //�غ�ɫ
#define GRAY  			     0X8430 //��ɫ
#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			     0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ
#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)


#endif





