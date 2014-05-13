#include "arm_math.h"

#ifndef MATH_HELPER_H
#define MATH_HELPER_H

float arm_snr_f32(float *pRef, float *pTest,  uint32_t buffSize);  
void arm_float_to_q12_20(float *pIn, q31_t * pOut, uint32_t numSamples);
void arm_provide_guard_bits_q15(q15_t *input_buf, uint32_t blockSize, uint32_t guard_bits);
void arm_provide_guard_bits_q31(q31_t *input_buf, uint32_t blockSize, uint32_t guard_bits);
void arm_float_to_q14(float *pIn, q15_t *pOut, uint32_t numSamples);
void arm_float_to_q29(float *pIn, q31_t *pOut, uint32_t numSamples);
void arm_float_to_q28(float *pIn, q31_t *pOut, uint32_t numSamples);
void arm_float_to_q30(float *pIn, q31_t *pOut, uint32_t numSamples);
void arm_clip_f32(float *pIn, uint32_t numSamples);
uint32_t arm_calc_guard_bits(uint32_t num_adds);
void arm_apply_guard_bits (float32_t * pIn, uint32_t numSamples, uint32_t guard_bits);
uint32_t arm_compare_fixed_q15(q15_t *pIn, q15_t * pOut, uint32_t numSamples);
uint32_t arm_compare_fixed_q31(q31_t *pIn, q31_t *pOut, uint32_t numSamples);
uint32_t arm_calc_2pow(uint32_t guard_bits);
#endif

