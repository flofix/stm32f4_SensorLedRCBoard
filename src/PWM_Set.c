#include "PWM_Set.h"

#define TimFreq 3000000    // Timer über Prescaler runtergetaktet. Wert wurde ausgewählt um eine hohe Auflösung zu erreichen. Maximale Auflöse 16 Bit
#define PWMFreq 50.0      // PWM Frequenz
#define CntPeriod (1/PWMFreq)*TimFreq  //60000


uint16_t CCR1_Val = 4500; //enspricht einer Pulsbreite von 1,5ms
uint16_t PrescalerValue = 27.5; //stellt den Duty Cycle auf 50 Hz

void PWM_Set_Configuration(void){
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

  /* TIM5 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

  /* GPIOA clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  
  /* GPIOB Configuration:  TIM5 CH1 (PA0) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 

  /* Connect TIM3 pins to AF2 */  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
	
	/* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = CntPeriod; // Setzten des Counters
  TIM_TimeBaseStructure.TIM_Prescaler = (uint16_t) ((SystemCoreClock / TimFreq) - 1)/2;//Heruntertakten des Timers auf 50 Hz 
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TIM5, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(TIM5, ENABLE);

  /* TIM5 enable counter */
  TIM_Cmd(TIM5, ENABLE);
}


void PWM_Set_CH1_ms(float ms)
{

	TIM5->CCR1=(uint32_t)(CntPeriod*PWMFreq/1000)*ms;  //(60000*50/1000)*1.5

}


	/* Funktion zum erzeugen von PWM Signalen über 4 Channel mit dem Timer 4*/


// uint16_t CCR1_Val = 4500;//333;
// uint16_t CCR2_Val = 6000;//249;
// uint16_t CCR3_Val = 30000;//166;
// uint16_t CCR4_Val = 60000;//83;
// uint16_t PrescalerValue = 27.5;//0;
// void PWM_Configuration(void){
// 	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
// 	TIM_OCInitTypeDef  TIM_OCInitStructure;
// 	GPIO_InitTypeDef GPIO_InitStructure;

//   /* TIM3 clock enable */
//   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

//   /* GPIOC and GPIOB clock enable */
//   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
//   
//   /* GPIOB Configuration:  TIM3 CH3 (PB0) and TIM3 CH4 (PB1) */
//   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
//   GPIO_Init(GPIOB, &GPIO_InitStructure); 

//   /* Connect TIM3 pins to AF2 */  
//   GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
//   GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4); 
//   GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM4);
//   GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_TIM4); 
// 	
// 	
// 	  /* Compute the prescaler value */
//   //PrescalerValue = (uint16_t) ((SystemCoreClock /2) / 28000000) - 1;

//   /* Time base configuration */
//   TIM_TimeBaseStructure.TIM_Period = CntPeriod;//665;
//   TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
//   TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

//   TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

//   /* PWM1 Mode configuration: Channel1 */
//   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//   TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
//   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

//   TIM_OC1Init(TIM4, &TIM_OCInitStructure);

//   TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

//   /* PWM1 Mode configuration: Channel2 */
//   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//   TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

//   TIM_OC2Init(TIM4, &TIM_OCInitStructure);

//   TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

//   /* PWM1 Mode configuration: Channel3 */
//   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//   TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

//   TIM_OC3Init(TIM4, &TIM_OCInitStructure);

//   TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

//   /* PWM1 Mode configuration: Channel4 */
//   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//   TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

//   TIM_OC4Init(TIM4, &TIM_OCInitStructure);

//   TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

//   TIM_ARRPreloadConfig(TIM4, ENABLE);

//   /* TIM3 enable counter */
//   TIM_Cmd(TIM4, ENABLE);

// }
