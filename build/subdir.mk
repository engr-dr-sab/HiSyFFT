################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/FFT_IP_GENERATOR.c \
../src/fixed_point_lib.c \
../src/support_functions.c 

OBJS += \
./FFT_IP_GENERATOR.o \
./fixed_point_lib.o \
./support_functions.o 

C_DEPS += \
./FFT_IP_GENERATOR.d \
./fixed_point_lib.d \
./support_functions.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


