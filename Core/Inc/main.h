#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif


#include "stm32h7xx_hal.h"
#include "stdio.h"
#include "lvgl.h"
#include "mpu.h"
#include "lcd.h"
#include "lcd_init.h"
#include "gpio.h"
#include "stdlib.h"
#include "iic.h"
#include "cst816d.h"
#include "rtthread.h"
#include "usart.h"
#include "tim.h"
#include "spi.h"
#include "w25qxx_spi.h"

#include "ff.h"
#include "ffconf.h"
#include "diskio.h"


extern void disp_enable_update(void);
extern void disp_disable_update(void);

extern void lv_demo_stress(void);
extern void lv_demo_music(void);

void SystemClock_Config(void); 
void CPU_CACHE_Enable(void); 
void Error_Handler(void);
void delay_us(__IO uint32_t delay);

 #define USE_TICK 0
///////////////////////////////////// 
 
#define SRAM_ITCM_BASE      (0x00000000)
#define SRAM_ITCM_SIZE      (1024 * 64U)

#define SRAM_DTCM_BASE      (0x20000000)
#define SRAM_DTCM_SIZE      (1024 * 128U)

#define SRAM_AXI_BASE       (0x24000000)        /* LCD FRAME BUFFER */
#define SRAM_AXI_SIZE       (1024 * 512U)

#define SRAM1_BASE          (0x30000000)        /* LVGL DISPLAY ROW BUFFER */
#define SRAM1_SIZE          (1024 * 128U)

#define SRAM2_BASE          (0x30020000)    
#define SRAM2_SIZE          (1024 * 128U)

#define SRAM3_BASE          (0x30040000)
#define SRAM3_SIZE          (1024 * 32U)

#define SRAM4_BASE          (0x38000000)
#define SRAM4_SIZE          (1024 * 64U)

#define SRAM_BKP_BASE       (0x38800000)
#define SRAM_BKP_SIZE       (1024 * 4U)
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
