################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/HLED/HLED_program.c 

OBJS += \
./HAL/HLED/HLED_program.o 

C_DEPS += \
./HAL/HLED/HLED_program.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/HLED/%.o: ../HAL/HLED/%.c HAL/HLED/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\IMT\03- Microcontroller Interfacing AVR\GitHub\Timer_using_ATmega32\HAL" -I"C:\IMT\03- Microcontroller Interfacing AVR\GitHub\Timer_using_ATmega32\HAL\HKEYPAD" -I"C:\IMT\03- Microcontroller Interfacing AVR\GitHub\Timer_using_ATmega32\HAL\HLCD" -I"C:\IMT\03- Microcontroller Interfacing AVR\GitHub\Timer_using_ATmega32\HAL\HLED" -I"C:\IMT\03- Microcontroller Interfacing AVR\GitHub\Timer_using_ATmega32\LIB" -I"C:\IMT\03- Microcontroller Interfacing AVR\GitHub\Timer_using_ATmega32\MCAL\MDIO" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


