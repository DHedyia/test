#include  "bsp_debug_adc.h"


__IO uint16_t   ADC_ConvertedValue[RHEOSTAT_NOFCHANEL]={0};


static  void   Rheostat_ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_GPIO_CLK1, ENABLE);
	GPIO_InitStructure.GPIO_Mode     =   GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_PuPd     =   GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin      =   GPIO_Pin_3;
	GPIO_Init(RHEOSTAT_ADC_GPIO_PORT1, &GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_GPIO_CLK2, ENABLE);
	GPIO_InitStructure.GPIO_Mode     =   GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_PuPd     =   GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin      =   GPIO_Pin_4;
	GPIO_Init(RHEOSTAT_ADC_GPIO_PORT2, &GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_GPIO_CLK3, ENABLE);
	GPIO_InitStructure.GPIO_Mode     =   GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_PuPd     =   GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin      =   GPIO_Pin_6;
	GPIO_Init(RHEOSTAT_ADC_GPIO_PORT3, &GPIO_InitStructure);
}


static  void  Rheostat_ADC_Mode_Config(void)
{
	ADC_InitTypeDef           ADC_InitStructure;
	ADC_CommonInitTypeDef     ADC_CommonInitStructure;
	DMA_InitTypeDef           DMA_InitStructure;
	
	/*DMA Init结构体 参数 初始化*/
	RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_DMA_CLK, ENABLE);
	DMA_InitStructure.DMA_PeripheralBaseAddr = RHEOSTAT_ADC_DR_ADDR;
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)&ADC_ConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = RHEOSTAT_NOFCHANEL;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	 
	DMA_InitStructure.DMA_Channel =  RHEOSTAT_ADC_DMA_CHANNEL;
	DMA_Init(RHEOSTAT_ADC_DMA_STREAM, &DMA_InitStructure);
	DMA_Cmd(RHEOSTAT_ADC_DMA_STREAM, ENABLE);
	
	
  RCC_APB2PeriphClockCmd(RHEOSTAT_ADC_CLK, ENABLE);
	
	          /*ADC_CommonInitTypeDef结构体初始化*/
	ADC_CommonInitStructure.ADC_DMAAccessMode     =  ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_Mode              =  ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler         =  ADC_Prescaler_Div4;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay  =  ADC_TwoSamplingDelay_20Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);
	
               /*ADC_Init结构体初始化*/
	ADC_InitStructure.ADC_ContinuousConvMode       = ENABLE;
	ADC_InitStructure.ADC_Resolution               = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode             = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge     = ADC_ExternalTrigConvEdge_None;
//	ADC_InitStructure.ADC_ExternalTrigConv         = 
	ADC_InitStructure.ADC_DataAlign                = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion          = RHEOSTAT_NOFCHANEL;
	
	ADC_Init(RHEOSTAT_ADC, &ADC_InitStructure);
	
	// 配置 ADC 通道转换顺序为1，第一个转换，采样时间为3个时钟周期
	ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_Channel1, 1, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_Channel2, 2, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_Channel3, 3, ADC_SampleTime_3Cycles);
	
	// 使能DMA请求 after last transfer （Single-ADC mode）
	ADC_DMARequestAfterLastTransferCmd(RHEOSTAT_ADC, ENABLE);
	ADC_DMACmd(RHEOSTAT_ADC, ENABLE);

	// 使能ADC
	ADC_Cmd(RHEOSTAT_ADC ,ENABLE);
	
	//开始ADC转换，软件触发?
	ADC_SoftwareStartConv(RHEOSTAT_ADC );
	
}

//static void Rheostat_ADC_NVIC_Config(void)
//{
//	NVIC_InitTypeDef   NVIC_InitStructure;
//	NVIC_PriorityGroupConfig (NVIC_PriorityGroup_1);
//	NVIC_InitStructure.NVIC_IRQChannel = RHEOSTAT_ADC_IRQ;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//	
//}

void Rheostat_Init(void)
{
	Rheostat_ADC_GPIO_Config();
	Rheostat_ADC_Mode_Config();
//	Rheostat_ADC_NVIC_Config();
}
	
	
