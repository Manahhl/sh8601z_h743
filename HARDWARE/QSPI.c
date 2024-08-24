#include "QSPI.h"
#include "main.h"


QSPI_HandleTypeDef QSPI_Handler;
QSPI_CommandTypeDef QSPI_CmdInitStructure;
MDMA_HandleTypeDef hmdma;


void QSPI_GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE(); 
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
  
	GPIO_InitStructure.Pin=GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13;
	GPIO_InitStructure.Mode=GPIO_MODE_AF_PP;
	GPIO_InitStructure.Pull=GPIO_PULLUP;
	GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStructure.Alternate=GPIO_AF9_QUADSPI;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIO_PIN_2;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Pull =GPIO_PULLUP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStructure.Alternate = GPIO_AF9_QUADSPI;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = GPIO_PIN_6;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStructure.Alternate = GPIO_AF10_QUADSPI;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	GPIO_InitStructure.Pin = GPIO_PIN_2;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStructure.Alternate = GPIO_AF9_QUADSPI;
	HAL_GPIO_Init(GPIOE,&GPIO_InitStructure);
}

void QSPI_Init(void)
{
	__HAL_RCC_QSPI_CLK_ENABLE();
	
	__HAL_RCC_QSPI_FORCE_RESET();
	__HAL_RCC_QSPI_RELEASE_RESET();
	
	QSPI_Handler.Instance=QUADSPI;
	QSPI_Handler.Init.ChipSelectHighTime=QSPI_CS_HIGH_TIME_1_CYCLE; //片选为高延时
	QSPI_Handler.Init.ClockMode=QSPI_CLOCK_MODE_3;					//配置时钟模式
	QSPI_Handler.Init.ClockPrescaler=8-1;								//配置时钟分频比
	QSPI_Handler.Init.DualFlash=QSPI_DUALFLASH_DISABLE;				//配置双闪存模式状态
	QSPI_Handler.Init.FifoThreshold=32;								//配置FIFO中字节阈值（仅在间接模式使用）
	QSPI_Handler.Init.FlashID=QSPI_FLASH_ID_1;						//配置使用的闪存
	QSPI_Handler.Init.FlashSize=20;									//配置闪存大小
	QSPI_Handler.Init.SampleShifting=QSPI_SAMPLE_SHIFTING_NONE; 	//配置采样移位
	HAL_QSPI_Init(&QSPI_Handler);
	
	QSPI_CmdInitStructure.Instruction = 0x32;
	QSPI_CmdInitStructure.Address     = 0x000000;
	QSPI_CmdInitStructure.DummyCycles = 0;
	QSPI_CmdInitStructure.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	QSPI_CmdInitStructure.AddressMode  = QSPI_ADDRESS_1_LINE;
	QSPI_CmdInitStructure.AddressSize  = QSPI_ADDRESS_24_BITS;
	QSPI_CmdInitStructure.DataMode     = QSPI_DATA_NONE;
	QSPI_CmdInitStructure.NbData       = 0;
	QSPI_CmdInitStructure.SIOOMode     = QSPI_SIOO_INST_EVERY_CMD;
	QSPI_CmdInitStructure.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	QSPI_CmdInitStructure.DdrMode      = QSPI_DDR_MODE_DISABLE;
	QSPI_CmdInitStructure.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	
	HAL_NVIC_SetPriority(QUADSPI_IRQn, 0x0f, 0);
	HAL_NVIC_EnableIRQ(QUADSPI_IRQn);
	
	__HAL_RCC_MDMA_CLK_ENABLE();

	#define MDMA_HALFWORD 1 
	#if MDMA_HALFWORD
	hmdma.Instance = MDMA_Channel0;
	hmdma.Init.Request = MDMA_REQUEST_QUADSPI_FIFO_TH;
	hmdma.Init.TransferTriggerMode = MDMA_BUFFER_TRANSFER;
	hmdma.Init.Priority =  MDMA_PRIORITY_HIGH;
	hmdma.Init.Endianness =  MDMA_LITTLE_HALFWORD_ENDIANNESS_EXCHANGE;
	hmdma.Init.SourceInc = MDMA_SRC_INC_HALFWORD;
	hmdma.Init.DestinationInc =  MDMA_DEST_INC_HALFWORD;
	hmdma.Init.SourceDataSize =  MDMA_SRC_DATASIZE_HALFWORD;
	hmdma.Init.DestDataSize = MDMA_DEST_DATASIZE_HALFWORD;
	hmdma.Init.DataAlignment = MDMA_DATAALIGN_PACKENABLE;
	hmdma.Init.BufferTransferLength = 32;
	hmdma.Init.SourceBurst = MDMA_SOURCE_BURST_16BEATS;
	hmdma.Init.DestBurst = MDMA_DEST_BURST_16BEATS;
	hmdma.Init.SourceBlockAddressOffset = 0;
	hmdma.Init.DestBlockAddressOffset = 0;
	#else
	hmdma.Instance = MDMA_Channel0;
	hmdma.Init.Request = MDMA_REQUEST_QUADSPI_FIFO_TH;
	hmdma.Init.TransferTriggerMode = MDMA_BUFFER_TRANSFER;
	hmdma.Init.Priority =  MDMA_PRIORITY_HIGH;
	hmdma.Init.Endianness =  MDMA_LITTLE_BYTE_ENDIANNESS_EXCHANGE;
	hmdma.Init.SourceInc = MDMA_SRC_INC_BYTE;
	hmdma.Init.DestinationInc =  MDMA_DEST_INC_BYTE;
	hmdma.Init.SourceDataSize =  MDMA_SRC_DATASIZE_BYTE;
	hmdma.Init.DestDataSize = MDMA_DEST_INC_BYTE;
	hmdma.Init.DataAlignment = MDMA_DATAALIGN_PACKENABLE;
	hmdma.Init.BufferTransferLength = 128;
	hmdma.Init.SourceBurst = MDMA_SOURCE_BURST_SINGLE;
	hmdma.Init.DestBurst = MDMA_DEST_BURST_SINGLE;
	hmdma.Init.SourceBlockAddressOffset = 0;
	hmdma.Init.DestBlockAddressOffset = 0;
	#endif

    HAL_MDMA_DeInit(&hmdma);  
	HAL_MDMA_Init(&hmdma);
	
	__HAL_LINKDMA(&QSPI_Handler,hmdma,hmdma);

	HAL_NVIC_SetPriority(MDMA_IRQn,0x02,0);
	HAL_NVIC_EnableIRQ(MDMA_IRQn);
}

 void HAL_QSPI_MspDeInit(QSPI_HandleTypeDef* qspiHandle)
{

  if(qspiHandle->Instance==QUADSPI)
  {
    /* Peripheral clock disable */
    __HAL_RCC_QSPI_CLK_DISABLE();

    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_2);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_2|GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13);
	  
	 /* 复位QSPI */
	__HAL_RCC_QSPI_FORCE_RESET();
	__HAL_RCC_QSPI_RELEASE_RESET();

    /* QUADSPI MDMA DeInit */
    HAL_MDMA_DeInit(qspiHandle->hmdma);

    /* QUADSPI interrupt Deinit */
    HAL_NVIC_DisableIRQ(QUADSPI_IRQn);
	  
	/* MDMA interrupt Deinit */
    HAL_NVIC_DisableIRQ(MDMA_IRQn);
  }
}



