#ifndef  _ADC_H
#define  _ADC_H

#include   "stm32f4xx.h"

#define  RHEOSTAT_ADC             ADC1
#define  RHEOSTAT_ADC_CLK         RCC_APB2Periph_ADC1

#define  RHEOSTAT_NOFCHANEL       3

#define  RHEOSTAT_ADC_GPIO_PORT1   GPIOC
#define  RHEOSTAT_ADC_GPIO_PIN1    GPIO_Pin_3
#define  RHEOSTAT_ADC_GPIO_CLK1    RCC_AHB1Periph_GPIOC
#define  RHEOSTAT_ADC_Channel1     ADC_Channel_13

#define  RHEOSTAT_ADC_GPIO_PORT2   GPIOA
#define  RHEOSTAT_ADC_GPIO_PIN2    GPIO_Pin_4
#define  RHEOSTAT_ADC_GPIO_CLK2    RCC_AHB1Periph_GPIOA
#define  RHEOSTAT_ADC_Channel2     ADC_Channel_4

#define  RHEOSTAT_ADC_GPIO_PORT3   GPIOA
#define  RHEOSTAT_ADC_GPIO_PIN3    GPIO_Pin_6
#define  RHEOSTAT_ADC_GPIO_CLK3    RCC_AHB1Periph_GPIOA
#define  RHEOSTAT_ADC_Channel3     ADC_Channel_6




//*ADC DR¼Ä´æÆ÷ºê¶¨Òå ADC×ª»»ºóµÄÊý×ÖÖµ´æÅ*/
#define RHEOSTAT_ADC_DR_ADDR   ((u32)ADC1+0x4c)

/*ADC  DMAÍ¨µÀºê¶¨Òå*/
#define RHEOSTAT_ADC_DMA_CLK       RCC_AHB1Periph_DMA2
#define RHEOSTAT_ADC_DMA_CHANNEL   DMA_Channel_0
#define RHEOSTAT_ADC_DMA_STREAM    DMA2_Stream0

void Rheostat_Init(void);



#endif  /*  _ADC_H */
