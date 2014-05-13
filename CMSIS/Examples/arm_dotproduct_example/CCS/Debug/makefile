################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv5/tools/compiler/tms470_5.0.1

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./HelperFunc/Source/math_helper.obj" \
"./Source/system.obj" \
"./Source/sys_startup.obj" \
"./Source/sys_pmu.obj" \
"./Source/sys_phantom.obj" \
"./Source/sys_mpu.obj" \
"./Source/sys_memory.obj" \
"./Source/sys_intvecs.obj" \
"./Source/sys_core.obj" \
"./Source/spi.obj" \
"./Source/sci.obj" \
"./Source/rtp.obj" \
"./Source/rti.obj" \
"./Source/pom.obj" \
"./Source/pinmux.obj" \
"./Source/perf_monitor_r4.obj" \
"./Source/mibspi.obj" \
"./Source/mdio.obj" \
"./Source/lin.obj" \
"./Source/i2c.obj" \
"./Source/het.obj" \
"./Source/gio.obj" \
"./Source/esm.obj" \
"./Source/emif.obj" \
"./Source/emac.obj" \
"./Source/dmm.obj" \
"./Source/dcc.obj" \
"./Source/can.obj" \
"./Source/adc.obj" \
"./arm_dotproduct_example_f32.obj" \
-l"rtsv7R4_T_be_v3D16_eabi.lib" \
-l"M:\Data\Software\CMSIS\Lib\ti_math_Cortex_R4_bspf.lib" \
"M:/Data/Software/CMSIS/Source/lnk_r4_flash.cmd" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Source/subdir_vars.mk
-include HelperFunc/Source/subdir_vars.mk
-include subdir_rules.mk
-include Source/subdir_rules.mk
-include HelperFunc/Source/subdir_rules.mk
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

# All Target
all: arm_dotproduct_example.out

# Tool invocations
arm_dotproduct_example.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccsv5/tools/compiler/tms470_5.0.1/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -g --define=CCS --define=UART_SUPPORT --diag_warning=225 --display_error_number --diag_wrap=off --enum_type=packed -z -m"arm_dotproduct_example.map" -i"C:/ti/ccsv5/tools/compiler/tms470_5.0.1/lib" -i"C:/ti/ccsv5/tools/compiler/tms470_5.0.1/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --rom_model --be32 -o "arm_dotproduct_example.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(TMS470_EXECUTABLE_OUTPUTS__QUOTED) "arm_dotproduct_example.out"
	-$(RM) "arm_dotproduct_example_f32.pp" "Source\adc.pp" "Source\can.pp" "Source\dcc.pp" "Source\dmm.pp" "Source\emac.pp" "Source\emif.pp" "Source\esm.pp" "Source\gio.pp" "Source\het.pp" "Source\i2c.pp" "Source\lin.pp" "Source\mdio.pp" "Source\mibspi.pp" "Source\pinmux.pp" "Source\pom.pp" "Source\rti.pp" "Source\rtp.pp" "Source\sci.pp" "Source\spi.pp" "Source\sys_phantom.pp" "Source\sys_startup.pp" "Source\system.pp" "HelperFunc\Source\math_helper.pp" 
	-$(RM) "arm_dotproduct_example_f32.obj" "Source\adc.obj" "Source\can.obj" "Source\dcc.obj" "Source\dmm.obj" "Source\emac.obj" "Source\emif.obj" "Source\esm.obj" "Source\gio.obj" "Source\het.obj" "Source\i2c.obj" "Source\lin.obj" "Source\mdio.obj" "Source\mibspi.obj" "Source\perf_monitor_r4.obj" "Source\pinmux.obj" "Source\pom.obj" "Source\rti.obj" "Source\rtp.obj" "Source\sci.obj" "Source\spi.obj" "Source\sys_core.obj" "Source\sys_intvecs.obj" "Source\sys_memory.obj" "Source\sys_mpu.obj" "Source\sys_phantom.obj" "Source\sys_pmu.obj" "Source\sys_startup.obj" "Source\system.obj" "HelperFunc\Source\math_helper.obj" 
	-$(RM) "Source\perf_monitor_r4.pp" "Source\sys_core.pp" "Source\sys_intvecs.pp" "Source\sys_memory.pp" "Source\sys_mpu.pp" "Source\sys_pmu.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
