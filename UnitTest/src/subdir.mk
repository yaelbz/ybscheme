################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/builtins.c \
../src/environment.c \
../src/evalStack.c \
../src/evaluator.c \
../src/global.c \
../src/printer.c \
../src/reader.c \
../src/symbolTable.c 

OBJS += \
./src/builtins.o \
./src/environment.o \
./src/evalStack.o \
./src/evaluator.o \
./src/global.o \
./src/printer.o \
./src/reader.o \
./src/symbolTable.o 

C_DEPS += \
./src/builtins.d \
./src/environment.d \
./src/evalStack.d \
./src/evaluator.d \
./src/global.d \
./src/printer.d \
./src/reader.d \
./src/symbolTable.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I.././src -I../contrib -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


