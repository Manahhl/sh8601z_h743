#ifndef _QSPI_H_
#define _QSPI_H_

#include "stm32h7xx_hal.h"


// SPD2010   QSPI ʱ��˵��
// ����/����ָ��+��ַ+�����ֽ�+������+����
// ��ַ:0x00<<16|�Ĵ���ָ��<<8|0x00 
// QSPIʱ�� ����Һ��ʱ ����Ҫ�����ֽ� ������
// ����Һ��ʱ ����û������ ���ǲ���û�е�ַȴ��������

void QSPI_GPIOInit(void);
void QSPI_Init(void);



#endif





