#include "ADC_Get.h"

/* Private define ------------------------------------------------------------*/
#define ADC3_DR_ADDRESS     ((uint32_t)0x4001224C)
#define ADC_CCR_ADDRESS    ((uint32_t)0x40012308)
#define ADC1_DR_ADDRESS    ((uint32_t)0x4001204C)

	
void ADC_Get_Configuration(void)
	{		
		ADC_InitTypeDef       ADC_InitStructure;
		ADC_CommonInitTypeDef ADC_CommonInitStructure;
		DMA_InitTypeDef       DMA_InitStructure;
		GPIO_InitTypeDef      GPIO_InitStructure;

		/* Enable ADC1, DMA2 and GPIO clocks ****************************************/
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

		/* DMA2 Stream0 channel0 configuration **************************************/
		DMA_InitStructure.DMA_Channel = DMA_Channel_0;  
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_ADDRESS;
		DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADCConvertedValue;
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
		DMA_InitStructure.DMA_BufferSize = 8;
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
		DMA_InitStructure.DMA_Priority = DMA_Priority_High;
		DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
		DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
		DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
		DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
		DMA_Init(DMA2_Stream0, &DMA_InitStructure);
		DMA_Cmd(DMA2_Stream0, ENABLE);
		
		/* Configure ADC1 Channel3 - Channel6 pin as analog input ******************************/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		/* Configure ADC1 Channel8 & Channel9 pin as analog input ******************************/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		/* Configure ADC1 Channel14 &Channel15 pin as analog input ******************************/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
		GPIO_Init(GPIOC, &GPIO_InitStructure);

		/* ADC Common Init **********************************************************/
		ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
		ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
		ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
		ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
		ADC_CommonInit(&ADC_CommonInitStructure);

		/* ADC1 Init ****************************************************************/
		ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
		ADC_InitStructure.ADC_ScanConvMode = ENABLE;
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
		ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_InitStructure.ADC_NbrOfConversion = 8;
		ADC_Init(ADC1, &ADC_InitStructure);

		/* ADC1 regular channel configuration *************************************/
		ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_3Cycles);
		ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 2, ADC_SampleTime_3Cycles);
		ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 3, ADC_SampleTime_3Cycles);
		ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 4, ADC_SampleTime_3Cycles);
		ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 5, ADC_SampleTime_3Cycles);
		ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 6, ADC_SampleTime_3Cycles);
		ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 7, ADC_SampleTime_3Cycles);
		ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 8, ADC_SampleTime_3Cycles);

	 /* Enable DMA request after last transfer (Single-ADC mode) */
		ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

		/* Enable ADC3 DMA */
		ADC_DMACmd(ADC1, ENABLE);

		/* Enable ADC3 */
		ADC_Cmd(ADC1, ENABLE);
				
	}

	
	/*  Backup der Funktionierenden ADC DMA Funktion mit 2 Channeln */
// 		ADC_InitTypeDef       ADC_InitStructure;
// 		ADC_CommonInitTypeDef ADC_CommonInitStructure;
// 		DMA_InitTypeDef       DMA_InitStructure;
// 		GPIO_InitTypeDef      GPIO_InitStructure;

// 		/* Enable ADC3, DMA2 and GPIO clocks ****************************************/
// 		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOC, ENABLE);
// 		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

// 		/* DMA2 Stream0 channel0 configuration **************************************/
// 		DMA_InitStructure.DMA_Channel = DMA_Channel_2;  
// 		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC3_DR_ADDRESS;
// 		DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADC3ConvertedValue;
// 		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
// 		DMA_InitStructure.DMA_BufferSize = 2;
// 		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
// 		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
// 		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
// 		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
// 		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
// 		DMA_InitStructure.DMA_Priority = DMA_Priority_High;
// 		DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
// 		DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
// 		DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
// 		DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
// 		DMA_Init(DMA2_Stream0, &DMA_InitStructure);
// 		DMA_Cmd(DMA2_Stream0, ENABLE);

// 		/* Configure ADC3 Channel12 pin as analog input ******************************/
// 		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
// 		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
// 		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
// 		GPIO_Init(GPIOC, &GPIO_InitStructure);

// 		/* ADC Common Init **********************************************************/
// 		ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
// 		ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
// 		ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
// 		ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
// 		ADC_CommonInit(&ADC_CommonInitStructure);

// 		/* ADC3 Init ****************************************************************/
// 		ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
// 		ADC_InitStructure.ADC_ScanConvMode = ENABLE;
// 		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
// 		ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
// 		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
// 		ADC_InitStructure.ADC_NbrOfConversion = 2;
// 		ADC_Init(ADC3, &ADC_InitStructure);

// 		/* ADC3 regular channel12 configuration *************************************/
// 		ADC_RegularChannelConfig(ADC3, ADC_Channel_11, 1, ADC_SampleTime_3Cycles);
// 		ADC_RegularChannelConfig(ADC3, ADC_Channel_12, 2, ADC_SampleTime_3Cycles);

// 	 /* Enable DMA request after last transfer (Single-ADC mode) */
// 		ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);

// 		/* Enable ADC3 DMA */
// 		ADC_DMACmd(ADC3, ENABLE);

// 		/* Enable ADC3 */
// 		ADC_Cmd(ADC3, ENABLE);
	
	
	
	
	
	
	/* Die zwei nachfolgenden Funktionen sind zum ADC auslesen ohne DMA und Funktionieren*/
// 	
// 	
// uint16_t adc_convert(){
//  ADC_SoftwareStartConv(ADC1);//Start the conversion
//  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));//Processing the conversion
//  return ADC_GetConversionValue(ADC1); //Return the converted data
// }

// void ADC_Configuration(void)
// { 
// 	ADC_InitTypeDef       ADC_InitStructure;
//  // ADC_CommonInitTypeDef ADC_CommonInitStructure;
// 	
//  ADC_DeInit();
//  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//data converted will be shifted to right
//  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//Input voltage is converted into a 12bit number giving a maximum value of 4096
//  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; //the conversion is continuous, the input data is converted more than once
//  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;// conversion is synchronous with TIM1 and CC1 (actually I'm not sure about this one :/)
//  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//no trigger for conversion
//  ADC_InitStructure.ADC_NbrOfConversion = 1;//I think this one is clear :p
//  ADC_InitStructure.ADC_ScanConvMode = DISABLE;//The scan is configured in one channel
//  ADC_Init(ADC1,&ADC_InitStructure);//Initialize ADC with the previous configuration
//  //Enable ADC conversion
//  ADC_Cmd(ADC1,ENABLE);
//  //Select the channel to be read from
//  ADC_RegularChannelConfig(ADC1,ADC_Channel_11,1,ADC_SampleTime_144Cycles);	
// 		
// 	}
