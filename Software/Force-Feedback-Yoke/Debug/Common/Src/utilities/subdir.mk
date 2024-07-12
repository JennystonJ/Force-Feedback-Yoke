################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Common/Src/utilities/utilities.c 

C_DEPS += \
./Common/Src/utilities/utilities.d 

OBJS += \
./Common/Src/utilities/utilities.o 


# Each subdirectory must supply rules for building sources it contributes
Common/Src/utilities/%.o Common/Src/utilities/%.su Common/Src/utilities/%.cyclo: ../Common/Src/utilities/%.c Common/Src/utilities/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -I../Common/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Common-2f-Src-2f-utilities

clean-Common-2f-Src-2f-utilities:
	-$(RM) ./Common/Src/utilities/utilities.cyclo ./Common/Src/utilities/utilities.d ./Common/Src/utilities/utilities.o ./Common/Src/utilities/utilities.su

.PHONY: clean-Common-2f-Src-2f-utilities

