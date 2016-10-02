################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Livrable\ 1.cpp \
../src/arret.cpp \
../src/coordonnees.cpp \
../src/ligne.cpp \
../src/station.cpp \
../src/voyage.cpp 

OBJS += \
./src/Livrable\ 1.o \
./src/arret.o \
./src/coordonnees.o \
./src/ligne.o \
./src/station.o \
./src/voyage.o 

CPP_DEPS += \
./src/Livrable\ 1.d \
./src/arret.d \
./src/coordonnees.d \
./src/ligne.d \
./src/station.d \
./src/voyage.d 


# Each subdirectory must supply rules for building sources it contributes
src/Livrable\ 1.o: ../src/Livrable\ 1.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Livrable 1.d" -MT"src/Livrable\ 1.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


