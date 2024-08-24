#include "main.h"
extern I2C_HandleTypeDef hi2c2;

void I2C_Read(uint16_t address, uint8_t *data, uint16_t length)
{
    while(HAL_I2C_Mem_Read(&hi2c2, CST816D_I2C_READADDR,address, I2C_MEMADD_SIZE_8BIT,data, length,0xff) != HAL_OK); 
}
void I2C_Read_regs(uint16_t address, uint8_t *data, uint16_t length)
{
	HAL_I2C_Master_Transmit(&hi2c2,CST816D_I2C_WRITEADDR,0x02,1,0xff);
	while(HAL_I2C_Mem_Read(&hi2c2, CST816D_I2C_READADDR,address, I2C_MEMADD_SIZE_8BIT,data, length,0xff) != HAL_OK);
}

int lastx,lasty;
void cst816d_touch_read(void)
{
	uint8_t buf[5];
	
	
	I2C_Read_regs(0x02,&buf[0],5);
	
	lv_touch->x = buf[2] | ((buf[1] & 0xF) << 8);
	lv_touch->y = buf[4] | ((buf[3] & 0xF) << 8);
	lv_touch->statue = buf[0];
	
	lastx=lv_touch->x;
	lasty=lv_touch->y;
	
	
	printf("lastx = %d lasty = %d \r\n",lastx,lasty);
	
	if((lv_touch->x == 360) && (lv_touch->y == 360))
	{
		printf("%s\r\n",(buf[0] == 0?"pressed":"release"));
	}
}

static int CST816D_idcheck()
{
    uint8_t id_data[2];
    I2C_Read(0xA7, &id_data[0], 1);
    printf("id_data[0] = %02x", id_data[0]);
    return 0;
}


void cst816d_reset()
{
    cst816d_set();
    HAL_Delay(10);
    cst816d_clear();
    HAL_Delay(50);
	cst816d_set();
}

void cst816d_init(void)
{
    HAL_I2C_Init(&hi2c2);

    cst816d_reset();
    HAL_Delay(100);

    CST816D_idcheck();
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if((GPIO_Pin == GPIO_PIN_1))
	{   
	   cst816d_touch_read();
	}
 
}
void EXTI1_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}
