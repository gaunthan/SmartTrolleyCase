################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/Program Files/TI/ccsv6/tools/compiler/msp430_4.3.3

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./main.obj" \
"./MSP-EXP430F5529_HAL/HAL_AppUart.obj" \
"./MSP-EXP430F5529_HAL/HAL_Board.obj" \
"./MSP-EXP430F5529_HAL/HAL_Buttons.obj" \
"./MSP-EXP430F5529_HAL/HAL_Cma3000.obj" \
"./MSP-EXP430F5529_HAL/HAL_Dogs102x6.obj" \
"./MSP-EXP430F5529_HAL/HAL_Menu.obj" \
"./MSP-EXP430F5529_HAL/HAL_SDCard.obj" \
"./MSP-EXP430F5529_HAL/HAL_Wheel.obj" \
"./F5xx_F6xx_Core_Lib/HAL_FLASH.obj" \
"./F5xx_F6xx_Core_Lib/HAL_PMAP.obj" \
"./F5xx_F6xx_Core_Lib/HAL_PMM.obj" \
"./F5xx_F6xx_Core_Lib/HAL_TLV.obj" \
"./F5xx_F6xx_Core_Lib/HAL_UCS.obj" \
"./Drivers/GPS/GPS.obj" \
"./Drivers/GPRS/GPRS.obj" \
"../lnk_msp430f5529.cmd" \
-l"libc.a" \
-l"libmath.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include MSP-EXP430F5529_HAL/subdir_vars.mk
-include F5xx_F6xx_Core_Lib/subdir_vars.mk
-include Drivers/GPS/subdir_vars.mk
-include Drivers/GPRS/subdir_vars.mk
-include subdir_rules.mk
-include MSP-EXP430F5529_HAL/subdir_rules.mk
-include F5xx_F6xx_Core_Lib/subdir_rules.mk
-include Drivers/GPS/subdir_rules.mk
-include Drivers/GPRS/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
SmartTrolleyCase.out \

EXE_OUTPUTS__QUOTED += \
"SmartTrolleyCase.out" \

BIN_OUTPUTS += \
SmartTrolleyCase.hex \

BIN_OUTPUTS__QUOTED += \
"SmartTrolleyCase.hex" \


# All Target
all: SmartTrolleyCase.out

# Tool invocations
SmartTrolleyCase.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"D:/Program Files/TI/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmspx --abi=eabi --data_model=restricted --advice:power=all -g --define=__MSP430F5529__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=minimal -z -m"SmartTrolleyCase.map" --heap_size=160 --stack_size=160 --use_hw_mpy=F5 --cinit_hold_wdt=on -i"D:/Program Files/TI/ccsv6/ccs_base/msp430/include" -i"D:/Program Files/TI/ccsv6/tools/compiler/msp430_4.3.3/lib" -i"D:/Program Files/TI/ccsv6/tools/compiler/msp430_4.3.3/include" -i"D:/Program Files/TI/ccsv6/ccs_base/msp430/lib/5xx_6xx_FRxx" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="SmartTrolleyCase_linkInfo.xml" --rom_model -o "SmartTrolleyCase.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

SmartTrolleyCase.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: MSP430 Hex Utility'
	"D:/Program Files/TI/ccsv6/tools/compiler/msp430_4.3.3/bin/hex430" --memwidth=8 --romwidth=8 -o "SmartTrolleyCase.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "main.pp" "MSP-EXP430F5529_HAL\HAL_AppUart.pp" "MSP-EXP430F5529_HAL\HAL_Board.pp" "MSP-EXP430F5529_HAL\HAL_Buttons.pp" "MSP-EXP430F5529_HAL\HAL_Cma3000.pp" "MSP-EXP430F5529_HAL\HAL_Dogs102x6.pp" "MSP-EXP430F5529_HAL\HAL_Menu.pp" "MSP-EXP430F5529_HAL\HAL_SDCard.pp" "MSP-EXP430F5529_HAL\HAL_Wheel.pp" "F5xx_F6xx_Core_Lib\HAL_FLASH.pp" "F5xx_F6xx_Core_Lib\HAL_PMAP.pp" "F5xx_F6xx_Core_Lib\HAL_PMM.pp" "F5xx_F6xx_Core_Lib\HAL_TLV.pp" "F5xx_F6xx_Core_Lib\HAL_UCS.pp" "Drivers\GPS\GPS.pp" "Drivers\GPRS\GPRS.pp" 
	-$(RM) "main.obj" "MSP-EXP430F5529_HAL\HAL_AppUart.obj" "MSP-EXP430F5529_HAL\HAL_Board.obj" "MSP-EXP430F5529_HAL\HAL_Buttons.obj" "MSP-EXP430F5529_HAL\HAL_Cma3000.obj" "MSP-EXP430F5529_HAL\HAL_Dogs102x6.obj" "MSP-EXP430F5529_HAL\HAL_Menu.obj" "MSP-EXP430F5529_HAL\HAL_SDCard.obj" "MSP-EXP430F5529_HAL\HAL_Wheel.obj" "F5xx_F6xx_Core_Lib\HAL_FLASH.obj" "F5xx_F6xx_Core_Lib\HAL_PMAP.obj" "F5xx_F6xx_Core_Lib\HAL_PMM.obj" "F5xx_F6xx_Core_Lib\HAL_TLV.obj" "F5xx_F6xx_Core_Lib\HAL_UCS.obj" "Drivers\GPS\GPS.obj" "Drivers\GPRS\GPRS.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

