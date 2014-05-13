/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_lms_q15.c      
*      
* Description:	Processing function for the Q15 LMS filter.      
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
 * @ingroup groupFilters      
 */     
     
/**      
 * @addtogroup LMS      
 * @{      
 */     
     
 /**      
 * @brief Processing function for Q15 LMS filter.      
 * @param[in] *S points to an instance of the Q15 LMS filter structure.      
 * @param[in] *pSrc points to the block of input data.      
 * @param[in] *pRef points to the block of reference data.      
 * @param[out] *pOut points to the block of output data.      
 * @param[out] *pErr points to the block of error data.      
 * @param[in] blockSize number of samples to process.      
 * @return none.      
 *   
 *  
 * \par Conditions for optimum performance  
 *  Input, output, state buffers should be aligned by 32-bit  
 *  
 * \par Restrictions  
 *  If the silicon does not support unaligned memory access enable the macro UNALIGNED_SUPPORT_DISABLE  
 *	In this case input, output, state buffers should be aligned by 32-bit  
 *  
 *  
 * \par Scaling and Overflow Behavior:      
 * The function is implemented using a 64-bit internal accumulator.      
 * Both coefficients and state variables are represented in 1.15 format and multiplications yield a 2.30 result.      
 * The 2.30 intermediate results are accumulated in a 64-bit accumulator in 34.30 format.      
 * There is no risk of internal overflow with this approach and the full precision of intermediate multiplications is preserved.      
 * After all additions have been performed, the accumulator is truncated to 34.15 format by discarding low 15 bits.      
 * Lastly, the accumulator is saturated to yield a result in 1.15 format.      
 *     
 * \par     
 * 	In this filter, filter coefficients are updated for each sample and the updation of filter cofficients are saturted.     
 *      
 */     
     
