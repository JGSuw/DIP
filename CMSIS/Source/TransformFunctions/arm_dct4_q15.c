/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_dct4_q15.c      
*      
* Description:	Processing function of DCT4 & IDCT4 Q15.      
*      
* Target Processor:          Cortex-R4/R5
*
* Version 1.0.0 2011/03/08
*     Alpha release.
*
* Version 1.0.1 2011/09/30
*     Beta release.
*
* Version 2.0.0 2011/12/15
*     Final release. 
* 
* -------------------------------------------------------------------- */     
#include "arm_math.h"     
     
/**      
 * @addtogroup DCT4_IDCT4      
 * @{      
 */     
     
/**      
 * @brief Processing function for the Q15 DCT4/IDCT4.     
 * @param[in]       *S             points to an instance of the Q15 DCT4 structure.     
 * @param[in]       *pState        points to state buffer.     
 * @param[in,out]   *pInlineBuffer points to the in-place input and output buffer.     
 * @return none.     
 *       
 * \par Input an output formats:      
 * Internally inputs are downscaled in the RFFT process function to avoid overflows.      
 * Number of bits downscaled, depends on the size of the transform.      
 * The input and output formats for different DCT sizes and number of bits to upscale are mentioned in the table below:       
 *      
 * \image html dct4FormatsQ15Table.gif      
 */     
     
