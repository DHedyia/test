/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ���ڽӷ����ԣ����ڽ��յ����ݺ����ϻش���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F429 ������
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"	
#include "bsp_debug_adc.h"

extern  __IO uint16_t   ADC_ConvertedValue[RHEOSTAT_NOFCHANEL];

// �ֲ����������ڱ���ת�������ĵ�ѹֵ
float ADC_ConvertedfValueLocal[RHEOSTAT_NOFCHANEL]={0};

static void Delay(__IO uint32_t nCount)
{
 for(; nCount !=0; nCount--);
}	

int main(void)
{	
	
	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  Debug_USART_Config();
	Rheostat_Init();
	
  while(1)
	{	
		  ADC_ConvertedfValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*(float)3.3; // ��ȡת����ADֵ?
      ADC_ConvertedfValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*(float)3.3;
		  ADC_ConvertedfValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*(float)3.3;
		  printf("\r\n The current C3 value = %f V \r\n",ADC_ConvertedfValueLocal[0]);  
		  printf("\r\n The current A4 value = %f V \r\n",ADC_ConvertedfValueLocal[1]); 
		  printf("\r\n The current A6 value = %f V \r\n",ADC_ConvertedfValueLocal[2]); 
      
      Delay(0xffffee);		
		  		
	}	
}



/*********************************************END OF FILE**********************/

