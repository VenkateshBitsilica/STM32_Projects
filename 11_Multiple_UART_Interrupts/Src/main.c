
#include "stm32l4xx_hal.h"
#include "stm32l4xx.h"
#include <stdio.h>

#define LED_PIN		GPIO_PIN_5
#define LED_PORT	GPIOA

/*UART1 is connected on APB2 bus
 * PA9 = USART2_TX
 * PA10 = USART2_RX
 */
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;


uint8_t tx_buffer1[10] = {1,2,3,4,5,6,7,8,9,10};
uint8_t rx_buffer1[10];

uint8_t tx_buffer2[10] = {1,2,3,4,5,6,7,8,9,10};
uint8_t rx_buffer2[10];

uint32_t rx_count1,rx_count2;
uint32_t tx_count1,tx_count2;

void uart1_init(void);
void uart2_init(void);
void led_init(void);
void Error_Handler(void);

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		tx_count1++;
	}
	if(huart->Instance == USART2)
	{
		tx_count2++;
	}


}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		rx_count1++;
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		HAL_UART_Receive_IT(&huart1, rx_buffer1, 10);
	}
	if(huart->Instance == USART2)
	{
		rx_count1++;

		HAL_UART_Receive_IT(&huart2, rx_buffer2, 10);
	}

}

int main()
{
	HAL_Init();
	uart1_init();
	uart2_init();
	led_init();

	HAL_UART_Transmit_IT(&huart1, tx_buffer1, 10);
	HAL_UART_Receive_IT(&huart1, rx_buffer1, 10);

	HAL_UART_Transmit_IT(&huart2, tx_buffer2, 10);
	while(1)
	{
		//tx_count++;
		HAL_UART_Transmit_IT(&huart1, tx_buffer1, 10);
		HAL_Delay(1000);
		HAL_UART_Transmit_IT(&huart2, tx_buffer2, 10);
		HAL_Delay(1000);
	}
}

void uart1_init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	//Enable clock for UART pins
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//Enable UART module clock access
	__HAL_RCC_USART1_CLK_ENABLE();

	//Configure GPIO pins as alternate functionality pins for UART2
	GPIO_InitStruct.Pin   = GPIO_PIN_9 | GPIO_PIN_10;
	GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  huart1.Instance = USART1;
	  huart1.Init.BaudRate = 115200;
	  huart1.Init.WordLength = UART_WORDLENGTH_8B;
	  huart1.Init.StopBits = UART_STOPBITS_1;
	  huart1.Init.Parity = UART_PARITY_NONE;
	  huart1.Init.Mode = UART_MODE_TX_RX;
	  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	  if (HAL_UART_Init(&huart1) != HAL_OK)
	  {
	    Error_Handler();
	  }

	  HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
	  HAL_NVIC_EnableIRQ(USART1_IRQn);

}

void uart2_init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	//Enable clock for UART pins
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//Enable UART module clock access
	__HAL_RCC_USART2_CLK_ENABLE();

	//Configure GPIO pins as alternate functionality pins for UART2
	GPIO_InitStruct.Pin   = GPIO_PIN_2 | GPIO_PIN_3;
	GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  huart2.Instance = USART2;
	  huart2.Init.BaudRate = 115200;
	  huart2.Init.WordLength = UART_WORDLENGTH_8B;
	  huart2.Init.StopBits = UART_STOPBITS_1;
	  huart2.Init.Parity = UART_PARITY_NONE;
	  huart2.Init.Mode = UART_MODE_TX_RX;
	  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	  if (HAL_UART_Init(&huart2) != HAL_OK)
	  {
	    Error_Handler();
	  }

	  HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
	  HAL_NVIC_EnableIRQ(USART2_IRQn);

}
void led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	//1. Configure PA5 as GPIO output for LED
	//Enable Clock
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitStruct.Pin = LED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);
}
void USART1_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart1);
}

void USART2_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart2);
}

void SysTick_Handler(void)
{
	HAL_IncTick();
}
void Error_Handler(void)
{

}


