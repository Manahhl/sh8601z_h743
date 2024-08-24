#ifndef _QSPI_H_
#define _QSPI_H_

#include "stm32h7xx_hal.h"


// SPD2010   QSPI 时序说明
// 单线/四线指令+地址+复用字节+空周期+数据
// 地址:0x00<<16|寄存器指令<<8|0x00 
// QSPI时序 驱动液晶时 不需要复用字节 空周期
// 驱动液晶时 可以没有数据 但是不能没有地址却发送数据

void QSPI_GPIOInit(void);
void QSPI_Init(void);



#endif





