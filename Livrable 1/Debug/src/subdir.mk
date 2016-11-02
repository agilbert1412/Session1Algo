################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/arret.cpp \
../src/auxiliaires.cpp \
../src/coordonnees.cpp \
../src/ligne.cpp \
../src/main.cpp \
../src/station.cpp \
../src/voyage.cpp 

OBJS += \
./src/arret.o \
./src/auxiliaires.o \
./src/coordonnees.o \
./src/ligne.o \
./src/main.o \
./src/station.o \
./src/voyage.o 

CPP_DEPS += \
./src/arret.d \
./src/auxiliaires.d \
./src/coordonnees.d \
./src/ligne.d \
./src/main.d \
./src/station.d \
./src/voyage.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


