
#ifndef ADC_H_
#define ADC_H_
#include "stm32l4xx_hal.h"

void adc_start(void);
uint32_t adc_read(void);
void adc_CC_init();


#endif /* ADC_H_ */
