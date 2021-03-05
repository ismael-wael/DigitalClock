################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Application/ControlModule_program.c \
../Src/Application/DisplayModule_program.c \
../Src/Application/InputModule_program.c \
../Src/Application/StatusModule_program.c 

OBJS += \
./Src/Application/ControlModule_program.o \
./Src/Application/DisplayModule_program.o \
./Src/Application/InputModule_program.o \
./Src/Application/StatusModule_program.o 

C_DEPS += \
./Src/Application/ControlModule_program.d \
./Src/Application/DisplayModule_program.d \
./Src/Application/InputModule_program.d \
./Src/Application/StatusModule_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Application/ControlModule_program.o: ../Src/Application/ControlModule_program.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/Application/ControlModule_program.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/Application/DisplayModule_program.o: ../Src/Application/DisplayModule_program.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/Application/DisplayModule_program.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/Application/InputModule_program.o: ../Src/Application/InputModule_program.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/Application/InputModule_program.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/Application/StatusModule_program.o: ../Src/Application/StatusModule_program.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/Application/StatusModule_program.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

