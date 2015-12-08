################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Application/LIN_Slave4.c" \
"../Sources/Application/Slave_Actions.c" \

C_SRCS += \
../Sources/Application/LIN_Slave4.c \
../Sources/Application/Slave_Actions.c \

OBJS += \
./Sources/Application/LIN_Slave4_c.obj \
./Sources/Application/Slave_Actions_c.obj \

OBJS_QUOTED += \
"./Sources/Application/LIN_Slave4_c.obj" \
"./Sources/Application/Slave_Actions_c.obj" \

C_DEPS += \
./Sources/Application/LIN_Slave4_c.d \
./Sources/Application/Slave_Actions_c.d \

OBJS_OS_FORMAT += \
./Sources/Application/LIN_Slave4_c.obj \
./Sources/Application/Slave_Actions_c.obj \

C_DEPS_QUOTED += \
"./Sources/Application/LIN_Slave4_c.d" \
"./Sources/Application/Slave_Actions_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Application/LIN_Slave4_c.obj: ../Sources/Application/LIN_Slave4.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/Application/LIN_Slave4.args" -o "Sources/Application/LIN_Slave4_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/Application/%.d: ../Sources/Application/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/Application/Slave_Actions_c.obj: ../Sources/Application/Slave_Actions.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/Application/Slave_Actions.args" -o "Sources/Application/Slave_Actions_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


