################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/SignalHandler.c \
../src/clean_text.c \
../src/do_crc.c \
../src/domain_socket_server.c \
../src/domain_socket_server_setup.c \
../src/get_appver.c \
../src/get_bootver.c \
../src/get_command_from_file.c \
../src/get_model.c \
../src/get_serial.c \
../src/get_varname.c \
../src/log_function.c \
../src/mei_rx.c \
../src/mei_service.c \
../src/mei_tx.c \
../src/process_commands.c \
../src/process_response.c 

OBJS += \
./src/SignalHandler.o \
./src/clean_text.o \
./src/do_crc.o \
./src/domain_socket_server.o \
./src/domain_socket_server_setup.o \
./src/get_appver.o \
./src/get_bootver.o \
./src/get_command_from_file.o \
./src/get_model.o \
./src/get_serial.o \
./src/get_varname.o \
./src/log_function.o \
./src/mei_rx.o \
./src/mei_service.o \
./src/mei_tx.o \
./src/process_commands.o \
./src/process_response.o 

C_DEPS += \
./src/SignalHandler.d \
./src/clean_text.d \
./src/do_crc.d \
./src/domain_socket_server.d \
./src/domain_socket_server_setup.d \
./src/get_appver.d \
./src/get_bootver.d \
./src/get_command_from_file.d \
./src/get_model.d \
./src/get_serial.d \
./src/get_varname.d \
./src/log_function.d \
./src/mei_rx.d \
./src/mei_service.d \
./src/mei_tx.d \
./src/process_commands.d \
./src/process_response.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	arm-linux-gnueabihf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


