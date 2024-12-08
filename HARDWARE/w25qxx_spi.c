#include "main.h"

#define delay(ms) HAL_Delay(ms-1)
#define get_tick() HAL_GetTick()

W25Qx_Parameter W25Qx_Para;
/**
  * @brief  Initializes the W25QXXXX interface.
  * @retval None
  */
uint8_t W25Qx_Init(void)
{ 
	uint8_t state;
	/* Reset W25Qxxx */
	W25Qx_Reset();
	delay(5);
	state = W25Qx_Get_Parameter(&W25Qx_Para);
	
	printf("state = %d\r\n",state);
	
	return state;
}

/**
  * @brief  This function reset the W25Qx.
  * @retval None
  */
static void	W25Qx_Reset(void)
{
	uint8_t cmd[2] = {RESET_ENABLE_CMD,RESET_MEMORY_CMD};
	
	W25Qx_Enable();
	/* Send the reset command */
	HAL_SPI_Transmit(&hspi1, cmd, 2, W25QXXXX_TIMEOUT_VALUE);	
	W25Qx_Disable();

}

/**
  * @brief  Reads current status of the W25QXXXX.
  * @retval W25QXXXX memory status
  */
static uint8_t W25Qx_GetStatus(void)
{
	uint8_t cmd[] = {READ_STATUS_REG1_CMD};
	uint8_t status;
	
	W25Qx_Enable();
	
	/* Send the read status command */
	HAL_SPI_Transmit(&hspi1, cmd, 1, W25QXXXX_TIMEOUT_VALUE);	
	/* Reception of the data */
	HAL_SPI_Receive(&hspi1,&status, 1, W25QXXXX_TIMEOUT_VALUE);
	W25Qx_Disable();
	
	/* Check the value of the register */
  if((status & W25QXXXX_FSR_BUSY) != 0)
  {
    return W25Qx_BUSY;
  }
	else
	{
		return W25Qx_OK;
	}		
}

/**
  * @brief  This function send a Write Enable and wait it is effective.
  * @retval None
  */
uint8_t W25Qx_WriteEnable(void)
{
	uint8_t cmd[] = {WRITE_ENABLE_CMD};
	uint32_t tickstart = get_tick();

	/*Select the FLASH: Chip Select low */
	W25Qx_Enable();
	/* Send the read ID command */
	HAL_SPI_Transmit(&hspi1, cmd, 1, W25QXXXX_TIMEOUT_VALUE);	
	/*Deselect the FLASH: Chip Select high */
	W25Qx_Disable();
	
	/* Wait the end of Flash writing */
	while(W25Qx_GetStatus() == W25Qx_BUSY)
	{
		/* Check for the Timeout */
    if((get_tick() - tickstart) > W25QXXXX_TIMEOUT_VALUE)
    {        
			return W25Qx_TIMEOUT;
    }
	  delay(1);
	}
	
	return W25Qx_OK;
}

/**
  * @brief  Read Manufacture/Device ID.
	* @param  return value address
/   ����ֵ����:        
/   0XEF13,��ʾоƬ�ͺ�ΪW25Q80   
/   0XEF14,��ʾоƬ�ͺ�ΪW25Q16     
/   0XEF15,��ʾоƬ�ͺ�ΪW25Q32   
/   0XEF16,��ʾоƬ�ͺ�ΪW25Q64  
  * @retval None
  */
uint16_t W25Qx_Read_ID()
{
	uint8_t idt[2];
	uint16_t rt_id;
	
	uint8_t cmd[4] = {READ_ID_CMD,0x00,0x00,0x00};
	
	W25Qx_Enable();
	/* Send the read ID command */
	HAL_SPI_Transmit(&hspi1, cmd, 4, W25QXXXX_TIMEOUT_VALUE);	
	/* Reception of the data */
	HAL_SPI_Receive(&hspi1,idt, 2, W25QXXXX_TIMEOUT_VALUE);
	
	 rt_id = (idt[0] << 8) + idt[1];
	
	return rt_id;
	W25Qx_Disable();
		
}

