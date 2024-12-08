#include "main.h"

extern QSPI_HandleTypeDef QSPI_Handler;
extern QSPI_CommandTypeDef QSPI_CmdInitStructure;
extern MDMA_HandleTypeDef hmdma;

//初始化结构体
typedef struct {
    uint8_t cmd;
    uint8_t data[16];
    uint8_t databytes;
} lcd_init_cmd_t;

 lcd_init_cmd_t SPD2010_init_cmds[]={
	 {0xc0,{0x5a,0x5a},2},
	 {0xc1,{0x5a,0x5a},2},
	 
	 {0x11,{100},0x80},
	 
	 {0x3a,{0x55},1},
	 {0x44,{0x00,0x00},2},
	 //{0x35,{0x00},1},
	 {0x36,{0x00},1},
	 {0xb0,{0x16},1},
	 {0xb1,{0x01,0x05,0x00,0xa2,0x00,0xa7,0x00,0xa7,0x00},9},
	 {0x53,{0x28},1},
	 {0xc4,{0x80},1},
	 
	 {0x29,{100},0x80},
	 
	 {0xb1,{0xc0},1},
	 
	 {0xc0,{0xa5,0xa5},2},
	 {0xc1,{0xa5,0xa5},2},
	 
	 {0,{0},0xFF},	
	};	 

