################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/auxiliaires.cpp \
../src/coordonnees.cpp \
../src/gestionnaire.cpp \
../src/main.cpp \
../src/reseau.cpp \
../src/station.cpp \
../src/voyage.cpp 

OBJS += \
./src/auxiliaires.o \
./src/coordonnees.o \
./src/gestionnaire.o \
./src/main.o \
./src/reseau.o \
./src/station.o \
./src/voyage.o 

CPP_DEPS += \
./src/auxiliaires.d \
./src/coordonnees.d \
./src/gestionnaire.d \
./src/main.d \
./src/reseau.d \
./src/station.d \
./src/voyage.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


