################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
arm_graphic_equalizer_data.obj: M:/Data/Software/CMSIS/Examples/arm_graphic_equalizer_example/arm_graphic_equalizer_data.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/tms470_5.0.1/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -g --include_path="C:/ti/ccsv5/tools/compiler/tms470_5.0.1/include" --include_path="../../../../Include" --include_path="../../../../DeviceSupport/TI/Include" --include_path="../../../../HelperFunc/Include" --define=CCS --define=UART_SUPPORT --diag_warning=225 --display_error_number --diag_wrap=off --enum_type=packed --preproc_with_compile --preproc_dependency="arm_graphic_equalizer_data.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

arm_graphic_equalizer_example_q31.obj: M:/Data/Software/CMSIS/Examples/arm_graphic_equalizer_example/arm_graphic_equalizer_example_q31.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/tms470_5.0.1/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -g --include_path="C:/ti/ccsv5/tools/compiler/tms470_5.0.1/include" --include_path="../../../../Include" --include_path="../../../../DeviceSupport/TI/Include" --include_path="../../../../HelperFunc/Include" --define=CCS --define=UART_SUPPORT --diag_warning=225 --display_error_number --diag_wrap=off --enum_type=packed --preproc_with_compile --preproc_dependency="arm_graphic_equalizer_example_q31.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


