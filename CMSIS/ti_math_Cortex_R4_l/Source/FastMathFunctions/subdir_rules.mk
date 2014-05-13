################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Source/FastMathFunctions/arm_cos_f32.obj: ../Source/FastMathFunctions/arm_cos_f32.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/tms470_5.0.0/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me -O3 --opt_for_speed=5 --fp_mode=strict -g --optimize_with_debug=on --include_path="C:/ti/ccsv5/tools/compiler/tms470_5.0.0/include" --include_path="M:/Data/Software/CMSIS/Include" --define=ARM_MATH_MATRIX_CHECK --define=ARM_MATH_ROUNDING --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="Source/FastMathFunctions/arm_cos_f32.pp" --obj_directory="Source/FastMathFunctions" --vectorize=off $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/FastMathFunctions/arm_cos_q15.obj: ../Source/FastMathFunctions/arm_cos_q15.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/tms470_5.0.0/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me -O3 --opt_for_speed=5 --fp_mode=strict -g --optimize_with_debug=on --include_path="C:/ti/ccsv5/tools/compiler/tms470_5.0.0/include" --include_path="M:/Data/Software/CMSIS/Include" --define=ARM_MATH_MATRIX_CHECK --define=ARM_MATH_ROUNDING --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="Source/FastMathFunctions/arm_cos_q15.pp" --obj_directory="Source/FastMathFunctions" --vectorize=off $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/FastMathFunctions/arm_cos_q31.obj: ../Source/FastMathFunctions/arm_cos_q31.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/tms470_5.0.0/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me -O3 --opt_for_speed=5 --fp_mode=strict -g --optimize_with_debug=on --include_path="C:/ti/ccsv5/tools/compiler/tms470_5.0.0/include" --include_path="M:/Data/Software/CMSIS/Include" --define=ARM_MATH_MATRIX_CHECK --define=ARM_MATH_ROUNDING --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="Source/FastMathFunctions/arm_cos_q31.pp" --obj_directory="Source/FastMathFunctions" --vectorize=off $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/FastMathFunctions/arm_sin_f32.obj: ../Source/FastMathFunctions/arm_sin_f32.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/tms470_5.0.0/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me -O3 --opt_for_speed=5 --fp_mode=strict -g --optimize_with_debug=on --include_path="C:/ti/ccsv5/tools/compiler/tms470_5.0.0/include" --include_path="M:/Data/Software/CMSIS/Include" --define=ARM_MATH_MATRIX_CHECK --define=ARM_MATH_ROUNDING --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="Source/FastMathFunctions/arm_sin_f32.pp" --obj_directory="Source/FastMathFunctions" --vectorize=off $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/FastMathFunctions/arm_sin_q15.obj: ../Source/FastMathFunctions/arm_sin_q15.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/tms470_5.0.0/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me -O3 --opt_for_speed=5 --fp_mode=strict -g --optimize_with_debug=on --include_path="C:/ti/ccsv5/tools/compiler/tms470_5.0.0/include" --include_path="M:/Data/Software/CMSIS/Include" --define=ARM_MATH_MATRIX_CHECK --define=ARM_MATH_ROUNDING --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="Source/FastMathFunctions/arm_sin_q15.pp" --obj_directory="Source/FastMathFunctions" --vectorize=off $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/FastMathFunctions/arm_sin_q31.obj: ../Source/FastMathFunctions/arm_sin_q31.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/tms470_5.0.0/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me -O3 --opt_for_speed=5 --fp_mode=strict -g --optimize_with_debug=on --include_path="C:/ti/ccsv5/tools/compiler/tms470_5.0.0/include" --include_path="M:/Data/Software/CMSIS/Include" --define=ARM_MATH_MATRIX_CHECK --define=ARM_MATH_ROUNDING --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="Source/FastMathFunctions/arm_sin_q31.pp" --obj_directory="Source/FastMathFunctions" --vectorize=off $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/FastMathFunctions/arm_sqrt_q15.obj: ../Source/FastMathFunctions/arm_sqrt_q15.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/tms470_5.0.0/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me -O3 --opt_for_speed=5 --fp_mode=strict -g --optimize_with_debug=on --include_path="C:/ti/ccsv5/tools/compiler/tms470_5.0.0/include" --include_path="M:/Data/Software/CMSIS/Include" --define=ARM_MATH_MATRIX_CHECK --define=ARM_MATH_ROUNDING --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="Source/FastMathFunctions/arm_sqrt_q15.pp" --obj_directory="Source/FastMathFunctions" --vectorize=off $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/FastMathFunctions/arm_sqrt_q31.obj: ../Source/FastMathFunctions/arm_sqrt_q31.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/tms470_5.0.0/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me -O3 --opt_for_speed=5 --fp_mode=strict -g --optimize_with_debug=on --include_path="C:/ti/ccsv5/tools/compiler/tms470_5.0.0/include" --include_path="M:/Data/Software/CMSIS/Include" --define=ARM_MATH_MATRIX_CHECK --define=ARM_MATH_ROUNDING --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="Source/FastMathFunctions/arm_sqrt_q31.pp" --obj_directory="Source/FastMathFunctions" --vectorize=off $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