#include <math.h>
/**
  * @brief  Get W25QX Parameter.
  * @param  Para: W25Qx_Parameter
  * @retval NULL
  */

uint8_t W25Qx_Get_Parameter(W25Qx_Parameter *Para)
{
	uint16_t id;
	uint32_t size;
	
	Para->PAGE_SIZE = 256;
	Para->SUBSECTOR_SIZE = 4096;
	Para->SECTOR_SIZE = 0x10000;
	
	id = W25Qx_Read_ID();
	printf("id = 0x%x\r\n",id);
	if(id < W25Q80 || id > W25Q128) return W25Qx_ERROR;
	
	size = (uint32_t) powf(2,(id - 0xEF13)) * 1024 * 1024;
	
	Para->FLASH_Id = id;
	Para->FLASH_Size = size;
	Para->SUBSECTOR_COUNT = Para->FLASH_Size / Para->SUBSECTOR_SIZE;
	Para->SECTOR_COUNT = Para->FLASH_Size / Para->SECTOR_SIZE;
	
	return W25Qx_OK;
}
/**
  * @brief  Reads an amount of data from the QSPI memory.
  * @param  pData: Pointer to data to be read
  * @param  ReadAddr: Read start address
  * @param  Size: Size of data to read    
  * @retval QSPI memory status
  */
uint8_t W25Qx_Read(uint8_t* pData, uint32_t ReadAddr, uint32_t Size)
{
	uint8_t cmd[4];

	/* Configure the command */
	cmd[0] = READ_CMD;
	cmd[1] = (uint8_t)(ReadAddr >> 16);
	cmd[2] = (uint8_t)(ReadAddr >> 8);
	cmd[3] = (uint8_t)(ReadAddr);
	
	W25Qx_Enable();
	/* Send the read ID command */
	HAL_SPI_Transmit(&hspi1, cmd, 4, W25QXXXX_TIMEOUT_VALUE);	
	/* Reception of the data */
	if (HAL_SPI_Receive(&hspi1, pData,Size,W25QXXXX_TIMEOUT_VALUE) != HAL_OK)
  {
    return W25Qx_ERROR;
  }
	W25Qx_Disable();
	return W25Qx_OK;
}

/**
  * @brief  Writes an amount of data to the QSPI memory.
  * @param  pData: Pointer to data to be written
  * @param  WriteAddr: Write start address
  * @param  Size: Size of data to write,No more than 256byte.    
  * @retval QSPI memory status
  */
uint8_t W25Qx_Write(uint8_t* pData, uint32_t WriteAddr, uint32_t Size)
{
	uint8_t cmd[4];
	uint32_t end_addr, current_size, current_addr;
	uint32_t tickstart = get_tick();
	
	/* Calculation of the size between the write address and the end of the page */
  current_addr = 0;

  while (current_addr <= WriteAddr)
  {
    current_addr += W25QXXXX_PAGE_SIZE;
  }
  current_size = current_addr - WriteAddr;

  /* Check if the size of the data is less than the remaining place in the page */
  if (current_size > Size)
  {
    current_size = Size;
  }

  /* Initialize the adress variables */
  current_addr = WriteAddr;
  end_addr = WriteAddr + Size;
	
  /* Perform the write page by page */
  do
  {
		/* Configure the command */
		cmd[0] = PAGE_PROG_CMD;
		cmd[1] = (uint8_t)(current_addr >> 16);
		cmd[2] = (uint8_t)(current_addr >> 8);
		cmd[3] = (uint8_t)(current_addr);

		/* Enable write operations */
		W25Qx_WriteEnable();
	
		W25Qx_Enable();
    /* Send the command */
    if (HAL_SPI_Transmit(&hspi1,cmd, 4, W25QXXXX_TIMEOUT_VALUE) != HAL_OK)
    {
      return W25Qx_ERROR;
    }
    
    /* Transmission of the data */
    if (HAL_SPI_Transmit(&hspi1, pData,current_size, W25QXXXX_TIMEOUT_VALUE) != HAL_OK)
    {
      return W25Qx_ERROR;
    }
		W25Qx_Disable();
    	/* Wait the end of Flash writing */
		while(W25Qx_GetStatus() == W25Qx_BUSY)
		{
			/* Check for the Timeout */
			if((get_tick() - tickstart) > W25QXXXX_TIMEOUT_VALUE)
			{        
				return W25Qx_TIMEOUT;
			}
			//delay(1);
		}
    
    /* Update the address and size variables for next page programming */
    current_addr += current_size;
    pData += current_size;
    current_size = ((current_addr + W25QXXXX_PAGE_SIZE) > end_addr) ? (end_addr - current_addr) : W25QXXXX_PAGE_SIZE;
  } while (current_addr < end_addr);

	
	return W25Qx_OK;
}

