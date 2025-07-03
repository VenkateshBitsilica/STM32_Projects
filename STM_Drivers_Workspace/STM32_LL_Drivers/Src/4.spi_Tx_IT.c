
#include "spi_driver.h"
#include <string.h>

/*
 * PB14 --> SPI2_MISO
 * PB15 --> SPI2_MOSI
 * PB13 -> SPI2_SCLK
 * PB12 --> SPI2_NSS
 * ALT function mode : 5
 */

#include "spi_driver.h"
#include <string.h>

SPI_Handle_t SPI2handle;

uint8_t tx_data[] = {10,20,30,40,50,60,70,80,90,100};
uint8_t rx_data[10];

// Actual definition
uint8_t spi_tx_done = 0;
uint8_t spi_rx_done = 0;



void SPI2_GPIOInits(void)
{

	GPIO_PclkControl(GPIOB, ENABLE);

	GPIO_Handle_t SPIPins;

	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_AFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);

	//MISO
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GPIO_Init(&SPIPins);


	//NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPIPins);


}

void SPI2_Inits(void)
{
	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8;
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_DI;

	SPI_Init(&SPI2handle);
}


int main(void)
{
    SPI2_GPIOInits();
    SPI2_Inits();
    SPI_SSOEConfig(SPI2, ENABLE);

    //SPI_SSIConfig(SPI2, ENABLE);

    // Configure NVIC
    SPI_IRQConfig(SPI2_IRQn, 1, ENABLE);

    // Enable SPI peripheral
    SPI_PeripheralControl(SPI2, ENABLE);

    // Start Transmission
    SPI_SendData_IT(&SPI2handle, tx_data, 10);

    // Wait for TX to complete
    while(!spi_tx_done);

    // Start Reception (if needed after TX)
    SPI_ReceiveData_IT(&SPI2handle, rx_data, 10);

    // Wait for RX to complete
    while(!spi_rx_done);

    // Confirm SPI is not busy
    while(SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG));

    // Disable SPI
    SPI_PeripheralControl(SPI2, DISABLE);

    while(1);
}

void SPI2_IRQHandler(void)
{
	SPI_IRQHandling(&SPI2handle);
}



