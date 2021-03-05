################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/OS/OS_program.c 

OBJS += \
./Src/OS/OS_program.o 

C_DEPS += \
./Src/OS/OS_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/OS/OS_program.o: ../Src/OS/OS_program.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/OS/OS_program.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