/**
  * @brief  Erases the specified block of the QSPI memory. 
  * @param  BlockAddress: Block address to erase  
  * @retval QSPI memory status
  */
uint8_t W25Qx_Erase_Block(uint32_t Address)
{
	uint8_t cmd[4];
	uint32_t tickstart = get_tick();
	cmd[0] = SECTOR_ERASE_CMD;
	cmd[1] = (uint8_t)(Address >> 16);
	cmd[2] = (uint8_t)(Address >> 8);
	cmd[3] = (uint8_t)(Address);
	
	/* Enable write operations */
	W25Qx_WriteEnable();
	
	/*Select the FLASH: Chip Select low */
	W25Qx_Enable();
	/* Send the read ID command */
	HAL_SPI_Transmit(&hspi1, cmd, 4, W25QXXXX_TIMEOUT_VALUE);	
	/*Deselect the FLASH: Chip Select high */
	W25Qx_Disable();
	
	/* Wait the end of Flash writing */
	while(W25Qx_GetStatus() == W25Qx_BUSY)
	{
		/* Check for the Timeout */
    if((get_tick() - tickstart) > W25QXXXX_SECTOR_ERASE_MAX_TIME)
    {        
			return W25Qx_TIMEOUT;
    }
	  //delay(1);
	}
	return W25Qx_OK;
}

/**
  * @brief  Erases the entire QSPI memory.This function will take a very long time.
  * @retval QSPI memory status
  */
uint8_t W25Qx_Erase_Chip(void)
{
	uint8_t cmd[4];
	uint32_t tickstart = get_tick();
	cmd[0] = CHIP_ERASE_CMD;
	
	/* Enable write operations */
	W25Qx_WriteEnable();
	
	/*Select the FLASH: Chip Select low */
	W25Qx_Enable();
	/* Send the read ID command */
	HAL_SPI_Transmit(&hspi1, cmd, 1, W25QXXXX_TIMEOUT_VALUE);	
	/*Deselect the FLASH: Chip Select high */
	W25Qx_Disable();
	
	/* Wait the end of Flash writing */
	while(W25Qx_GetStatus() == W25Qx_BUSY)
	{
		/* Check for the Timeout */
    if((get_tick() - tickstart) > W25QXXXX_BULK_ERASE_MAX_TIME)
    {        
			return W25Qx_TIMEOUT;
    }
	  //delay(1);
	}
	return W25Qx_OK;
}
//////////////////////////////////////////////////////////////////////////
//flash 
//д��ӵ�ַ0��ʼд�룬���ú���W25Qx_Write
//���յ�ַд����д���ַ��ʼ��ȡ�����ú���W25Qx_Read
//
FATFS flash_fs;
BYTE work[FF_MAX_SS];
//�ļ����� ������̫���ˣ�ռ�ڴ棬�����malloc
FIL fnew;

