################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv5/tools/compiler/tms470_4.9.5

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./source/system.obj" \
"./source/sys_startup.obj" \
"./source/sys_selftest.obj" \
"./source/sys_pmu.obj" \
"./source/sys_phantom.obj" \
"./source/sys_pcr.obj" \
"./source/sys_mpu.obj" \
"./source/sys_main.obj" \
"./source/sys_intvecs.obj" \
"./source/sys_core.obj" \
"./source/sci.obj" \
"./source/rti.obj" \
"./source/pinmux.obj" \
"./source/notification.obj" \
"./source/gio.obj" \
"./source/esm.obj" \
"./source/eqep.obj" \
"./source/dabort.obj" \
"./arm_matrix_example_f32.obj" \
-l"rtsv7R4_T_le_v3D16_eabi.lib" \
-l"C:\ti\Hercules\Cortex-R4 CMSIS DSP Library\1.0.0\Lib\arm_math_Cortex_R4_lspf.lib" \
-l"C:\ti\Hercules\Cortex-R4 CMSIS DSP Library\1.0.0\Lib\ti_math_Cortex_R4_lspf.lib" \
"../source/sys_link.cmd" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include source/subdir_vars.mk
-include subdir_rules.mk
-include source/subdir_rules.mk
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
all: DIP.out

# Tool invocations
DIP.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccsv5/tools/compiler/tms470_4.9.5/bin/cl470" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -me -g --diag_warning=225 --display_error_number --enum_type=packed -z -m"DIP.map" -i"C:/ti/ccsv5/tools/compiler/tms470_4.9.5/lib" -i"C:/ti/ccsv5/tools/compiler/tms470_4.9.5/include" --reread_libs --warn_sections --display_error_number --rom_model -o "DIP.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(TMS470_EXECUTABLE_OUTPUTS__QUOTED) "DIP.out"
	-$(RM) "arm_matrix_example_f32.pp" "source\eqep.pp" "source\esm.pp" "source\gio.pp" "source\notification.pp" "source\pinmux.pp" "source\rti.pp" "source\sci.pp" "source\sys_main.pp" "source\sys_pcr.pp" "source\sys_phantom.pp" "source\sys_selftest.pp" "source\sys_startup.pp" "source\system.pp" 
	-$(RM) "arm_matrix_example_f32.obj" "source\dabort.obj" "source\eqep.obj" "source\esm.obj" "source\gio.obj" "source\notification.obj" "source\pinmux.obj" "source\rti.obj" "source\sci.obj" "source\sys_core.obj" "source\sys_intvecs.obj" "source\sys_main.obj" "source\sys_mpu.obj" "source\sys_pcr.obj" "source\sys_phantom.obj" "source\sys_pmu.obj" "source\sys_selftest.obj" "source\sys_startup.obj" "source\system.obj" 
	-$(RM) "source\dabort.pp" "source\sys_core.pp" "source\sys_intvecs.pp" "source\sys_mpu.pp" "source\sys_pmu.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
