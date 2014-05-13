/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:        arm_fir_q7.c      
*      
* Description:  Q7 FIR filter processing function.      
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
 * @addtogroup FIR      
 * @{      
 */   
   
/**      
 * @param[in]   *S points to an instance of the Q7 FIR filter structure.      
 * @param[in]   *pSrc points to the block of input data.      
 * @param[out]  *pDst points to the block of output data.      
 * @param[in]   blockSize number of samples to process per call.      
 * @return 	none.      
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function is implemented using a 32-bit internal accumulator.      
 * Both coefficients and state variables are represented in 1.7 format and multiplications yield a 2.14 result.      
 * The 2.14 intermediate results are accumulated in a 32-bit accumulator in 18.14 format.      
 * There is no risk of internal overflow with this approach and the full precision of intermediate multiplications is preserved.      
 * The accumulator is converted to 18.7 format by discarding the low 7 bits.      
 * Finally, the result is truncated to 1.7 format.      
 */   
   
void arm_fir_q7(   
  const arm_fir_instance_q7 * S,   
  q7_t * pSrc,   
  q7_t * pDst,   
  uint32_t blockSize)   
{   
  uint32_t numTaps = S->numTaps;                 /* Number of taps in the filter */   
  uint32_t tapCnt, blkCnt, i;                    /* Loop counters */   
  q7_t *pState = S->pState;                      /* State pointer */   
  q7_t *pCoeffs = S->pCoeffs;                    /* Coefficient pointer */   
  q7_t *px7, *pb7;                                 /* Temporary pointers to state and coeff */   
  q7_t *pStateCurnt;                             /* Points to the current sample of the state */   
  q31_t x20, b20, x31, b31, xin1, xin2;  
  q31_t  acc0, acc1, acc2, acc3; 			   	/* Accumlators */  
  q31_t x0;  
  q7_t x1, x2, x3, x4, c0;  
  
  /* S->pState points to state array which contains previous frame (numTaps - 1) samples */   
  /* pStateCurnt points to the location where the new input data should be written */   
  pStateCurnt = S->pState + (numTaps - 1u);   
   
  /* Apply loop unrolling and compute 4 output values simultaneously.      
   * The variables acc0 ... acc3 hold output values that are being computed:      
   *      
   *    acc0 =  b[numTaps-1] * x[n-numTaps-1] + b[numTaps-2] * x[n-numTaps-2] + b[numTaps-3] * x[n-numTaps-3] +...+ b[0] * x[0]      
   *    acc1 =  b[numTaps-1] * x[n-numTaps] +   b[numTaps-2] * x[n-numTaps-1] + b[numTaps-3] * x[n-numTaps-2] +...+ b[0] * x[1]      
   *    acc2 =  b[numTaps-1] * x[n-numTaps+1] + b[numTaps-2] * x[n-numTaps] +   b[numTaps-3] * x[n-numTaps-1] +...+ b[0] * x[2]      
   *    acc3 =  b[numTaps-1] * x[n-numTaps+2] + b[numTaps-2] * x[n-numTaps+1] + b[numTaps-3] * x[n-numTaps]   +...+ b[0] * x[3]      
   */   
  blkCnt = blockSize >> 2;   
   
  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.      
   ** a second loop below computes the remaining 1 to 3 samples. */   
  while(blkCnt > 0u)   
  {   
    /* Copy four new input samples into the state buffer */   
    *pStateCurnt++ = *pSrc++;  
	*pStateCurnt++ = *pSrc++;  
	*pStateCurnt++ = *pSrc++;  
	*pStateCurnt++ = *pSrc++;  
  
     /* Set all accumulators to zero */   
    acc0 = 0;   
    acc1 = 0;   
    acc2 = 0;   
    acc3 = 0;    
   
    /* Initialize state pointer of type q31_t with pointer of type q7_t   
	 * for reading four samples at a time */   
    px7 = pState;   
   
    /* Initialize coefficient pointer of type q31_t with pointer of type q7_t   
	 * for reading four samples at a time */  
    pb7 = pCoeffs;   
  
    /* Read the first four samples from the state buffer:      
     *  x[n-numTaps + 1], x[n-numTaps], x[n-numTaps-1], x[n-numTaps-2]  */   
	xin1 = *__SIMD32(px7)++;     
  
	/* Calculation of loop count */	  
    tapCnt = numTaps >> 2u;   
  
	/* Initialise loop count */  
	i = tapCnt;  
   
    /* Loop over the number of taps.  Unroll by a factor of 4.    
     ** Repeat until we've computed numTaps-4 coefficients. */   
    while(i > 0u)   
    {   
    /* Read the next four samples from the state buffer:      
     *  x[n-numTaps-3], x[n-numTaps-4], x[n-numTaps-5], x[n-numTaps-6]  */         
	  xin2 = *__SIMD32(px7)++;  
  
      /* Read the b[numTaps - 1], b[numTaps - 2], b[numTaps - 3], b[numTaps - 4]  coefficients */   
      b20 = *__SIMD32(pb7)++;;    
  
#ifdef CCS  
  
	  /* Extract x[n-numTaps],  x[n-numTaps-2] */  
	  x20 = __SXTB16(xin1, 0);  
  
	  /* Extract x[n-numTaps + 1],  x[n-numTaps- 1] */  
	  x31 = __SXTB16(xin1, 8);  
  
	  /* Extract the b[numTaps - 1],  b[numTaps - 3]  coefficients */   
	  b31 = __SXTB16(b20, 8);	    
  
	  /* Read the  b[numTaps - 2], b[numTaps - 4]  coefficients */   
	  b20 = __SXTB16(b20, 0);  
  
#else  
  
	  /* Extract x[n-numTaps],  x[n-numTaps-2] */  
	  x20 = __SXTB16(xin1);  
  
	  /* Extract x[n-numTaps + 1],  x[n-numTaps- 1] */  
	  x31 = __SXTB16(__ROR(xin1, 8));  
  
	  /* Extract the b[numTaps - 1],  b[numTaps - 3]  coefficients */   
	  b31 = __SXTB16(__ROR(b20, 8));	    
  
	  /* Read the  b[numTaps - 2], b[numTaps - 4]  coefficients */   
	  b20 = __SXTB16(b20);  
  
#endif	  /* acc0 += x[n-numTaps] * b[numTaps - 2] +  x[n-numTaps-2] * b[numTaps - 4] */  
      acc0 = __SMLAD(x20, b20, acc0);  
  
	  /* acc0 += x[n-numTaps + 1] * b[numTaps - 1] + x[n-numTaps- 1] * b[numTaps - 3] */  
      acc0 = __SMLAD(x31, b31, acc0);  
  
	  /* second sample */  
  
	  /* pack state variables from Xin1 and Xin2 */  
  
#ifndef ARM_MATH_BIG_ENDIAN  
	  x0 = xin1 >> 8;  
	  x0 = (x0 & 0x00FFFFFF)|((xin2 & 0xFF) << 24);   
#else  
	  x0 = xin1 << 8;  
	  x0 = (x0 & 0xFFFFFF00)|((xin2 & 0xFF000000) >> 24);    
#endif  
  
	  /* Extract state data */		    
#ifdef CCS  
  
	  x20 = __SXTB16(x0, 0);  
	  x31 = __SXTB16(x0, 8);  
  
#else  
  
	  x20 = __SXTB16(x0);  
	  x31 = __SXTB16(__ROR(x0, 8));  
  
#endif  
	  /* Perform the multiply-accumulates */   
	  acc1 = __SMLAD(x20, b20, acc1);  
      acc1 = __SMLAD(x31, b31, acc1);  
  
	  /* third sample */  
	  /* pack state variables from Xin1 and Xin2 */  
  
#ifndef ARM_MATH_BIG_ENDIAN  
	  x0 = xin1 >> 16;  
	  x0 = (x0 & 0x0000FFFF)|((xin2 & 0xFFFF) << 16);   
#else  
	  x0 = xin1 << 16;  
	  x0 = (x0 & 0xFFFF0000)|((xin2 & 0xFFFF0000) >> 16);   
			     
#endif	     
	    
	  /* Extract state data */  
#ifdef CCS  
	    
	  x20 = __SXTB16(x0, 0);  
	  x31 = __SXTB16(x0, 8);  
  
#else  
	    
	  x20 = __SXTB16(x0);  
	  x31 = __SXTB16(__ROR(x0, 8));  
  
#endif  
  
	  /* Perform the multiply-accumulates */   
	  acc2 = __SMLAD(x20, b20, acc2);  
      acc2 = __SMLAD(x31, b31, acc2);  
  
  
	  /* fourth sample */  
	  /* pack state variables from Xin1 and Xin2 */  
#ifndef ARM_MATH_BIG_ENDIAN  
	  x0 = xin1>>24;  
	  x0 = (x0& 0x000000FF)|((xin2 & 0xFFFFFF) << 8);   
#else  
	  x0 = xin1 << 24;  
	  x0 = (x0 & 0xFF000000)|((xin2 & 0xFFFFFF00) >> 8);   
#endif  
	    
	  /* Extract state data */  
#ifdef CCS  
  
	  x20 = __SXTB16(x0, 0);  
	  x31 = __SXTB16(x0, 8);  
  
#else  
  
	  x20 = __SXTB16(x0);  
	  x31 = __SXTB16(__ROR(x0, 8));  
  
#endif  
  
	  /* Perform the multiply-accumulates */   
	  acc3=__SMLAD(x20, b20, acc3);  
      acc3=__SMLAD(x31, b31, acc3);  
	    
	  /* Copy Xin2 for next iteration */		  
	  xin1 = xin2;  
  
	    
      /* Decrement the tap loop counter */   
      i--;   
    }   
  
	/* Initializtion to keep px7(state pointer) at correct position */  
	px7 = px7 - 4u;  
  
	/* Read state values */  
 	x1 = (*px7++);  
	x2 = (*px7++);  
	x3 = (*px7++);  
  
    /* If the filter length is not a multiple of 4, compute the remaining filter taps */   
   
    i = numTaps - (tapCnt * 4u);   
    while(i > 0u)   
    {   
      /* Read coefficients */   
      c0 = (*pb7++);   
   
      /* Fetch 1 state variable */   
      x4 = (*px7++);   
   
      /* Perform the multiply-accumulates */   
      acc0 += ((q15_t) x1 * c0);   
      acc1 += ((q15_t) x2 * c0);   
      acc2 += ((q15_t) x3 * c0);   
      acc3 += ((q15_t) x4 * c0);   
   
      /* Reuse the present sample states for next sample */   
      x1 = x2;   
      x2 = x3;   
      x3 = x4;   
   
      /* Decrement the loop counter */   
      i--;   
    }   
  
#ifdef CCS  
	/* Saturate output */   
    acc0 = __SSATA(acc0, 7u, 8);   
    /*Store filtered output */  
	*pDst++ = acc0;	   
    acc1 = __SSATA(acc1, 7u, 8);   
    *pDst++ = acc1;   
    acc2 = __SSATA(acc2, 7u, 8);   
    *pDst++ = acc2;   
    acc3 = __SSATA(acc3, 7u, 8);   
    *pDst++ = acc3;   
#else   
	/* Saturate output */   
    acc0 = __SSAT((acc0 >> 7u), 8);   
	/*Store filtered output */  
    *pDst++ = acc0;   
    acc1 = __SSAT((acc1 >> 7u), 8);   
    *pDst++ = acc1;   
    acc2 = __SSAT((acc2 >> 7u), 8);   
    *pDst++ = acc2;   
    acc3 = __SSAT((acc3 >> 7u), 8);   
    *pDst++ = acc3;   
#endif   
   
    /* Advance the state pointer by 4 to process the next sample */   
    pState = pState + 4;   
   
    /* Decrement the loop counter */   
    blkCnt--;   
  }   
   
  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.      
   ** No loop unrolling is used. */   
  blkCnt = blockSize % 4u;   
   
  while(blkCnt > 0u)   
  {   
    /* Copy one sample at a time into state buffer */   
    *pStateCurnt++ = *pSrc++;   
   
    /* Set the accumulator to zero */   
    acc0 = 0;   
   
    /* Initialize state pointer */   
    px7 = pState;   
   
    /* Initialize Coefficient pointer */   
    pb7 = (pCoeffs);   
   
    tapCnt = numTaps;   
   
    /* Perform the multiply-accumulates */   
    do   
    {   
      acc0 += (q15_t) (*px7++) * (*(pb7++));   
   
	  /* Decrement the loop counter */   
      tapCnt--;   
   
    } while(tapCnt > 0u);   
   
    /* The result is in 2.14 format.  Convert to 1.7      
     ** Then store the output in the destination buffer. */   
#ifdef CCS   
    *pDst++ = __SSATA(acc0, 7u, 8);   
#else   
    *pDst++ = __SSAT((acc0 >> 7u), 8);   
#endif	   
   
    /* Advance state pointer by 1 for the next sample */   
    pState = pState + 1u;   
   
    /* Decrement the samples loop counter */   
    blkCnt--;   
  }   
   
  /* Processing is complete.    
   ** Now copy the last numTaps - 1 samples to the satrt of the state buffer.    
   ** This prepares the state buffer for the next function call. */   
   
  /* Points to the start of the state buffer */   
  pStateCurnt = S->pState;   
   
  tapCnt = (numTaps - 1u) >> 3u;   
   
  /* copy data */   
  while(tapCnt > 0u)   
  {   
	  /* Copy state values to start of state buffer */  
	  *pStateCurnt++ = *pState++;   
	  *pStateCurnt++ = *pState++;   
	  *pStateCurnt++ = *pState++;   
	  *pStateCurnt++ = *pState++;  
	     
	  *pStateCurnt++ = *pState++;   
	  *pStateCurnt++ = *pState++;   
	  *pStateCurnt++ = *pState++;   
	  *pStateCurnt++ = *pState++;   
  
    /* Decrement the loop counter */   
    tapCnt--;   
  }   
   
  /* Calculate remaining number of copies */   
  tapCnt = (numTaps - 1u) % 8u;   
   
  /* Copy the remaining q31_t data */   
  while(tapCnt > 0u)   
  {   
    *pStateCurnt++ = *pState++;   
   
    /* Decrement the loop counter */   
    tapCnt--;   
  }   
   
}   
   
/**      
 * @} end of FIR group      
 */   