//FATFS����
void FATFS_FLASH_Test(void)
{
    UINT fnum;//�ɹ���д����
    FRESULT res;//����ֵ
//	FIL *fnew;
//	fnew = (FIL *)malloc(sizeof(FIL));
	printf("fil fnew ��С = %d\r\n",sizeof(FIL));
	BYTE FATFS_Wr_Buff[50]  ={"hello,Ƕ��ʽ֪ʶ��Դ����RYMCU��ӭ�㣡ok"};// д������
	BYTE FATFS_Rd_Buff[50]  ={0};// ��������
	
    printf("rnrn------------------FLASH FATFS�ļ�ϵͳ����------------------rnrn\r\n");
    res = f_mount(&flash_fs,"3:/",1);
//    if(res == FR_NO_FILESYSTEM)
//    {
//        printf("FLASH��û�н����ļ�ϵͳ����ʼ��ʽ����rn\r\n");
//        res = f_mkfs("3:/",0,work,FF_MAX_SS);//��ʽ��
//        if(res == FR_OK)
//        {
//            printf("FLASH�ļ�ϵͳ��ʽ���ɹ���rn\r\n");
//            //��ʽ���ɹ�����ȡ���������¹��أ�
//            res = f_mount(NULL,"3:/",1);
//            printf("ȡ�����سɹ����� %drn\r\n",res);
//            res = f_mount(&flash_fs,"3:/",1);
//            printf("���¹��سɹ����� %drn\r\n",res);
//        }
//        else
//        {
//            printf("FLASH�ļ�ϵͳ��ʽ��ʧ�ܣ�rn\r\n");
//        }
//    }
    printf("rnrn-------------------FATFSϵͳ���ԣ�д�ļ�-------------------rn\r\n");
    //���ļ����ļ��������򴴽�����
    res = f_open(&fnew,"3:/RY.txt",FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
	printf("f_open res %d\r\n",res);
    if(res == FR_OK) printf("�򿪻򴴽�RY.txt�ɹ���rn\r\n");
    else             printf("�򿪻򴴽�RY.txtʧ�ܣ�rn\r\n");
    //д����
    res = f_write(&fnew,FATFS_Wr_Buff, sizeof(FATFS_Wr_Buff),&fnum);
    if(res == FR_OK) printf("��RY.txtд�����ݣ�rn%s\r\n",FATFS_Wr_Buff);
    else             printf("��RY.txtд������ʧ��,code: %d!rn\r\n",res);
    //���д�����󣬹ر��ļ�
    f_close(&fnew);
    printf("rn-------------------FATFSϵͳ���ԣ����ļ�-------------------rnrn\r\n");
    //���ļ�������ʽ���Ѵ������ļ�
    res = f_open(&fnew,"3:/RY.txt",FA_OPEN_EXISTING | FA_READ);
	printf("f_open res %d\r\n",res);
    if(res != FR_OK){printf("���ļ�ʧ�ܣ�rn\r\n");return;}
    //������
    res = f_read(&fnew,FATFS_Rd_Buff, sizeof(FATFS_Rd_Buff),&fnum);
	printf("f_open res %d\r\n",res);
    if(res != FR_OK){printf("��ȡ�ļ�ʧ�ܣ�rn\r\n");return;}
    printf("��ȡ�ļ����ݣ�rn %s rn\r\n",FATFS_Rd_Buff);
    f_close(&fnew);//��ȡ��ϣ��ر��ļ���
}



static void flash_test_func()
{   	
	SPI1_init();
	W25Qx_Init();
	rt_thread_delay(10);
	FATFS_FLASH_Test();
	printf("flash_test_func enter!\r\n");
	while(1)
	{
		rt_thread_delay(1000);
		
	}
}

static void spi_flash_test()
{
	rt_thread_t flash_test;	

	flash_test = rt_thread_create(
				"flash_test",
				flash_test_func,
				RT_NULL,
				2*1024,
				10,
				20);
	rt_thread_startup(flash_test);	
}

INIT_ENV_EXPORT(spi_flash_test)