void arm_lms_q15(     
  const arm_lms_instance_q15 * S,     
  q15_t * pSrc,     
  q15_t * pRef,     
  q15_t * pOut,     
  q15_t * pErr,     
  uint32_t blockSize)     
{     
  q15_t *pState = S->pState;                     /* State pointer */     
  uint32_t numTaps = S->numTaps;                 /* Number of filter coefficients in the filter */     
  q15_t *pCoeffs = S->pCoeffs;                   /* Coefficient pointer */     
  q15_t *pStateCurnt;                            /* Points to the current sample of the state */     
  q15_t mu = S->mu;                              /* Adaptive factor */     
  q15_t *px;                                     /* Temporary pointer for state */     
  q15_t *pb;                                     /* Temporary pointer for coefficient buffer */     
  uint32_t tapCnt, blkCnt;                       /* Loop counters */     
  q63_t acc;                                     /* Accumulator */     
  q15_t e = 0;                                   /* error of data sample */     
  q15_t alpha;                                   /* Intermediate constant for taps update */     
  q31_t coef;                                    /* Teporary variable for coefficient */     
  q31_t x0, x1;  
  q31_t c0, c1;  
  q31_t coef0, coef1;   
  q31_t acc_l, acc_h;  
  int32_t lShift = (15 - (int32_t) S->postShift); /*  Post shift  */  
  int32_t uShift = (32 - lShift);   
  
  /* S->pState points to buffer which contains previous frame (numTaps - 1) samples */     
  /* pStateCurnt points to the location where the new input data should be written */     
  pStateCurnt = &(S->pState[(numTaps - 1u)]);     
     
  /* Initializing blkCnt with blockSize */     
  blkCnt = blockSize;     
     
  while(blkCnt > 0u)     
  {     
    /* Copy the new input sample into the state buffer */     
    *pStateCurnt++ = *pSrc++;     
     
    /* Initialize state pointer */     
    px = pState;     
     
    /* Initialize coefficient pointer */     
    pb = pCoeffs;     
     
    /* Set the accumulator to zero */     
    acc = 0;     
     
    /* Loop unrolling.  Process 4 taps at a time. */     
    tapCnt = numTaps >> 2u;     
     
    while(tapCnt > 0u)     
    {     
	  /* Read two values from state and coefficient buffers */  
	  x0 = _SIMD32_OFFSET(px);  
	  c0 = *__SIMD32(pb)++;  
  
	  /* Read next two values from state and coefficient buffers */  
	  x1 = _SIMD32_OFFSET(px + 2u);  
	  c1 = *__SIMD32(pb)++;	   
	  /* update state pointer */  
	  px += 4u;  
	        
      /* Perform the multiply-accumulate */  
      /* acc +=  b[N] * x[n-N] + b[N-1] * x[n-N-1] */     
      acc = __SMLALD(x0, c0, acc);     
      acc = __SMLALD(x1, c1, acc);     
     
      /* Decrement the loop counter */     
      tapCnt--;     
    }     
     
    /* If the filter length is not a multiple of 4, compute the remaining filter taps */     
    tapCnt = numTaps % 0x4u;     
     
    while(tapCnt > 0u)     
    {     
      /* Perform the multiply-accumulate */     
      acc += (q63_t) (((q31_t) (*px++) * (*pb++)));     
     
      /* Decrement the loop counter */     
      tapCnt--;     
    }    
	  
	  /* Calc lower part of acc */   
	  acc_l = acc & 0xffffffff;   
   
	  /* Calc upper part of acc */   
	  acc_h = (acc >> 32) & 0xffffffff;   
   
	  /* Apply shift for lower part of acc and upper part of acc */   
	  acc = (uint32_t)acc_l >> lShift | acc_h << uShift;   
     
    /* Converting the result to 1.15 format and saturate the output */     
#ifdef CCS   
    acc = __SSATA(acc, 0, 16);     
#else   
    acc = __SSAT(acc, 16);     
#endif  //	#ifdef CCS   
   
    /* Store the result from accumulator into the destination buffer. */     
    *pOut++ = (q15_t) acc;     
     
    /* Compute and store error */     
    e = *pRef++ - (q15_t) acc;     
     
    *pErr++ = (q15_t) e;     
     
    /* Compute alpha i.e. intermediate constant for taps update */     
    alpha = (q15_t) (((q31_t) e * (mu)) >> 15);     
     
    /* Initialize state pointer */     
    /* Advance state pointer by 1 for the next sample */     
    px = pState++;     
     
    /* Initialize coefficient pointer */     
    pb = pCoeffs;     
     
    /* Loop unrolling.  Process 4 taps at a time. */     
    tapCnt = numTaps >> 2u;     
     
    /* Update filter coefficients */     
    while(tapCnt > 0u)     
    {  
  
		/* *pb++ = (q31_t) *pb + (((q31_t) alpha * (*px++)) >> 15); */  
		  
		/* Read two values from state and coefficient buffers */  
	    x0 = *px;  
		x1 = *(px + 1u);  
		c0 = *pb;  
		c1 = *(pb + 1u);  
  
		/* update coefficient value */  
		/* coef0 is in 1.15 format */  
	    coef0 = (q31_t) c0 + (((q31_t) alpha * x0) >> 15);  
		coef1 = (q31_t) c1 + (((q31_t) alpha * x1) >> 15);  
  
#ifdef CCS  
	    c0 = (q15_t) __SSATA((coef0), 0, 16);  
		c1 = (q15_t) __SSATA((coef1), 0, 16);  
#else  
	    c0 = (q15_t) __SSAT((coef0), 16);  
		c1 = (q15_t) __SSAT((coef1), 16);  
#endif  
  
		/* store updated coeff values */  
		*pb = c0;  
		*(pb + 1u) = c1;  
  
		/* Read two values from state and coefficient buffers */  
		x0 = *(px + 2u);  
		x1 = *(px + 3u);  
		c0 = *(pb + 2u);  
		c1 = *(pb + 3u);  
  
		/* update coefficient value */  
		/* coef0 is in 1.15 format */  
	    coef0 = (q31_t) c0 + (((q31_t) alpha * x0) >> 15);  
		coef1 = (q31_t) c1 + (((q31_t) alpha * x1) >> 15);  
  
#ifdef CCS  
	    c0 = (q15_t) __SSATA((coef0), 0, 16);  
		c1 = (q15_t) __SSATA((coef1), 0, 16);  
#else  
	    c0 = (q15_t) __SSAT((coef0), 16);  
		c1 = (q15_t) __SSAT((coef1), 16);  
#endif  
  
		/* store updated coeff values */  
     	*(pb + 2u) = c0;  
		*(pb + 3u) = c1;  
  
		/* update pointers */  
		 px += 4u;  
		 pb += 4u;  
     
      /* Decrement the loop counter */     
      tapCnt--;     
    }     
     
    /* If the filter length is not a multiple of 4, compute the remaining filter taps */     
    tapCnt = numTaps % 0x4u;     
     
    while(tapCnt > 0u)     
    {     
      /* Perform the multiply-accumulate */     
      coef = (q31_t) *pb + (((q31_t) alpha * (*px++)) >> 15);   
	      
#ifdef CCS   
      *pb++ = (q15_t) __SSATA((coef), 0, 16);     
#else   
      *pb++ = (q15_t) __SSAT((coef), 16);     
#endif   
     
      /* Decrement the loop counter */     
      tapCnt--;     
    }     
     
    /* Decrement the loop counter */     
    blkCnt--;     
     
  }     
     
  /* Processing is complete. Now copy the last numTaps - 1 samples to the      
     satrt of the state buffer. This prepares the state buffer for the      
     next function call. */     
     
  /* Points to the start of the pState buffer */     
  pStateCurnt = S->pState;     
     
  /* Calculation of count for copying integer writes */     
  tapCnt = (numTaps - 1u) >> 2;     
     
  while(tapCnt > 0u)     
  {     
  
#ifndef UNALIGNED_SUPPORT_DISABLE  
     
    *__SIMD32(pStateCurnt)++ = *__SIMD32(pState)++;     
    *__SIMD32(pStateCurnt)++ = *__SIMD32(pState)++;   
  
#else  
	 *pStateCurnt++ = *pState++;  
	 *pStateCurnt++ = *pState++;  
	 *pStateCurnt++ = *pState++;  
	 *pStateCurnt++ = *pState++;  
#endif	    
     
    tapCnt--;     
     
  }     
     
  /* Calculation of count for remaining q15_t data */     
  tapCnt = (numTaps - 1u) % 0x4u;     
     
  /* copy data */     
  while(tapCnt > 0u)     
  {     
    *pStateCurnt++ = *pState++;     
     
    /* Decrement the loop counter */     
    tapCnt--;     
  }     
     
}     
     
/**      
   * @} end of LMS group      
   */     
