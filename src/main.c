#include "stm32f4xx_conf.h"
#include "stm32f4_discovery.h"
#include "ADC.h"

/* Private define ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
 void GPIO_Configuration(void);
 void RCC_Configuration(void);
 
  /* Private variables ---------------------------------------------------------*/
 __IO uint16_t ADC3ConvertedValue[2];

 
int main(void)
{
		RCC_Configuration();
		GPIO_Configuration();
		ADC_DMA_Configuration();
		//ADC_Configuration();
	
		//STM_EVAL_LEDOnLed anschalen
		//STM_EVAL_LEDOff Led ausschalten
		
		STM_EVAL_LEDOn(LED3);
		STM_EVAL_LEDOn(LED4);
		STM_EVAL_LEDOn(LED5);
		STM_EVAL_LEDOn(LED6);
	
	
			/* Start ADC3 Software Conversion */ 
		ADC_SoftwareStartConv(ADC3);

     while(1)
     {

      ADC3ConvertedValue[0];
			ADC3ConvertedValue[1];
    }
}
/*Pheriperal Clock Configuration*/ 
void RCC_Configuration(void)
{
  /* Enable peripheral clocks ------------------------------------------------*/
  /* Enable ADC1 and GPIOA, GPIOD & GPIOD clock */
 // RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

}

/* GPIO Configuration*/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure PA.00 & PA03  (ADC Channel0 & Channel3) as analog input -------------------------*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	  /* Configure PC.00  (ADC Channel10) as analog input -------------------------*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 
	GPIO_Init(GPIOC,&GPIO_InitStructure);
 
  /* Configure PD12, 13, 14 and PD15 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}
