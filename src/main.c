#include "stm32f4xx_conf.h"
#include "stm32f4_discovery.h"
#include <math.h>
/* Selbstgeschriebene Header */
#include "ADC_Get.h"
#include "PWM_Set.h"
#include "PWM_Get.h"
#include "Can.h"
#include "Led_I2C_Set.h"
#include "Motor_Speed_Get.h"

/* Private define ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint16_t ADCConvertedValue[8];
// __IO uint16_t DutyCycle1;
// __IO uint16_t DutyCycle2;
// __IO uint32_t Frequency1;
// __IO uint32_t Frequency2;

 
int main(void)
{
		Discovery_Led_Set_Configuration();
		ADC_Get_Configuration();
		PWM_Set_Configuration();
		PWM_Get_Configuration();
	
		/* Start ADC3 Software Conversion */ 
		ADC_SoftwareStartConv(ADC1);
	
		//STM_EVAL_LEDOnLed anschalen
		//STM_EVAL_LEDOff Led ausschalten
		
		STM_EVAL_LEDOn(LED3);
		STM_EVAL_LEDOn(LED4);
		STM_EVAL_LEDOn(LED5);
		STM_EVAL_LEDOn(LED6);
	
		PWM_Set_CH1_ms(1);
     while(1)
     {		
		//	ADCConvertedValue[1];
    }
}

