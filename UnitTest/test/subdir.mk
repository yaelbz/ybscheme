################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/AllTests.cpp \
../test/TestHelper.cpp 

OBJS += \
./test/AllTests.o \
./test/TestHelper.o 

CPP_DEPS += \
./test/AllTests.d \
./test/TestHelper.d 


# Each subdirectory must supply rules for building sources it contributes
test/%.o: ../test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/martin/workspace/ybschemeTest/contrib" -I"/home/martin/workspace/ybscheme/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


