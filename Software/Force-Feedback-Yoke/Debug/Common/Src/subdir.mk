################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Common/Src/feed_forward.c \
../Common/Src/force_feedback_controller.c \
../Common/Src/force_feedback_periodic.c \
../Common/Src/pid.c \
../Common/Src/rotary_encoder.c \
../Common/Src/utilities.c 

C_DEPS += \
./Common/Src/feed_forward.d \
./Common/Src/force_feedback_controller.d \
./Common/Src/force_feedback_periodic.d \
./Common/Src/pid.d \
./Common/Src/rotary_encoder.d \
./Common/Src/utilities.d 

OBJS += \
./Common/Src/feed_forward.o \
./Common/Src/force_feedback_controller.o \
./Common/Src/force_feedback_periodic.o \
./Common/Src/pid.o \
./Common/Src/rotary_encoder.o \
./Common/Src/utilities.o 


# Each subdirectory must supply rules for building sources it contributes
Common/Src/%.o Common/Src/%.su Common/Src/%.cyclo: ../Common/Src/%.c Common/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../Common -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Common-2f-Src

clean-Common-2f-Src:
	-$(RM) ./Common/Src/feed_forward.cyclo ./Common/Src/feed_forward.d ./Common/Src/feed_forward.o ./Common/Src/feed_forward.su ./Common/Src/force_feedback_controller.cyclo ./Common/Src/force_feedback_controller.d ./Common/Src/force_feedback_controller.o ./Common/Src/force_feedback_controller.su ./Common/Src/force_feedback_periodic.cyclo ./Common/Src/force_feedback_periodic.d ./Common/Src/force_feedback_periodic.o ./Common/Src/force_feedback_periodic.su ./Common/Src/pid.cyclo ./Common/Src/pid.d ./Common/Src/pid.o ./Common/Src/pid.su ./Common/Src/rotary_encoder.cyclo ./Common/Src/rotary_encoder.d ./Common/Src/rotary_encoder.o ./Common/Src/rotary_encoder.su ./Common/Src/utilities.cyclo ./Common/Src/utilities.d ./Common/Src/utilities.o ./Common/Src/utilities.su

.PHONY: clean-Common-2f-Src

