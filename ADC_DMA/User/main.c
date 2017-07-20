/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   串口接发测试，串口接收到数据后马上回传。
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F429 开发板
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"	
#include "bsp_debug_adc.h"

extern  __IO uint16_t   ADC_ConvertedValue[RHEOSTAT_NOFCHANEL];

// 局部变量，用于保存转换计算后的电压值
float ADC_ConvertedfValueLocal[RHEOSTAT_NOFCHANEL]={0};

static void Delay(__IO uint32_t nCount)
{
 for(; nCount !=0; nCount--);
}	

int main(void)
{	
	
	
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  Debug_USART_Config();
	Rheostat_Init();
	
  while(1)
	{	
		  ADC_ConvertedfValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*(float)3.3; // 读取转换的AD值?
      ADC_ConvertedfValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*(float)3.3;
		  ADC_ConvertedfValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*(float)3.3;
		  printf("\r\n The current C3 value = %f V \r\n",ADC_ConvertedfValueLocal[0]);  
		  printf("\r\n The current A4 value = %f V \r\n",ADC_ConvertedfValueLocal[1]); 
		  printf("\r\n The current A6 value = %f V \r\n",ADC_ConvertedfValueLocal[2]); 
      
      Delay(0xffffee);		
		  		
	}	
}



/*********************************************END OF FILE**********************/

