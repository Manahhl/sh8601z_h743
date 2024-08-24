
#include "main.h"
#include "mpu.h"

typedef struct
{
    uint32_t BaseAddress;
    uint32_t Size;
    uint32_t AccessPermission;
    uint32_t IsCacheable;
    uint32_t IsBufferable;
    uint32_t IsShareable;
    uint32_t DisableExec;
} _mpu_cfg_t;

const _mpu_cfg_t mpu_config[] = {
	//DTCM 共128k，指令允许，禁止公用，允许cache，允许缓冲
    {0x20000000, 
     MPU_REGION_SIZE_128KB,
     MPU_REGION_FULL_ACCESS,
     MPU_ACCESS_CACHEABLE,
     MPU_ACCESS_BUFFERABLE,
     MPU_ACCESS_NOT_SHAREABLE,
     MPU_INSTRUCTION_ACCESS_ENABLE},
	 //保护整个AXI SRAM,共512K字节,允许指令访问,禁止共用,允许cache,允许缓冲
    {0x24000000,
     MPU_REGION_SIZE_512KB,
     MPU_REGION_FULL_ACCESS,
     MPU_ACCESS_CACHEABLE,
     MPU_ACCESS_BUFFERABLE,
     MPU_ACCESS_NOT_SHAREABLE,
     MPU_INSTRUCTION_ACCESS_ENABLE},
	 //保护整个SRAM1~SRAM3,共288K字节,允许指令访问,禁止共用,允许cache,允许缓冲
    {0x30000000, 
     MPU_REGION_SIZE_128KB,
     MPU_REGION_FULL_ACCESS,
     MPU_ACCESS_CACHEABLE,
     MPU_ACCESS_BUFFERABLE,
     MPU_ACCESS_NOT_SHAREABLE,
     MPU_INSTRUCTION_ACCESS_ENABLE},
	 {0x30020000, 
     MPU_REGION_SIZE_128KB,
     MPU_REGION_FULL_ACCESS,
     MPU_ACCESS_CACHEABLE,
     MPU_ACCESS_BUFFERABLE,
     MPU_ACCESS_NOT_SHAREABLE,
     MPU_INSTRUCTION_ACCESS_ENABLE},
	 {0x30040000, 
     MPU_REGION_SIZE_32KB,
     MPU_REGION_FULL_ACCESS,
     MPU_ACCESS_CACHEABLE,
     MPU_ACCESS_BUFFERABLE,
     MPU_ACCESS_NOT_SHAREABLE,
     MPU_INSTRUCTION_ACCESS_ENABLE},
	 //保护整个SRAM4,共64K字节,允许指令访问,禁止共用,允许cache,允许缓冲
    {0x38000000, 
     MPU_REGION_SIZE_64KB,
     MPU_REGION_FULL_ACCESS,
     MPU_ACCESS_CACHEABLE,
     MPU_ACCESS_BUFFERABLE,
     MPU_ACCESS_NOT_SHAREABLE,
     MPU_INSTRUCTION_ACCESS_ENABLE},

};

void mpu_init(void)
{
	MPU_Region_InitTypeDef MPU_Initure;
    
    for (uint8_t i = 0; i < sizeof(mpu_config)/sizeof(_mpu_cfg_t); i++)
    {
        HAL_MPU_Disable();                                      //配置MPU之前先关闭MPU,配置完成以后在使能MPU
        
        _mpu_cfg_t *cfg = (_mpu_cfg_t *)&mpu_config[i];
        
        MPU_Initure.Enable           = MPU_REGION_ENABLE;       //使能该保护区域 
        MPU_Initure.Number           = MPU_REGION_NUMBER0 + i;  //设置保护区域
        MPU_Initure.BaseAddress      = cfg->BaseAddress;        //设置基址
        MPU_Initure.Size             = cfg->Size;               //设置保护区域大小
        MPU_Initure.SubRegionDisable = 0X00;                    //禁止子区域
        MPU_Initure.TypeExtField     = MPU_TEX_LEVEL0;          //设置类型扩展域为level0
        MPU_Initure.AccessPermission = cfg->AccessPermission;   //设置访问权限,
        MPU_Initure.IsCacheable      = cfg->IsCacheable;        //是否cache?     
        MPU_Initure.IsBufferable     = cfg->IsBufferable;       //是否缓冲?
        MPU_Initure.IsShareable      = cfg->IsShareable;        //是否共用?
        MPU_Initure.DisableExec      = cfg->DisableExec;        //允许指令访问(允许读取指令)
        HAL_MPU_ConfigRegion(&MPU_Initure);                     //配置MPU
        
        HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);                 //开启MPU
    }	
}
