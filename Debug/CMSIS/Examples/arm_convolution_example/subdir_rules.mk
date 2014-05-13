################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
CMSIS/Examples/arm_convolution_example/arm_convolution_example_f32.obj: ../CMSIS/Examples/arm_convolution_example/arm_convolution_example_f32.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/tms470_4.9.5/bin/cl470" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -me -g --include_path="{CMSIS_LOC}/include" --include_path="C:/ti/ccsv5/tools/compiler/tms470_4.9.5/include" --include_path="C:/Users/Minto/workspace_v5_2/DIP/include" --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="CMSIS/Examples/arm_convolution_example/arm_convolution_example_f32.pp" --obj_directory="CMSIS/Examples/arm_convolution_example" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


