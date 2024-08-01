################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/peripherals/gpio.c 

OBJS += \
./Core/Src/peripherals/gpio.o 

C_DEPS += \
./Core/Src/peripherals/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/peripherals/%.o Core/Src/peripherals/%.su Core/Src/peripherals/%.cyclo: ../Core/Src/peripherals/%.c Core/Src/peripherals/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -I../Common/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-peripherals

clean-Core-2f-Src-2f-peripherals:
	-$(RM) ./Core/Src/peripherals/gpio.cyclo ./Core/Src/peripherals/gpio.d ./Core/Src/peripherals/gpio.o ./Core/Src/peripherals/gpio.su

.PHONY: clean-Core-2f-Src-2f-peripherals

