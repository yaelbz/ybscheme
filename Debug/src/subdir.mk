################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/martin/workspace/ybscheme/src/builtins.c \
/home/martin/workspace/ybscheme/src/environment.c \
/home/martin/workspace/ybscheme/src/evalStack.c \
/home/martin/workspace/ybscheme/src/evaluator.c \
/home/martin/workspace/ybscheme/src/global.c \
/home/martin/workspace/ybscheme/src/printer.c \
/home/martin/workspace/ybscheme/src/reader.c \
/home/martin/workspace/ybscheme/src/symbolTable.c \
/home/martin/workspace/ybscheme/src/ybscheme.c 

OBJS += \
./src/builtins.o \
./src/environment.o \
./src/evalStack.o \
./src/evaluator.o \
./src/global.o \
./src/printer.o \
./src/reader.o \
./src/symbolTable.o \
./src/ybscheme.o 

C_DEPS += \
./src/builtins.d \
./src/environment.d \
./src/evalStack.d \
./src/evaluator.d \
./src/global.d \
./src/printer.d \
./src/reader.d \
./src/symbolTable.d \
./src/ybscheme.d 


# Each subdirectory must supply rules for building sources it contributes
src/builtins.o: /home/martin/workspace/ybscheme/src/builtins.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/martin/workspace/ybscheme/src" -O0 -g3 -std=c99 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/environment.o: /home/martin/workspace/ybscheme/src/environment.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/martin/workspace/ybscheme/src" -O0 -g3 -std=c99 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/evalStack.o: /home/martin/workspace/ybscheme/src/evalStack.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/martin/workspace/ybscheme/src" -O0 -g3 -std=c99 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/evaluator.o: /home/martin/workspace/ybscheme/src/evaluator.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/martin/workspace/ybscheme/src" -O0 -g3 -std=c99 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/global.o: /home/martin/workspace/ybscheme/src/global.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/martin/workspace/ybscheme/src" -O0 -g3 -std=c99 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/printer.o: /home/martin/workspace/ybscheme/src/printer.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/martin/workspace/ybscheme/src" -O0 -g3 -std=c99 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/reader.o: /home/martin/workspace/ybscheme/src/reader.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/martin/workspace/ybscheme/src" -O0 -g3 -std=c99 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/symbolTable.o: /home/martin/workspace/ybscheme/src/symbolTable.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/martin/workspace/ybscheme/src" -O0 -g3 -std=c99 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ybscheme.o: /home/martin/workspace/ybscheme/src/ybscheme.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/martin/workspace/ybscheme/src" -O0 -g3 -std=c99 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


