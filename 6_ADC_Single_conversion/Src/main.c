#include "stm32l4xx_hal.h"
#include "adc.h"

ADC_HandleTypeDef hadc1;

uint32_t adc_val;
int main()
{
	HAL_Init();
	adc_SC_init();
	while(1)
	{
		//1.Start ADC
		HAL_ADC_Start(&hadc1);
		//2. Poll for conversion
		HAL_ADC_PollForConversion(&hadc1, 1);
		//3. Get Conversion
		adc_val = adc_read();
	}
}


void SysTick_Handler(void)
{
	HAL_IncTick();
}
