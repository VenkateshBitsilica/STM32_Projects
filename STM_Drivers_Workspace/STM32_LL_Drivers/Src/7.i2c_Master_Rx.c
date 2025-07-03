
#include "i2c_driver.h"
#include <string.h>

/*
 * PB8	-->		I2C1_SCL
 * PB9  -->		I2C1_SDA
 * SCL_CLK	-->	100kHz
 */

I2C_Handle_t i2c1;
#define SLAVE_ADDR	0x68

void delay(uint32_t n)
{
	uint32_t i,j;
	for(i=0; i<n;i++)
		for(j=0;j<1000;j++);
}

void I2C_GPIOInits(void)
{

	GPIO_PclkControl(GPIOB, ENABLE);

	GPIO_Handle_t I2CPins;

	I2CPins.pGPIOx = GPIOB;
	I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_AFN;
	I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
	I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//I2C_CLK
	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
	GPIO_Init(&I2CPins);

	//I2C_SDA
	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
	GPIO_Init(&I2CPins);
}

void i2c1_init(void)
{
	i2c1.pI2Cx = I2C1;
	i2c1.I2C_config.I2C_DeviceAddress = 0x60;

	I2C_Init(&i2c1);
}

void btn_init(void)
{
	GPIO_Handle_t pGPIOBtn;

	GPIO_PclkControl(GPIOC, ENABLE);


	pGPIOBtn.pGPIOx = GPIOC;
	pGPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	pGPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	pGPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	pGPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&pGPIOBtn);
}

uint8_t buffer[32];
uint8_t command;
uint8_t len;

int main(void)
{

    I2C_GPIOInits();
    i2c1_init();
    btn_init();

    while(1)
    {
    	//Waits until button is pressed
    	while(GPIO_ReadInputPin(GPIOC, GPIO_PIN_NO_13) == SET);

    	delay(100);
    	command = 0x51;
    	I2C_MasterSendData(i2c1.pI2Cx, &command, 1, SLAVE_ADDR);

    	I2C_MasterReceiveData(i2c1.pI2Cx, &len, 1, SLAVE_ADDR);

    	command = 0x52;
    	I2C_MasterSendData(i2c1.pI2Cx, &command, 1, SLAVE_ADDR);

    	I2C_MasterReceiveData(i2c1.pI2Cx, buffer, len, SLAVE_ADDR);

    }

}





