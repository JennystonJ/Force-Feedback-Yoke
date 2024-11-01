################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Common/Src/button.c \
../Common/Src/encoder.c \
../Common/Src/feed_forward.c \
../Common/Src/force_feedback_controller.c \
../Common/Src/force_feedback_periodic.c \
../Common/Src/motor.c \
../Common/Src/packet_parser.c \
../Common/Src/pid.c \
../Common/Src/rotary_encoder.c \
../Common/Src/usb_report.c 

C_DEPS += \
./Common/Src/button.d \
./Common/Src/encoder.d \
./Common/Src/feed_forward.d \
./Common/Src/force_feedback_controller.d \
./Common/Src/force_feedback_periodic.d \
./Common/Src/motor.d \
./Common/Src/packet_parser.d \
./Common/Src/pid.d \
./Common/Src/rotary_encoder.d \
./Common/Src/usb_report.d 

OBJS += \
./Common/Src/button.o \
./Common/Src/encoder.o \
./Common/Src/feed_forward.o \
./Common/Src/force_feedback_controller.o \
./Common/Src/force_feedback_periodic.o \
./Common/Src/motor.o \
./Common/Src/packet_parser.o \
./Common/Src/pid.o \
./Common/Src/rotary_encoder.o \
./Common/Src/usb_report.o 


# Each subdirectory must supply rules for building sources it contributes
Common/Src/%.o Common/Src/%.su Common/Src/%.cyclo: ../Common/Src/%.c Common/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -I../Common/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Common-2f-Src

clean-Common-2f-Src:
	-$(RM) ./Common/Src/button.cyclo ./Common/Src/button.d ./Common/Src/button.o ./Common/Src/button.su ./Common/Src/encoder.cyclo ./Common/Src/encoder.d ./Common/Src/encoder.o ./Common/Src/encoder.su ./Common/Src/feed_forward.cyclo ./Common/Src/feed_forward.d ./Common/Src/feed_forward.o ./Common/Src/feed_forward.su ./Common/Src/force_feedback_controller.cyclo ./Common/Src/force_feedback_controller.d ./Common/Src/force_feedback_controller.o ./Common/Src/force_feedback_controller.su ./Common/Src/force_feedback_periodic.cyclo ./Common/Src/force_feedback_periodic.d ./Common/Src/force_feedback_periodic.o ./Common/Src/force_feedback_periodic.su ./Common/Src/motor.cyclo ./Common/Src/motor.d ./Common/Src/motor.o ./Common/Src/motor.su ./Common/Src/packet_parser.cyclo ./Common/Src/packet_parser.d ./Common/Src/packet_parser.o ./Common/Src/packet_parser.su ./Common/Src/pid.cyclo ./Common/Src/pid.d ./Common/Src/pid.o ./Common/Src/pid.su ./Common/Src/rotary_encoder.cyclo ./Common/Src/rotary_encoder.d ./Common/Src/rotary_encoder.o ./Common/Src/rotary_encoder.su ./Common/Src/usb_report.cyclo ./Common/Src/usb_report.d ./Common/Src/usb_report.o ./Common/Src/usb_report.su

.PHONY: clean-Common-2f-Src

