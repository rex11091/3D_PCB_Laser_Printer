################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/CException.c \
../Src/CommandCode.c \
../Src/Exception.c \
../Src/Integration.c \
../Src/MotorController.c \
../Src/MotorStep.c \
../Src/UserConfig.c \
../Src/getCMD.c \
../Src/hardwareConfig.c \
../Src/main.c \
../Src/stm32f1xx_hal_msp.c \
../Src/stm32f1xx_it.c \
../Src/system_stm32f1xx.c \
../Src/usb_device.c \
../Src/usbd_cdc_if.c \
../Src/usbd_conf.c \
../Src/usbd_desc.c 

OBJS += \
./Src/CException.o \
./Src/CommandCode.o \
./Src/Exception.o \
./Src/Integration.o \
./Src/MotorController.o \
./Src/MotorStep.o \
./Src/UserConfig.o \
./Src/getCMD.o \
./Src/hardwareConfig.o \
./Src/main.o \
./Src/stm32f1xx_hal_msp.o \
./Src/stm32f1xx_it.o \
./Src/system_stm32f1xx.o \
./Src/usb_device.o \
./Src/usbd_cdc_if.o \
./Src/usbd_conf.o \
./Src/usbd_desc.o 

C_DEPS += \
./Src/CException.d \
./Src/CommandCode.d \
./Src/Exception.d \
./Src/Integration.d \
./Src/MotorController.d \
./Src/MotorStep.d \
./Src/UserConfig.d \
./Src/getCMD.d \
./Src/hardwareConfig.d \
./Src/main.d \
./Src/stm32f1xx_hal_msp.d \
./Src/stm32f1xx_it.d \
./Src/system_stm32f1xx.d \
./Src/usb_device.d \
./Src/usbd_cdc_if.d \
./Src/usbd_conf.d \
./Src/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"C:/REX/3D_PCB_Laser_Printer/Inc" -I"C:/REX/StepperMotor/vendor/ceedling/vendor/unity/release" -I"C:/REX/3D_PCB_Laser_Printer/Drivers/STM32F1xx_HAL_Driver/Inc" -I"C:/REX/3D_PCB_Laser_Printer/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"C:/REX/3D_PCB_Laser_Printer/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/REX/3D_PCB_Laser_Printer/Drivers/CMSIS/Include" -I"C:/REX/3D_PCB_Laser_Printer/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/REX/3D_PCB_Laser_Printer/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


