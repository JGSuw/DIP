################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Source/ControllerFunctions/arm_pid_init_f32.obj: ../Source/ControllerFunctions/arm_pid_init_f32.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/tms470_5.0.0/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -me -O0 --opt_for_speed=2 --fp_mode=strict -g --optimize_with_debug=on --include_path="C:/ti/ccsv5/tools/compiler/tms470_5.0.0/include" --include_path="M:/Data/Software/CMSIS/Include" --define=ARM_MATH_MATRIX_CHECK --define=ARM_MATH_ROUNDING --define=FPU_PRESENT --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="Source/ControllerFunctions/arm_pid_init_f32.pp" --obj_directory="Source/ControllerFunctions" --vectorize=off $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/ControllerFunctions/arm_pid_init_q15.obj: ../Source/ControllerFunctions/arm_pid_init_q15.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/tms470_5.0.0/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -me -O0 --opt_for_speed=2 --fp_mode=strict -g --optimize_with_debug=on --include_path="C:/ti/ccsv5/tools/compiler/tms470_5.0.0/include" --include_path="M:/Data/Software/CMSIS/Include" --define=ARM_MATH_MATRIX_CHECK --define=ARM_MATH_ROUNDING --define=FPU_PRESENT --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="Source/ControllerFunctions/arm_pid_init_q15.pp" --obj_directory="Source/ControllerFunctions" --vectorize=off $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/ControllerFunctions/arm_pid_init_q31.obj: ../Source/ControllerFunctions/arm_pid_init_q31.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/tms470_5.0.0/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -me -O0 --opt_for_speed=2 --fp_mode=strict -g --optimize_with_debug=on --include_path="C:/ti/ccsv5/tools/compiler/tms470_5.0.0/include" --include_path="M:/Data/Software/CMSIS/Include" --define=ARM_MATH_MATRIX_CHECK --define=ARM_MATH_ROUNDING --define=FPU_PRESENT --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="Source/ControllerFunctions/arm_pid_init_q31.pp" --obj_directory="Source/ControllerFunctions" --vectorize=off $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/ControllerFunctions/arm_pid_reset_f32.obj: ../Source/ControllerFunctions/arm_pid_reset_f32.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/tms470_5.0.0/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -me -O0 --opt_for_speed=2 --fp_mode=strict -g --optimize_with_debug=on --include_path="C:/ti/ccsv5/tools/compiler/tms470_5.0.0/include" --include_path="M:/Data/Software/CMSIS/Include" --define=ARM_MATH_MATRIX_CHECK --define=ARM_MATH_ROUNDING --define=FPU_PRESENT --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="Source/ControllerFunctions/arm_pid_reset_f32.pp" --obj_directory="Source/ControllerFunctions" --vectorize=off $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/ControllerFunctions/arm_pid_reset_q15.obj: ../Source/ControllerFunctions/arm_pid_reset_q15.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/tms470_5.0.0/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -me -O0 --opt_for_speed=2 --fp_mode=strict -g --optimize_with_debug=on --include_path="C:/ti/ccsv5/tools/compiler/tms470_5.0.0/include" --include_path="M:/Data/Software/CMSIS/Include" --define=ARM_MATH_MATRIX_CHECK --define=ARM_MATH_ROUNDING --define=FPU_PRESENT --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="Source/ControllerFunctions/arm_pid_reset_q15.pp" --obj_directory="Source/ControllerFunctions" --vectorize=off $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/ControllerFunctions/arm_pid_reset_q31.obj: ../Source/ControllerFunctions/arm_pid_reset_q31.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/tms470_5.0.0/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -me -O0 --opt_for_speed=2 --fp_mode=strict -g --optimize_with_debug=on --include_path="C:/ti/ccsv5/tools/compiler/tms470_5.0.0/include" --include_path="M:/Data/Software/CMSIS/Include" --define=ARM_MATH_MATRIX_CHECK --define=ARM_MATH_ROUNDING --define=FPU_PRESENT --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="Source/ControllerFunctions/arm_pid_reset_q31.pp" --obj_directory="Source/ControllerFunctions" --vectorize=off $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/ControllerFunctions/arm_sin_cos_f32.obj: ../Source/ControllerFunctions/arm_sin_cos_f32.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/tms470_5.0.0/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -me -O3 --opt_for_speed=5 --fp_mode=strict -g --optimize_with_debug=on --include_path="C:/ti/ccsv5/tools/compiler/tms470_5.0.0/include" --include_path="M:/Data/Software/CMSIS/Include" --define=ARM_MATH_MATRIX_CHECK --define=ARM_MATH_ROUNDING --define=FPU_PRESENT --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="Source/ControllerFunctions/arm_sin_cos_f32.pp" --obj_directory="Source/ControllerFunctions" --vectorize=off $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/ControllerFunctions/arm_sin_cos_q31.obj: ../Source/ControllerFunctions/arm_sin_cos_q31.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/tms470_5.0.0/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -me -O3 --opt_for_speed=5 --fp_mode=strict -g --optimize_with_debug=on --include_path="C:/ti/ccsv5/tools/compiler/tms470_5.0.0/include" --include_path="M:/Data/Software/CMSIS/Include" --define=ARM_MATH_MATRIX_CHECK --define=ARM_MATH_ROUNDING --define=FPU_PRESENT --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="Source/ControllerFunctions/arm_sin_cos_q31.pp" --obj_directory="Source/ControllerFunctions" --vectorize=off $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


