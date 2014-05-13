/*-----------------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_fir_interpolate_q15.c      
*      
* Description:	Q15 FIR interpolation.      
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
* ---------------------------------------------------------------------------*/     
#include "arm_math.h"     
     
/**      
 * @ingroup groupFilters      
 */     
     
/**      
 * @addtogroup FIR_Interpolate      
 * @{      
 */     
     
/**      
 * @brief Processing function for the Q15 FIR interpolator.      
 * @param[in] *S        points to an instance of the Q15 FIR interpolator structure.      
 * @param[in] *pSrc     points to the block of input data.      
 * @param[out] *pDst    points to the block of output data.      
 * @param[in] blockSize number of input samples to process per call.      
 * @return none.      
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function is implemented using a 64-bit internal accumulator.      
 * Both coefficients and state variables are represented in 1.15 format and multiplications yield a 2.30 result.      
 * The 2.30 intermediate results are accumulated in a 64-bit accumulator in 34.30 format.      
 * There is no risk of internal overflow with this approach and the full precision of intermediate multiplications is preserved.      
 * After all additions have been performed, the accumulator is truncated to 34.15 format by discarding low 15 bits.      
 * Lastly, the accumulator is saturated to yield a result in 1.15 format.      
 */   
  
    
void arm_fir_interpolate_q15(     
  const arm_fir_interpolate_instance_q15 * S,     
  q15_t * pSrc,     
  q15_t * pDst,     
  uint32_t blockSize)     
{     
  q15_t *pState = S->pState;                     /* State pointer                                            */     
  q15_t *pCoeffs = S->pCoeffs;                   /* Coefficient pointer                                      */     
  q15_t *pStateCurnt;                            /* Points to the current sample of the state                */     
  q15_t *ptr1, *ptr2;                            /* Temporary pointers for state and coefficient buffers     */     
  q63_t sum0;                                    /* Accumulators                                             */     
  q15_t x0, c0;                              /* Temporary variables to hold state and coefficient values */     
  uint32_t i, blkCnt, j, tapCnt;                 /* Loop counters                                            */     
  uint16_t phaseLen = S->phaseLength;            /* Length of each polyphase filter component */     
  uint32_t blkCntN2;  
  q63_t acc0, acc1;   
  q15_t x1;  
     
  /* S->pState buffer contains previous frame (phaseLen - 1) samples */     
  /* pStateCurnt points to the location where the new input data should be written */     
  pStateCurnt = S->pState + ((q31_t) phaseLen - 1);     
  
  /* Initialise  blkCnt */  
  blkCnt = blockSize / 2;  
  blkCntN2 = blockSize - (2*blkCnt);      
     
  /* Samples loop unrolled by 2 */     
  while(blkCnt > 0u)     
  {     
    /* Copy new input sample into the state buffer */     
    *pStateCurnt++ = *pSrc++;  
	*pStateCurnt++ = *pSrc++;  
    
    /* Address modifier index of coefficient buffer */     
    j = 1u;     
     
    /* Loop over the Interpolation factor. */     
    i = (S->L);  
	     
    while(i > 0u)     
    {     
      /* Set accumulator to zero */     
      acc0 = 0;     
	  acc1 = 0;  
     
      /* Initialize state pointer */     
      ptr1 = pState;     
     
      /* Initialize coefficient pointer */     
      ptr2 = pCoeffs + (S->L - j);     
     
      /* Loop over the polyPhase length. Unroll by a factor of 4.      
       ** Repeat until we've computed numTaps-(4*S->L) coefficients. */     
      tapCnt = phaseLen >> 2u;  
	      
	  x0 = *(ptr1++);  
  
      while(tapCnt > 0u)     
      {  
	    
 		/* Read the input sample */     
		x1 = *(ptr1++);  
  
		/* Read the coefficient */     
		c0 = *(ptr2);  
  
		/* Perform the multiply-accumulate */     
		acc0 += (q63_t)x0 * c0;     
		acc1 += (q63_t)x1 * c0;     
  
  
		/* Read the coefficient */  
		c0 = *(ptr2 + S->L);  
		  
        /* Read the input sample */     
		x0 = *(ptr1++);  
  
		/* Perform the multiply-accumulate */     
		acc0 += (q63_t)x1 * c0;     
		acc1 += (q63_t)x0 * c0;     
		  
		     
		/* Read the coefficient */		     
		c0 = *(ptr2 + S->L * 2);  
  
		/* Read the input sample */     
		x1 = *(ptr1++);  
  
	    /* Perform the multiply-accumulate */     
		acc0 += (q63_t)x0 * c0;     
		acc1 += (q63_t)x1 * c0;     
  
		/* Read the coefficient */  
		c0 = *(ptr2 + S->L * 3);  
  
	    /* Read the input sample */     
		x0 = *(ptr1++);  
  
	    /* Perform the multiply-accumulate */     
		acc0 += (q63_t)x1 * c0;     
		acc1 += (q63_t)x0 * c0;     
  
  
		/* Upsampling is done by stuffing L-1 zeros between each sample.      
		* So instead of multiplying zeros with coefficients,      
		* Increment the coefficient pointer by interpolation factor times. */     
		ptr2 +=  4 * S->L;          
     
        /* Decrement the loop counter */     
        tapCnt--;     
      }     
     
      /* If the polyPhase length is not a multiple of 4, compute the remaining filter taps */     
      tapCnt = phaseLen % 0x4u;     
     
      while(tapCnt > 0u)     
      {  
  
	    /* Read the input sample */   
		x1 = *(ptr1++);  
  
		/* Read the coefficient */		  
		c0 = *(ptr2);  
	    
        /* Perform the multiply-accumulate */     
		acc0 += (q63_t)x0 * c0;     
		acc1 += (q63_t)x1 * c0;    
		  
        /* Increment the coefficient pointer by interpolation factor times. */     
		ptr2 += S->L;  
		  
		/* update states for next sample processing */  
		x0 = x1;  
     
        /* Decrement the loop counter */     
        tapCnt--;     
      }     
     
      /* The result is in the accumulator, store in the destination buffer. */     
#ifdef CCS  
//	*pDst = (q15_t) __SSATA(acc0, 15, 16);  
//	*(pDst + S->L)  = (q15_t) __SSATA(acc1, 15, 16);  
	*pDst = (q15_t) __SSATA((acc0 >> 15), 0, 16);  		  //JMM August 15 2012
	*(pDst + S->L)  = (q15_t) __SSATA((acc1 >> 15), 0, 16);   //JMM August 15 2012
#else  
      *pDst = (q15_t) (__SSAT((acc0 >> 15), 16));  
	  *(pDst + S->L)  = (q15_t) (__SSAT((acc1 >> 15), 16));  
#endif	    
	  pDst++;   
     
      /* Increment the address modifier index of coefficient buffer */     
      j++;     
     
      /* Decrement the loop counter */     
      i--;     
    }     
     
    /* Advance the state pointer by 1      
     * to process the next group of interpolation factor number samples */     
    pState = pState + 2;   
	  
	pDst += S->L;    
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
  
  /* If the blockSize is not a multiple of 2, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blkCntN2;     
     
  /* Loop over the blockSize. */     
  while(blkCnt > 0u)     
  {     
    /* Copy new input sample into the state buffer */     
    *pStateCurnt++ = *pSrc++;     
     
    /* Address modifier index of coefficient buffer */     
    j = 1u;     
     
    /* Loop over the Interpolation factor. */     
    i = S->L;     
    while(i > 0u)     
    {     
      /* Set accumulator to zero */     
      sum0 = 0;     
     
      /* Initialize state pointer */     
      ptr1 = pState;     
     
      /* Initialize coefficient pointer */     
      ptr2 = pCoeffs + (S->L - j);     
     
      /* Loop over the polyPhase length. Unroll by a factor of 4.      
       ** Repeat until we've computed numTaps-(4*S->L) coefficients. */     
      tapCnt = phaseLen >> 2;     
      while(tapCnt > 0u)     
      {     
     
        /* Read the coefficient */     
        c0 = *(ptr2);     
     
        /* Upsampling is done by stuffing L-1 zeros between each sample.      
         * So instead of multiplying zeros with coefficients,      
         * Increment the coefficient pointer by interpolation factor times. */     
        ptr2 += S->L;     
     
        /* Read the input sample */     
        x0 = *(ptr1++);     
     
        /* Perform the multiply-accumulate */     
        sum0 += (q63_t) x0 *c0;     
     
        /* Read the coefficient */     
        c0 = *(ptr2);     
     
        /* Increment the coefficient pointer by interpolation factor times. */     
        ptr2 += S->L;     
     
        /* Read the input sample */     
        x0 = *(ptr1++);     
     
        /* Perform the multiply-accumulate */     
        sum0 += (q63_t) x0 *c0;     
     
        /* Read the coefficient */     
        c0 = *(ptr2);     
     
        /* Increment the coefficient pointer by interpolation factor times. */     
        ptr2 += S->L;     
     
        /* Read the input sample */     
        x0 = *(ptr1++);     
     
        /* Perform the multiply-accumulate */     
        sum0 += (q63_t) x0 *c0;     
     
        /* Read the coefficient */     
        c0 = *(ptr2);     
     
        /* Increment the coefficient pointer by interpolation factor times. */     
        ptr2 += S->L;     
     
        /* Read the input sample */     
        x0 = *(ptr1++);     
     
        /* Perform the multiply-accumulate */     
        sum0 += (q63_t) x0 *c0;     
     
        /* Decrement the loop counter */     
        tapCnt--;     
      }     
     
      /* If the polyPhase length is not a multiple of 4, compute the remaining filter taps */     
      tapCnt = phaseLen & 0x3u;     
     
      while(tapCnt > 0u)     
      {     
        /* Read the coefficient */     
        c0 = *(ptr2);     
     
        /* Increment the coefficient pointer by interpolation factor times. */     
        ptr2 += S->L;     
     
        /* Read the input sample */     
        x0 = *(ptr1++);     
     
        /* Perform the multiply-accumulate */     
        sum0 += (q63_t) x0 *c0;     
     
        /* Decrement the loop counter */     
        tapCnt--;     
      }     
     
      /* The result is in the accumulator, store in the destination buffer. */     
#ifdef CCS  
  
//    *pDst++ = (q15_t) (__SSATA(sum0, 15, 16));     
    *pDst++ = (q15_t) (__SSATA((sum0 >> 15), 0, 16)); //JMM August 15 2012    
     
#else  
  
    *pDst++ = (q15_t) (__SSAT((sum0 >> 15), 16));     
     
#endif      /* Increment the address modifier index of coefficient buffer */     
      j++;     
     
      /* Decrement the loop counter */     
      i--;     
    }     
     
    /* Advance the state pointer by 1      
     * to process the next group of interpolation factor number samples */     
    pState = pState + 1;     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* Processing is complete.      
   ** Now copy the last phaseLen - 1 samples to the satrt of the state buffer.      
   ** This prepares the state buffer for the next function call. */     
     
  /* Points to the start of the state buffer */     
  pStateCurnt = S->pState;     
     
  tapCnt = (phaseLen - 1u) >> 2u;     
     
  /* copy data */     
  while(tapCnt > 0u)     
  {     
    *pStateCurnt++ = *pState++;     
    *pStateCurnt++ = *pState++;     
    *pStateCurnt++ = *pState++;     
    *pStateCurnt++ = *pState++;     
     
    /* Decrement the loop counter */     
    tapCnt--;     
  }     
     
  tapCnt = (phaseLen - 1u) % 0x04u;     
     
  /* copy data */     
  while(tapCnt > 0u)     
  {     
    *pStateCurnt++ = *pState++;     
     
    /* Decrement the loop counter */     
    tapCnt--;     
  }   
     
}   
  
     
 /**      
  * @} end of FIR_Interpolate group      
  */     
