#include "stm32f4xx_conf.h"
#include "stm32f4xx.h"

/* Private function prototypes -----------------------------------------------*/
void ADC_DMA_Configuration(void);

/* Private variables ---------------------------------------------------------*/
extern __IO uint16_t ADC3ConvertedValue[2];

/* Funktionsprotoypen der alten ADC Funktionen */

// void ADC_Configuration(void);
// uint16_t adc_convert(void);
