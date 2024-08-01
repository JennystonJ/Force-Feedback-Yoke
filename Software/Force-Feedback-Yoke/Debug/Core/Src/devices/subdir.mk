################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/devices/as5600.c \
../Core/Src/devices/as5600_interface.c \
../Core/Src/devices/bts7960.c \
../Core/Src/devices/bts7960_interface.c \
../Core/Src/devices/home_sensor.c \
../Core/Src/devices/ina219.c 

OBJS += \
./Core/Src/devices/as5600.o \
./Core/Src/devices/as5600_interface.o \
./Core/Src/devices/bts7960.o \
./Core/Src/devices/bts7960_interface.o \
./Core/Src/devices/home_sensor.o \
./Core/Src/devices/ina219.o 

C_DEPS += \
./Core/Src/devices/as5600.d \
./Core/Src/devices/as5600_interface.d \
./Core/Src/devices/bts7960.d \
./Core/Src/devices/bts7960_interface.d \
./Core/Src/devices/home_sensor.d \
./Core/Src/devices/ina219.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/devices/%.o Core/Src/devices/%.su Core/Src/devices/%.cyclo: ../Core/Src/devices/%.c Core/Src/devices/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -I../Common/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-devices

clean-Core-2f-Src-2f-devices:
	-$(RM) ./Core/Src/devices/as5600.cyclo ./Core/Src/devices/as5600.d ./Core/Src/devices/as5600.o ./Core/Src/devices/as5600.su ./Core/Src/devices/as5600_interface.cyclo ./Core/Src/devices/as5600_interface.d ./Core/Src/devices/as5600_interface.o ./Core/Src/devices/as5600_interface.su ./Core/Src/devices/bts7960.cyclo ./Core/Src/devices/bts7960.d ./Core/Src/devices/bts7960.o ./Core/Src/devices/bts7960.su ./Core/Src/devices/bts7960_interface.cyclo ./Core/Src/devices/bts7960_interface.d ./Core/Src/devices/bts7960_interface.o ./Core/Src/devices/bts7960_interface.su ./Core/Src/devices/home_sensor.cyclo ./Core/Src/devices/home_sensor.d ./Core/Src/devices/home_sensor.o ./Core/Src/devices/home_sensor.su ./Core/Src/devices/ina219.cyclo ./Core/Src/devices/ina219.d ./Core/Src/devices/ina219.o ./Core/Src/devices/ina219.su

.PHONY: clean-Core-2f-Src-2f-devices

