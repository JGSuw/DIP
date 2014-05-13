################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Source/CommonTables/arm_common_tables.obj: ../Source/CommonTables/arm_common_tables.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/tms470_5.0.0/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -me -O3 --opt_for_speed=5 --fp_mode=strict -g --optimize_with_debug=on --include_path="C:/ti/ccsv5/tools/compiler/tms470_5.0.0/include" --include_path="M:/Data/Software/CMSIS/Include" --define=ARM_MATH_MATRIX_CHECK --define=ARM_MATH_ROUNDING --define=FPU_PRESENT --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="Source/CommonTables/arm_common_tables.pp" --obj_directory="Source/CommonTables" --vectorize=off $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


