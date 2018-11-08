################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CommandLineParser.cpp \
../Connection.cpp \
../EndPoint.cpp \
../Helpers.cpp \
../ProtocolParser.cpp \
../ProtocolValidator.cpp \
../Receive.cpp \
../Send.cpp \
../Socket.cpp \
../Transact.cpp \
../dns_forwarder.cpp 

OBJS += \
./CommandLineParser.o \
./Connection.o \
./EndPoint.o \
./Helpers.o \
./ProtocolParser.o \
./ProtocolValidator.o \
./Receive.o \
./Send.o \
./Socket.o \
./Transact.o \
./dns_forwarder.o 

CPP_DEPS += \
./CommandLineParser.d \
./Connection.d \
./EndPoint.d \
./Helpers.d \
./ProtocolParser.d \
./ProtocolValidator.d \
./Receive.d \
./Send.d \
./Socket.d \
./Transact.d \
./dns_forwarder.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++14 -D__cpluplus=201402L -I/usr/include/boost -O0 -g3 -pedantic -pedantic-errors -w -Wall -Wextra -Werror -Wconversion -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


