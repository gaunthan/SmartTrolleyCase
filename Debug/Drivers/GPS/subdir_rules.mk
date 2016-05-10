################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Drivers/GPS/GPS.obj: ../Drivers/GPS/GPS.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"D:/Program Files/TI/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmspx --abi=eabi --data_model=restricted --include_path="D:/Program Files/TI/ccsv6/ccs_base/msp430/include" --include_path="D:/Program Files/TI/ccsv6/tools/compiler/msp430_4.3.3/include" --include_path="E:/Workspace/TI/SmartTrolleyCase/MSP-EXP430F5529_HAL" --include_path="E:/Workspace/TI/SmartTrolleyCase" --include_path="E:/Workspace/TI/SmartTrolleyCase/F5xx_F6xx_Core_Lib" --include_path="E:/Workspace/TI/SmartTrolleyCase/Drivers/GPS" --include_path="E:/Workspace/TI/SmartTrolleyCase/Drivers/nmea_decode/include" --advice:power=all -g --define=__MSP430F5529__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="Drivers/GPS/GPS.pp" --obj_directory="Drivers/GPS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


