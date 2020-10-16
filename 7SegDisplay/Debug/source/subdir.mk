################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/App.c \
../source/SevenSegDisplay.c \
../source/SysTick.c \
../source/Timer.c \
../source/encoder.c \
../source/gpio.c \
../source/lector.c 

OBJS += \
./source/App.o \
./source/SevenSegDisplay.o \
./source/SysTick.o \
./source/Timer.o \
./source/encoder.o \
./source/gpio.o \
./source/lector.o 

C_DEPS += \
./source/App.d \
./source/SevenSegDisplay.d \
./source/SysTick.d \
./source/Timer.d \
./source/encoder.d \
./source/gpio.d \
./source/lector.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DCPU_MK64FN1M0VLL12_cm4 -DCPU_MK64FN1M0VLL12 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I../source -I../ -I../CMSIS -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


