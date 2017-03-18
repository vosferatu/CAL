################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Client.cpp \
../src/Geography.cpp \
../src/Interface.cpp \
../src/Node.cpp \
../src/Street.cpp 

OBJS += \
./src/Client.o \
./src/Geography.o \
./src/Interface.o \
./src/Node.o \
./src/Street.o 

CPP_DEPS += \
./src/Client.d \
./src/Geography.d \
./src/Interface.d \
./src/Node.d \
./src/Street.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


