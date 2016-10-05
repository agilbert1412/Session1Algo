################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Livrable1.cpp \
../src/arret.cpp \
../src/auxiliaires.cpp \
../src/coordonnees.cpp \
../src/ligne.cpp \
../src/station.cpp \
../src/voyage.cpp 

OBJS += \
./src/Livrable1.o \
./src/arret.o \
./src/auxiliaires.o \
./src/coordonnees.o \
./src/ligne.o \
./src/station.o \
./src/voyage.o 

CPP_DEPS += \
./src/Livrable1.d \
./src/arret.d \
./src/auxiliaires.d \
./src/coordonnees.d \
./src/ligne.d \
./src/station.d \
./src/voyage.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


