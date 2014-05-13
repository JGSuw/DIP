################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
HelperFunc/Source/math_helper.obj: M:/Data/Software/CMSIS/Examples/HelperFunc/Source/math_helper.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/tms470_5.0.1/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -g --include_path="C:/ti/ccsv5/tools/compiler/tms470_5.0.1/include" --include_path="../../../../Include" --include_path="../../../../DeviceSupport/TI/Include" --include_path="../../../../HelperFunc/Include" --define=CCS --define=UART_SUPPORT --diag_warning=225 --display_error_number --diag_wrap=off --enum_type=packed --preproc_with_compile --preproc_dependency="HelperFunc/Source/math_helper.pp" --obj_directory="HelperFunc/Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