void arm_dct4_q15(     
  const arm_dct4_instance_q15 * S,     
  q15_t * pState,     
  q15_t * pInlineBuffer)     
{     
  uint32_t i;                                    /* Loop counter */     
  q15_t *weights = S->pTwiddle;                  /* Pointer to the Weights table */     
  q15_t *cosFact = S->pCosFactor;                /* Pointer to the cos factors table */     
  q15_t *pS1, *pS2, *pbuff;                      /* Temporary pointers for input buffer and pState buffer */     
  q15_t in;                                      /* Temporary variable */     
  q31_t in1, in2, in3, in4;  
  q15_t i1, i2, i3, i4;  
     
     
  /* DCT4 computation involves DCT2 (which is calculated using RFFT)      
   * along with some pre-processing and post-processing.      
   * Computational procedure is explained as follows:      
   * (a) Pre-processing involves multiplying input with cos factor,      
   *     r(n) = 2 * u(n) * cos(pi*(2*n+1)/(4*n))      
   *              where,      
   *                 r(n) -- output of preprocessing      
   *                 u(n) -- input to preprocessing(actual Source buffer)      
   * (b) Calculation of DCT2 using FFT is divided into three steps:      
   *                  Step1: Re-ordering of even and odd elements of input.      
   *                  Step2: Calculating FFT of the re-ordered input.      
   *                  Step3: Taking the real part of the product of FFT output and weights.      
   * (c) Post-processing - DCT4 can be obtained from DCT2 output using the following equation:      
   *                   Y4(k) = Y2(k) - Y4(k-1) and Y4(-1) = Y4(0)      
   *                        where,      
   *                           Y4 -- DCT4 output,   Y2 -- DCT2 output      
   * (d) Multiplying the output with the normalizing factor sqrt(2/N).      
   */     
     
        /*-------- Pre-processing ------------*/     
  /* Multiplying input with cos factor i.e. r(n) = 2 * x(n) * cos(pi*(2*n+1)/(4*n)) */     
  arm_mult_q15(pInlineBuffer, cosFact, pInlineBuffer, S->N);     
  arm_shift_q15(pInlineBuffer, 1, pInlineBuffer, S->N);     
     
  /* ----------------------------------------------------------------      
   * Step1: Re-ordering of even and odd elements as      
   *             pState[i] =  pInlineBuffer[2*i] and      
   *             pState[N-i-1] = pInlineBuffer[2*i+1] where i = 0 to N/2      
   ---------------------------------------------------------------------*/     
     
  /* pS1 initialized to pState */     
  pS1 = pState;     
     
  /* pS2 initialized to pState+N-1, so that it points to the end of the state buffer */     
  pS2 = pState + (S->N - 1u);     
     
  /* pbuff initialized to input buffer */     
  pbuff = pInlineBuffer;     
     
  /* Initializing the loop counter to N/2 >> 2 for loop unrolling by 4 */     
  i = (uint32_t) S->Nby2 >> 2u;     
     
  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.      
   ** a second loop below computes the remaining 1 to 3 samples. */     
  do     
  {     
    /* Re-ordering of even and odd elements */     
	pS2 -= 4u;  
    /* pState[i] =  pInlineBuffer[2*i] */   
     /* pState[N-i-1] = pInlineBuffer[2*i+1] */     
	in1 = *__SIMD32(pbuff)++;  
	in2 = *__SIMD32(pbuff)++;  
  
	pS2[4] = (q15_t)in1;  
  
	in3 = *__SIMD32(pbuff)++;  
  
#ifndef ARM_MATH_BIG_ENDIAN  
  
	in1 = __PKHTB(in2, in1, 16);  
  
#else  
  
	in1 = __PKHTB(in1, in2, 16);  
  
#endif	//		#ifndef ARM_MATH_BIG_ENDIAN  
  
	in4 = *__SIMD32(pbuff)++;  
  
	pS2[3] = (q15_t)in2;  
  
#ifndef ARM_MATH_BIG_ENDIAN  
  
	in2 = __PKHTB(in4, in3, 16);  
  
#else  
  
	in2 = __PKHTB(in3, in4, 16);  
  
#endif	//		#ifndef ARM_MATH_BIG_ENDIAN  
  
	pS2[2] = (q15_t)in3;  
  
	*__SIMD32(pS1)++ = in1;  
  
	pS2[1] = (q15_t)in4;  
  
	*__SIMD32(pS1)++ = in2;  
  
    /* Decrement the loop counter */     
    i--;     
  } while(i > 0u);     
     
  /* pbuff initialized to input buffer */     
  pbuff = pInlineBuffer;     
     
  /* pS1 initialized to pState */     
  pS1 = pState;     
     
  /* Initializing the loop counter to N/4 instead of N for loop unrolling */     
  i = (uint32_t) S->N >> 2u;     
     
  /* Processing with loop unrolling 4 times as N is always multiple of 4.      
   * Compute 4 outputs at a time */     
  do     
  {     
    /* Writing the re-ordered output back to inplace input buffer */     
	in1 = *__SIMD32(pS1)++;  
	in2 = *__SIMD32(pS1)++;  
	*__SIMD32(pbuff)++ = in1;  
	*__SIMD32(pbuff)++ = in2;   
     
    /* Decrement the loop counter */     
    i--;     
  } while(i > 0u);     
     
     
  /* ---------------------------------------------------------      
   *     Step2: Calculate RFFT for N-point input      
   * ---------------------------------------------------------- */     
  /* pInlineBuffer is real input of length N , pState is the complex output of length 2N */     
  arm_rfft_q15(S->pRfft, pInlineBuffer, pState);     
     
 /*----------------------------------------------------------------------      
  *  Step3: Multiply the FFT output with the weights.      
  *----------------------------------------------------------------------*/     
  arm_cmplx_mult_cmplx_q15(pState, weights, pState, S->N);     
     
  /* The output of complex multiplication is in 3.13 format.      
   * Hence changing the format of N (i.e. 2*N elements) complex numbers to 1.15 format by shifting left by 2 bits. */     
  arm_shift_q15(pState, 2, pState, S->N * 2);     
     
  /* ----------- Post-processing ---------- */     
  /* DCT-IV can be obtained from DCT-II by the equation,      
   *       Y4(k) = Y2(k) - Y4(k-1) and Y4(-1) = Y4(0)      
   *       Hence, Y4(0) = Y2(0)/2  */     
  /* Getting only real part from the output and Converting to DCT-IV */     
     
  /* Initializing the loop counter to N >> 2 for loop unrolling by 4 */     
  i = ((uint32_t) S->N - 1u) >> 2u;     
     
  /* pbuff initialized to input buffer. */     
  pbuff = pInlineBuffer;     
     
  /* pS1 initialized to pState */     
  pS1 = pState;     
     
  /* Calculating Y4(0) from Y2(0) using Y4(0) = Y2(0)/2 */     
  in = *pS1++ >> 1u;     
  /* input buffer acts as inplace, so output values are stored in the input itself. */     
  *pbuff++ = in;     
     
  /* pState pointer is incremented twice as the real values are located alternatively in the array */     
  pS1++;     
     
  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.      
   ** a second loop below computes the remaining 1 to 3 samples. */     
  do     
  {     
    /* Calculating Y4(1) to Y4(N-1) from Y2 using equation Y4(k) = Y2(k) - Y4(k-1) */     
    /* pState pointer (pS1) is incremented twice as the real values are located alternatively in the array */     
	i1 = pS1[0];  
	i2 = pS1[2];  
	i3 = pS1[4];  
	i4 = pS1[6];  
  
	i1 = i1 - in;  
	i2 = i2 - i1;  
	i3 = i3 - i2;  
	in = i4 - i3;  
  
	*pbuff++ = i1;  
	*pbuff++ = i2;  
	*pbuff++ = i3;  
	*pbuff++ = in;  
  
	pS1 += 8u;  
     
    /* Decrement the loop counter */     
    i--;     
  } while(i > 0u);     
     
  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  i = ((uint32_t) S->N - 1u) % 0x4u;     
     
  while(i > 0u)     
  {     
    /* Calculating Y4(1) to Y4(N-1) from Y2 using equation Y4(k) = Y2(k) - Y4(k-1) */     
    /* pState pointer (pS1) is incremented twice as the real values are located alternatively in the array */     
    in = *pS1++ - in;     
    *pbuff++ = in;     
    /* points to the next real value */     
    pS1++;     
     
    /* Decrement the loop counter */     
    i--;     
  }     
     
     
   /*------------ Normalizing the output by multiplying with the normalizing factor ----------*/     
     
  /* Initializing the loop counter to N/4 instead of N for loop unrolling */     
  i = (uint32_t) S->N >> 2u;     
     
  /* pbuff initialized to the pInlineBuffer(now contains the output values) */     
  pbuff = pInlineBuffer;     
     
  /* Processing with loop unrolling 4 times as N is always multiple of 4.  Compute 4 outputs at a time */     
  do     
  {     
    /* Multiplying pInlineBuffer with the normalizing factor sqrt(2/N) */     
	i1 = pbuff[0];  
	i2 = pbuff[1];  
	i3 = pbuff[2];  
	i4 = pbuff[3];  
	  
	i1 = ((q15_t)(((q31_t) i1 * S->normalize) >> 15));    
	i2 = ((q15_t)(((q31_t) i2 * S->normalize) >> 15));    
	i3 = ((q15_t)(((q31_t) i3 * S->normalize) >> 15));    
	i4 = ((q15_t)(((q31_t) i4 * S->normalize) >> 15));    
  
	pbuff[0] = i1;  
	pbuff[1] = i2;  
	pbuff[2] = i3;  
	pbuff[3] = i4;  
  
	pbuff += 4u;  
  
    /* Decrement the loop counter */     
    i--;     
  } while(i > 0u);     
     
}     
     
/**      
   * @} end of DCT4_IDCT4 group      
   */     
