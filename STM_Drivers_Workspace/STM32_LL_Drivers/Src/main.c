#include "gpio_driver.h"
#include <stdio.h>


void delay(uint32_t n)
{
	uint32_t i,j;
	for(i=0; i<n;i++)
		for(j=0;j<1000;j++);
}

int main(void)
{
	GPIO_Handle_t pGPIOLed,pGPIOBtn;
	GPIO_Deinit(GPIOA);

	GPIO_PclkControl(GPIOA, ENABLE);
	GPIO_PclkControl(GPIOC, ENABLE);

	pGPIOLed.pGPIOx = GPIOA;
	pGPIOLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	pGPIOLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	pGPIOLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	pGPIOLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	pGPIOLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&pGPIOLed);

	pGPIOBtn.pGPIOx = GPIOC;
	pGPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	pGPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FE;
	pGPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	pGPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&pGPIOBtn);

	//GPIO_WritetoOutputPin(GPIOC, GPIO_PIN_NO_13, SET);

	//IRQ Configuration
	GPIO_IRQConfig(EXTI15_10_IRQn, 5, ENABLE);
	//GPIO_IRQPriorityConfig(EXTI15_10_IRQn, 5);
	//GPIO_IRQInterruptConfig(EXTI15_10_IRQn, ENABLE);

	while(1);

}

void EXTI15_10_IRQHandler(void)
{
	GPIO_IRQHandler(GPIO_PIN_NO_13);
	delay(100);
	GPIO_TogglePin(GPIOA, GPIO_PIN_NO_5);
}
