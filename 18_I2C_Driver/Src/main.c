#include "stm32l4xx_hal.h"

I2C_HandleTypeDef hi2c1;

void i2c_init(void);

int main()
{
	HAL_Init();

	while(1)
	{

	}
}
void i2c_init(void)
{
	/*
	 * PB8	-->	I2C_SCL
	 * PB9	--> I2C_SDA
	*/

	//Enable clock for GPIOB and I2C
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_I2C1_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	//Configure I2C
	hi2c1.Instance = I2C1;
	hi2c1.Init.Timing = 0x00B1112E; 	//For 400kHz fast mode
	hi2c1.Init.OwnAddress1 =0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	HAL_I2C_Init(&hi2c1);

}

void SysTick_Handler(void)
{
	HAL_IncTick();
}



