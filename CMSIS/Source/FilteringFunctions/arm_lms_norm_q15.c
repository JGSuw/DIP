/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_lms_norm_q15.c      
*      
* Description:	Q15 NLMS filter.      
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
 * @addtogroup LMS_NORM      
 * @{      
 */     
     
/**      
* @brief Processing function for Q15 normalized LMS filter.      
* @param[in] *S points to an instance of the Q15 normalized LMS filter structure.      
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
* <b>Scaling and Overflow Behavior:</b>      
* \par      
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
     
void arm_lms_norm_q15(     
  arm_lms_norm_instance_q15 * S,     
  q15_t * pSrc,     
  q15_t * pRef,     
  q15_t * pOut,     
  q15_t * pErr,     
  uint32_t blockSize)     
{     
  q15_t *pState = S->pState;                     /* State pointer */     
  q15_t *pCoeffs = S->pCoeffs;                   /* Coefficient pointer */     
  q15_t *pStateCurnt;                            /* Points to the current sample of the state */     
  q15_t *px, *pb;                                /* Temporary pointers for state and coefficient buffers */     
  q15_t mu = S->mu;                              /* Adaptive factor */     
  uint32_t numTaps = S->numTaps;                 /* Number of filter coefficients in the filter */     
  uint32_t tapCnt, blkCnt;                       /* Loop counters */     
  q31_t energy;                                  /* Energy of the input */     
  q63_t acc;                                     /* Accumulator */     
  q15_t e = 0, d = 0;                            /* error, reference data sample */     
  q15_t w = 0, in;                               /* weight factor and state */     
  q15_t x0;                                      /* temporary variable to hold input sample */     
  q15_t errorXmu, oneByEnergy;                   /* Temporary variables to store error and mu product and reciprocal of energy */     
  q15_t postShift;                               /* Post shift to be applied to weight after reciprocal calculation */     
  q31_t coef;                                    /* Teporary variable for coefficient */     
  q31_t x1, x2;  
  q31_t c0, c1;  
  q31_t coef0, coef1;    
  q31_t acc_l, acc_h;  
  int32_t lShift = (15 - (int32_t) S->postShift); /*  Post shift  */  
  int32_t uShift = (32 - lShift);   
  
  energy = S->energy;     
  x0 = S->x0;     
     
  /* S->pState points to buffer which contains previous frame (numTaps - 1) samples */     
  /* pStateCurnt points to the location where the new input data should be written */     
  pStateCurnt = &(S->pState[(numTaps - 1u)]);     
     
  /* Initializing blkCnt with blockSize */     
  blkCnt = blockSize;     
     
  while(blkCnt > 0u)     
  {     
    /* Copy the new input sample into the state buffer */     
    *pStateCurnt++ = *pSrc;     
     
    /* Initialize pState pointer */     
    px = pState;     
     
    /* Initialize coeff pointer */     
    pb = (pCoeffs);     
     
    /* Read the sample from input buffer */     
    in = *pSrc++;     
     
    /* Update the energy calculation */     
    energy -= (((q31_t) x0 * (x0)) >> 15);     
    energy += (((q31_t) in * (in)) >> 15);     
     
    /* Set the accumulator to zero */     
    acc = 0;     
     
    /* Loop unrolling.  Process 4 taps at a time. */     
    tapCnt = numTaps >> 2;     
     
    while(tapCnt > 0u)     
    {     
	  /* Read two values from state and coefficient buffers */  
	  x1 = _SIMD32_OFFSET(px);  
	  c0 = *__SIMD32(pb)++;  
  
	  /* Read next two values from state and coefficient buffers */  
	  x2 = _SIMD32_OFFSET(px + 2u);  
	  c1 = *__SIMD32(pb)++;	   
	  /* update state pointer */  
	  px += 4u;  
	        
      /* Perform the multiply-accumulate */  
      /* acc +=  b[N] * x[n-N] + b[N-1] * x[n-N-1] */     
      acc = __SMLALD(x1, c0, acc);     
      acc = __SMLALD(x2, c1, acc);      
     
      /* Decrement the loop counter */     
      tapCnt--;     
    }     
     
    /* If the filter length is not a multiple of 4, compute the remaining filter taps */     
    tapCnt = numTaps % 0x4u;     
     
    while(tapCnt > 0u)     
    {     
      /* Perform the multiply-accumulate */     
      acc += (((q31_t) * px++ * (*pb++)));     
     
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
    acc = __SSATA(acc, 0, 16u);     
#else   
    acc = __SSAT(acc, 16u);     
#endif   
   
    /* Store the result from accumulator into the destination buffer. */     
    *pOut++ = (q15_t) acc;     
     
    /* Compute and store error */     
    d = *pRef++;     
    e = d - (q15_t) acc;     
    *pErr++ = e;     
     
    /* Calculation of 1/energy */     
    postShift = arm_recip_q15((q15_t) energy + DELTA_Q15,     
                              &oneByEnergy, S->recipTable);     
     
    /* Calculation of e * mu value */     
    errorXmu = (q15_t) (((q31_t) e * mu) >> 15);     
     
    /* Calculation of (e * mu) * (1/energy) value */     
    acc = (((q31_t) errorXmu * oneByEnergy) >> (15 - postShift));     
     
    /* Weighting factor for the normalized version */     
#ifdef CCS   
    w = (q15_t) __SSATA((q31_t) acc, 0, 16);     
#else   
    w = (q15_t) __SSAT((q31_t) acc, 16);     
#endif     
    /* Initialize pState pointer */     
    px = pState;     
     
    /* Initialize coeff pointer */     
    pb = (pCoeffs);     
     
    /* Loop unrolling.  Process 4 taps at a time. */     
    tapCnt = numTaps >> 2;     
     
    /* Update filter coefficients */     
    while(tapCnt > 0u)     
    {     
  
		/* *pb++ = (q31_t) *pb + (((q31_t) w * (*px++)) >> 15); */  
		  
		/* Read two values from state and coefficient buffers */  
	    x1 = *px;  
		x2 = *(px + 1u);  
		c0 = *pb;  
		c1 = *(pb + 1u);  
  
		/* update coefficient value */  
		/* coef0 is in 1.15 format */  
	    coef0 = (q31_t) c0 + (((q31_t) w * x1) >> 15);  
		coef1 = (q31_t) c1 + (((q31_t) w * x2) >> 15);  
  
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
		x1 = *(px + 2u);  
		x2 = *(px + 3u);  
		c0 = *(pb + 2u);  
		c1 = *(pb + 3u);  
  
		/* update coefficient value */  
		/* coef0 is in 1.15 format */  
	    coef0 = (q31_t) c0 + (((q31_t) w * x1) >> 15);  
		coef1 = (q31_t) c1 + (((q31_t) w * x2) >> 15);  
  
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
      coef = *pb + (((q31_t) w * (*px++)) >> 15);  
	       
#ifdef CCS     
      *pb++ = (q15_t) __SSATA((coef), 0, 16);     
#else   
      *pb++ = (q15_t) __SSAT((coef), 16);     
#endif	     
     
      /* Decrement the loop counter */     
      tapCnt--;     
    }     
     
    /* Read the sample from state buffer */     
    x0 = *pState;     
     
    /* Advance state pointer by 1 for the next sample */     
    pState = pState + 1u;     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* Save energy and x0 values for the next frame */     
  S->energy = (q15_t) energy;     
  S->x0 = x0;     
     
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
   * @} end of LMS_NORM group      
   */     