//????д???????
void LCD_WR_REG(uint8_t reg)
{
	QSPI_CmdInitStructure.DummyCycles=0;
	QSPI_CmdInitStructure.Instruction=0x02;
	QSPI_CmdInitStructure.InstructionMode=QSPI_INSTRUCTION_1_LINE;
	QSPI_CmdInitStructure.Address=reg<<8;		
	QSPI_CmdInitStructure.AddressMode=QSPI_ADDRESS_1_LINE;
	QSPI_CmdInitStructure.AddressSize=QSPI_ADDRESS_24_BITS;
	
	QSPI_CmdInitStructure.DataMode=QSPI_DATA_NONE;
	QSPI_CmdInitStructure.NbData=0;
	
	QSPI_CmdInitStructure.SIOOMode=QSPI_SIOO_INST_EVERY_CMD;
	QSPI_CmdInitStructure.DdrMode=QSPI_DDR_MODE_DISABLE;
	QSPI_CmdInitStructure.DdrHoldHalfCycle=QSPI_DDR_HHC_ANALOG_DELAY;	
	QSPI_CmdInitStructure.AlternateBytesSize=QSPI_ALTERNATE_BYTES_NONE;	
	HAL_QSPI_Command(&QSPI_Handler,&QSPI_CmdInitStructure,HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}

//????д?????????????е?????????????????
void LCD_Transmit_Byte(uint8_t reg,uint8_t dat)
{
	QSPI_CmdInitStructure.DummyCycles=0;
	QSPI_CmdInitStructure.Instruction=0x02;
	QSPI_CmdInitStructure.InstructionMode=QSPI_INSTRUCTION_1_LINE;
	
	QSPI_CmdInitStructure.Address=reg<<8;		
	QSPI_CmdInitStructure.AddressMode=QSPI_ADDRESS_1_LINE;
	QSPI_CmdInitStructure.AddressSize=QSPI_ADDRESS_24_BITS;
	
	QSPI_CmdInitStructure.DataMode=QSPI_DATA_1_LINE;
	QSPI_CmdInitStructure.NbData=1;
	QSPI_CmdInitStructure.SIOOMode=QSPI_SIOO_INST_EVERY_CMD;
	QSPI_CmdInitStructure.DdrMode=QSPI_DDR_MODE_DISABLE;
	QSPI_CmdInitStructure.DdrHoldHalfCycle=QSPI_DDR_HHC_ANALOG_DELAY;	
	QSPI_CmdInitStructure.AlternateBytesSize=QSPI_ALTERNATE_BYTES_NONE;	
	HAL_QSPI_Command(&QSPI_Handler,&QSPI_CmdInitStructure,HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
	HAL_QSPI_Transmit(&QSPI_Handler,&dat,HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
}

void LCD_Transmit_DATA(uint8_t reg,uint32_t len,uint8_t *dat)
{
	QSPI_CmdInitStructure.DummyCycles=0;
	QSPI_CmdInitStructure.Instruction=0x02;
	QSPI_CmdInitStructure.InstructionMode=QSPI_INSTRUCTION_1_LINE;
	
	QSPI_CmdInitStructure.Address=reg<<8;		
	QSPI_CmdInitStructure.AddressMode=QSPI_ADDRESS_1_LINE;
	QSPI_CmdInitStructure.AddressSize=QSPI_ADDRESS_24_BITS;
	
	QSPI_CmdInitStructure.DataMode=QSPI_DATA_1_LINE;
	QSPI_CmdInitStructure.NbData=len;
	QSPI_CmdInitStructure.SIOOMode=QSPI_SIOO_INST_EVERY_CMD;
	QSPI_CmdInitStructure.DdrMode=QSPI_DDR_MODE_DISABLE;
	QSPI_CmdInitStructure.DdrHoldHalfCycle=QSPI_DDR_HHC_ANALOG_DELAY;	
	QSPI_CmdInitStructure.AlternateBytesSize=QSPI_ALTERNATE_BYTES_NONE;	
	HAL_QSPI_Command(&QSPI_Handler,&QSPI_CmdInitStructure,HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
	HAL_QSPI_Transmit(&QSPI_Handler,dat,HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
}

void LCD_4LineTransmit_Byte(uint8_t reg,uint8_t dat)
{
	QSPI_CmdInitStructure.DummyCycles=0;
	QSPI_CmdInitStructure.Instruction=0x32;
	QSPI_CmdInitStructure.InstructionMode=QSPI_INSTRUCTION_1_LINE;
	
	QSPI_CmdInitStructure.Address=reg<<8;		
	QSPI_CmdInitStructure.AddressMode=QSPI_ADDRESS_1_LINE;
	QSPI_CmdInitStructure.AddressSize=QSPI_ADDRESS_24_BITS;
	
	QSPI_CmdInitStructure.DataMode=QSPI_DATA_4_LINES;
	QSPI_CmdInitStructure.NbData=1;
	QSPI_CmdInitStructure.SIOOMode=QSPI_SIOO_INST_EVERY_CMD;
	QSPI_CmdInitStructure.DdrMode=QSPI_DDR_MODE_DISABLE;
	QSPI_CmdInitStructure.DdrHoldHalfCycle=QSPI_DDR_HHC_ANALOG_DELAY;	
	QSPI_CmdInitStructure.AlternateBytesSize=QSPI_ALTERNATE_BYTES_NONE;	
	HAL_QSPI_Command(&QSPI_Handler,&QSPI_CmdInitStructure,HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
	HAL_QSPI_Transmit(&QSPI_Handler,&dat,HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
	
}

void LCD_4LineTransmit_DATA(uint8_t reg,uint32_t len,uint8_t *dat)
{
	
	QSPI_CmdInitStructure.Instruction=0x02;
	QSPI_CmdInitStructure.InstructionMode=QSPI_INSTRUCTION_1_LINE;	
	QSPI_CmdInitStructure.Address=reg<<8;		
	QSPI_CmdInitStructure.AddressMode=QSPI_ADDRESS_1_LINE;	
	QSPI_CmdInitStructure.DataMode=QSPI_DATA_1_LINE;
	QSPI_CmdInitStructure.NbData=len;

	HAL_QSPI_Command(&QSPI_Handler,&QSPI_CmdInitStructure,HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
	HAL_QSPI_Transmit(&QSPI_Handler,dat,HAL_QSPI_TIMEOUT_DEFAULT_VALUE);	
}

void LCD_4LineTransmit_DATA_DMA(uint8_t reg,uint32_t len,uint8_t *dat)
{
	QSPI_CmdInitStructure.Instruction=0x32;
	QSPI_CmdInitStructure.InstructionMode=QSPI_INSTRUCTION_1_LINE;	
	QSPI_CmdInitStructure.Address=reg<<8;		
	QSPI_CmdInitStructure.AddressMode=QSPI_ADDRESS_1_LINE;	
	QSPI_CmdInitStructure.DataMode=QSPI_DATA_4_LINES;
	QSPI_CmdInitStructure.NbData=len;
	
	HAL_QSPI_Command(&QSPI_Handler,&QSPI_CmdInitStructure,HAL_QPSI_TIMEOUT_DEFAULT_VALUE);	
	while(HAL_QSPI_Transmit_DMA(&QSPI_Handler,dat) == HAL_OK);
}

void LCD_Address_Set(uint16_t xs,uint16_t ys,uint16_t xe,uint16_t ye)
{
	uint8_t DATAX[4]={xs>>8,xs&0xff,xe>>8,xe&0xff};
	uint8_t DATAY[4]={ys>>8,ys&0xff,ye>>8,ye&0xff};
	LCD_4LineTransmit_DATA(0x2A,4,DATAX);
	LCD_4LineTransmit_DATA(0x2B,4,DATAY);

}

void LCD_Init(void)
{
	uint16_t cmd=0;
	LCD_RES_Set();
	HAL_Delay(10);
	LCD_RES_Clr();
	HAL_Delay(100);
	LCD_RES_Set();
	HAL_Delay(120);
    while(SPD2010_init_cmds[cmd].databytes!=0xff)
	{
		if(SPD2010_init_cmds[cmd].databytes&0x80)
		{
			LCD_WR_REG(SPD2010_init_cmds[cmd].cmd);
			HAL_Delay(120);
		}
		else
		{
			LCD_4LineTransmit_DATA(SPD2010_init_cmds[cmd].cmd,
											SPD2010_init_cmds[cmd].databytes&0x1F,
											SPD2010_init_cmds[cmd].data);
		}		
		cmd++;
	}
}

