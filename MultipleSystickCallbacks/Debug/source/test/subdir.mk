################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/test/LedTimerTestBench.c 

OBJS += \
./source/test/LedTimerTestBench.o 

C_DEPS += \
./source/test/LedTimerTestBench.d 


# Each subdirectory must supply rules for building sources it contributes
source/test/LedTimerTestBench.o: ../source/test/LedTimerTestBench.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DCPU_MK64FN1M0VLL12_cm4 -DCPU_MK64FN1M0VLL12 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"source/test/LedTimerTestBench.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


