################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32L4xx_HAL_Driver/Src/Legacy/stm32l4xx_hal_can.c 

OBJS += \
./Drivers/STM32L4xx_HAL_Driver/Src/Legacy/stm32l4xx_hal_can.o 

C_DEPS += \
./Drivers/STM32L4xx_HAL_Driver/Src/Legacy/stm32l4xx_hal_can.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32L4xx_HAL_Driver/Src/Legacy/%.o Drivers/STM32L4xx_HAL_Driver/Src/Legacy/%.su Drivers/STM32L4xx_HAL_Driver/Src/Legacy/%.cyclo: ../Drivers/STM32L4xx_HAL_Driver/Src/Legacy/%.c Drivers/STM32L4xx_HAL_Driver/Src/Legacy/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Inc -I"C:/Users/Venkatesh J/Desktop/BS/Microcontrollers/STM32L476RG/Workspace/9_ADC_Interrupt/Drivers/CMSIS/Include" -I"C:/Users/Venkatesh J/Desktop/BS/Microcontrollers/STM32L476RG/Workspace/9_ADC_Interrupt/Drivers/CMSIS/Device/ST/STM32L4xx/Include" -I"C:/Users/Venkatesh J/Desktop/BS/Microcontrollers/STM32L476RG/Workspace/9_ADC_Interrupt/Drivers/STM32L4xx_HAL_Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-STM32L4xx_HAL_Driver-2f-Src-2f-Legacy

clean-Drivers-2f-STM32L4xx_HAL_Driver-2f-Src-2f-Legacy:
	-$(RM) ./Drivers/STM32L4xx_HAL_Driver/Src/Legacy/stm32l4xx_hal_can.cyclo ./Drivers/STM32L4xx_HAL_Driver/Src/Legacy/stm32l4xx_hal_can.d ./Drivers/STM32L4xx_HAL_Driver/Src/Legacy/stm32l4xx_hal_can.o ./Drivers/STM32L4xx_HAL_Driver/Src/Legacy/stm32l4xx_hal_can.su

.PHONY: clean-Drivers-2f-STM32L4xx_HAL_Driver-2f-Src-2f-Legacy

