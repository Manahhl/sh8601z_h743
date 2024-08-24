#ifndef __CST816D_H
#define __CST816D_H
#include "main.h"

typedef struct point
{
	uint8_t statue;
	uint32_t x;
	uint32_t y;
}_point;
extern _point *lv_touch;

#define cst816d_set() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
#define cst816d_clear() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);

#define CST816D_I2C_ADDR 0x15
#define CST816D_I2C_READADDR 0x2B
#define CST816D_I2C_WRITEADDR 0x2A

void cst816d_init(void);

#endif /* __CST816D_H */












