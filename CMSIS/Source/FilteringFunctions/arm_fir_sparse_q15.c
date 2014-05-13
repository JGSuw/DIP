/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_fir_sparse_q15.c      
*      
* Description:	Q15 sparse FIR filter processing function.     
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
* ------------------------------------------------------------------- */     
#include "arm_math.h"    
     
/**      
 * @addtogroup FIR_Sparse      
 * @{      
 */     
     
/**     
 * @brief Processing function for the Q15 sparse FIR filter.     
 * @param[in]  *S           points to an instance of the Q15 sparse FIR structure.     
 * @param[in]  *pSrc        points to the block of input data.     
 * @param[out] *pDst        points to the block of output data     
 * @param[in]  *pScratchIn  points to a temporary buffer of size blockSize.     
 * @param[in]  *pScratchOut points to a temporary buffer of size blockSize.     
 * @param[in]  blockSize    number of input samples to process per call.     
 * @return none.     
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function is implemented using an internal 32-bit accumulator.     
 * The 1.15 x 1.15 multiplications yield a 2.30 result and these are added to a 2.30 accumulator.     
 * Thus the full precision of the multiplications is maintained but there is only a single guard bit in the accumulator.     
 * If the accumulator result overflows it will wrap around rather than saturate.     
 * After all multiply-accumulates are performed, the 2.30 accumulator is truncated to 2.15 format and then saturated to 1.15 format.      
 * In order to avoid overflows the input signal or coefficients must be scaled down by log2(numTaps) bits.     
 */     
     
     
void arm_fir_sparse_q15(     
  arm_fir_sparse_instance_q15 * S,     
  q15_t * pSrc,     
  q15_t * pDst,     
  q15_t * pScratchIn,     
  q31_t * pScratchOut,     
  uint32_t blockSize)     
{     
     
  q15_t *pState = S->pState;                     /* State pointer */     
  q15_t *pIn = pSrc;                   /* Working pointer for input */     
  q15_t *pOut = pDst;                            /* Working pointer for output */     
  q15_t *pCoeffs = S->pCoeffs;                   /* Coefficient pointer */     
  q15_t *px;                                     /* Temporary pointers for scratch buffer */     
  q15_t *pb = pScratchIn;                        /* Temporary pointers for scratch buffer */     
  q15_t *py = pState;                            /* Temporary pointers for state buffer */     
  int32_t *pTapDelay = S->pTapDelay;             /* Pointer to the array containing offset of the non-zero tap values. */     
  uint32_t delaySize = S->maxDelay + blockSize;  /* state length */     
  uint16_t numTaps = S->numTaps;                 /* Filter order */     
  int32_t readIndex;                             /* Read index of the state buffer */     
  uint32_t tapCnt, blkCnt;                       /* loop counters */     
  q15_t coeff = *pCoeffs++;                      /* Read the first coefficient value */     
  q31_t *pScr2 = pScratchOut;                    /* Working pointer for pScratchOut */     
  q31_t in1, in2;                                /* Temporary variables */     
  q15_t x0, x1;  
  q31_t y0, y1;  
     
     
  /* BlockSize of Input samples are copied into the state buffer */     
  /* StateIndex points to the starting position to write in the state buffer */     
  arm_circularWrite_q15(py, delaySize, &S->stateIndex, 1, pIn, 1, blockSize);     
     
  /* Loop over the number of taps. */     
  tapCnt = numTaps;     
     
  /* Read Index, from where the state buffer should be read, is calculated. */     
  readIndex = (S->stateIndex - blockSize) - *pTapDelay++;     
     
  /* Wraparound of readIndex */     
  if(readIndex < 0)     
  {     
    readIndex += (int32_t) delaySize;     
  }     
     
  /* Working pointer for state buffer is updated */     
  py = pState;     
     
  /* blockSize samples are read from the state buffer */     
  arm_circularRead_q15(py, delaySize, &readIndex, 1,     
                       pb, pb, blockSize, 1, blockSize);     
     
  /* Working pointer for the scratch buffer of state values */     
  px = pb;     
     
  /* Working pointer for scratch buffer of output values */     
  pScratchOut = pScr2;     
     
  /* Loop over the blockSize. Unroll by a factor of 4.      
   * Compute 4 multiplications at a time. */     
  blkCnt = blockSize >> 2;     
     
  while(blkCnt > 0u)     
  {  
    /* Perform Multiplications and store in scratch buffer */  
  
    /* Read two values from state */  
    x0 = *px;  
	x1 = *(px + 1u);  
  
    /* multiply  */  
	y0 = (q31_t)x0 * coeff;  
	y1 = (q31_t)x1 * coeff;  
	     
	/* Write two values into output buffer */     
    *pScratchOut++ =  y0;     
    *pScratchOut++ =  y1;     
  
	/* Read next two values from state */  
  	x0 = *(px + 2u);  
	x1 = *(px + 3u);  
  
	/* multiply  */  
	y0 = (q31_t)x0 * coeff;  
	y1 = (q31_t)x1 * coeff;  
	     
	/* Write next two values into output buffer */     
    *pScratchOut++ =  y0;  
	px += 4u;	     
    *pScratchOut++ =  y1;     
	     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 4,      
   * compute the remaining samples */     
  blkCnt = blockSize % 0x4u;     
     
  while(blkCnt > 0u)     
  {     
    /* Perform multiplication and store in the scratch buffer */     
    *pScratchOut++ = ((q31_t) * px++ * coeff);     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* Load the coefficient value and      
   * increment the coefficient buffer for the next set of state values */     
  coeff = *pCoeffs++;     
     
  /* Read Index, from where the state buffer should be read, is calculated. */     
  readIndex = (S->stateIndex - blockSize) - *pTapDelay++;     
     
  /* Wraparound of readIndex */     
  if(readIndex < 0)     
  {     
    readIndex += (int32_t) delaySize;     
  }     
     
  /* Loop over the number of taps. */     
  tapCnt = (uint32_t) numTaps - 1u;     
     
  while(tapCnt > 0u)     
  {     
    /* Working pointer for state buffer is updated */     
    py = pState;     
     
    /* blockSize samples are read from the state buffer */     
    arm_circularRead_q15(py, delaySize, &readIndex, 1,     
                         pb, pb, blockSize, 1, blockSize);     
     
    /* Working pointer for the scratch buffer of state values */     
    px = pb;     
     
    /* Working pointer for scratch buffer of output values */     
    pScratchOut = pScr2;     
     
    /* Loop over the blockSize. Unroll by a factor of 4.      
     * Compute 4 MACS at a time. */     
    blkCnt = blockSize >> 2;     
     
    while(blkCnt > 0u)     
    {  
        /* Read two values from scratch */  
		x0 = *px;  
		x1 = *(px + 1u);  
  
		/* Read two values from output buffer */  
		y0 = *pScratchOut;  
		y1 = *(pScratchOut + 1u);  
  
		/* Perform Multiply-Accumulate */  
		y0 = (q31_t)x0 * coeff + y0;  
		y1 = (q31_t)x1 * coeff + y1;  
  
		/* write multiply-Accumlate values into output buffer */		  
		*pScratchOut = y0;  
		*(pScratchOut + 1u) = y1;  
  
        /* Read next two values from scratch */  
	    x0 = *(px + 2u);  
		x1 = *(px + 3u);  
		/* Read two values from output buffer */  
		y0 = *(pScratchOut + 2u);  
		y1 = *(pScratchOut + 3u);  
  
		/* Perform Multiply-Accumulate */  
		y0 = (q31_t)x0 * coeff + y0;  
		y1 = (q31_t)x1 * coeff + y1;  
  
		/* write multiply-Accumlate values into output buffer */  
		*(pScratchOut + 2u) = y0;  
		*(pScratchOut + 3u) = y1;  
  
		/* update pointers */  
		px += 4u;  
		pScratchOut += 4u;  
		     
     
      /* Decrement the loop counter */     
      blkCnt--;     
    }     
     
    /* If the blockSize is not a multiple of 4,      
     * compute the remaining samples */     
    blkCnt = blockSize % 0x4u;     
     
    while(blkCnt > 0u)     
    {  
      
      /* Perform Multiply-Accumulate */     
      *pScratchOut++ += (q31_t) * px++ * coeff;     
     
      /* Decrement the loop counter */     
      blkCnt--;     
    }     
     
    /* Load the coefficient value and      
     * increment the coefficient buffer for the next set of state values */     
    coeff = *pCoeffs++;     
     
    /* Read Index, from where the state buffer should be read, is calculated. */     
    readIndex = (S->stateIndex - blockSize) - *pTapDelay++;     
     
    /* Wraparound of readIndex */     
    if(readIndex < 0)     
    {     
      readIndex += (int32_t) delaySize;     
    }     
     
    /* Decrement the tap loop counter */     
    tapCnt--;     
  }     
     
  /* All the output values are in pScratchOut buffer.      
     Convert them into 1.15 format, saturate and store in the destination buffer. */     
  /* Loop over the blockSize. */     
  blkCnt = blockSize >> 2;     
     
  while(blkCnt > 0u)     
  {     
	/* Read two values from output buffer */  
    in1 = *pScr2++;     
    in2 = *pScr2++;     
    
#ifndef  ARM_MATH_BIG_ENDIAN   
   
    *__SIMD32(pOut)++ =     
#ifdef CCS   
      __PKHBT((q15_t) __SSATA(in1, 15, 16), (q15_t) __SSATA(in2, 15, 16), 16);      
#else   
      __PKHBT((q15_t) __SSAT(in1 >> 15, 16), (q15_t) __SSAT(in2 >> 15, 16), 16);      
#endif	   //	#ifdef CCS   
			     
#else   
    *__SIMD32(pOut)++ =   
#ifdef CCS   
      __PKHBT((q15_t) __SSATA(in2, 15, 16), (q15_t) __SSATA(in1, 15, 16), 16);      
#else   
      __PKHBT((q15_t) __SSAT(in2 >> 15, 16), (q15_t) __SSAT(in1 >> 15, 16), 16);    
#endif	 //	#ifdef CCS   
   
#endif /*      #ifndef  ARM_MATH_BIG_ENDIAN    */   
   
	/* Read two values from output buffer */  
    in1 = *pScr2++;     
    in2 = *pScr2++;     
   
#ifndef  ARM_MATH_BIG_ENDIAN   
   
    *__SIMD32(pOut)++ =     
#ifdef CCS   
      __PKHBT((q15_t) __SSATA(in1, 15, 16), (q15_t) __SSATA(in2, 15, 16), 16);     
#else   
      __PKHBT((q15_t) __SSAT(in1 >> 15, 16), (q15_t) __SSAT(in2 >> 15, 16), 16);     
#endif 		//	#ifdef CCS   
     
#else   
   
    *__SIMD32(pOut)++ =   
#ifdef CCS  
      __PKHBT((q15_t) __SSATA(in2, 15, 16), (q15_t) __SSATA(in1, 15, 16), 16);    
#else   
      __PKHBT((q15_t) __SSAT(in2 >> 15, 16), (q15_t) __SSAT(in1 >> 15, 16), 16);   
#endif	   //	#ifdef CCS   
   
                
   
#endif /*      #ifndef  ARM_MATH_BIG_ENDIAN    */   
   
    blkCnt--;     
     
  }     
     
  /* If the blockSize is not a multiple of 4,      
     remaining samples are processed in the below loop */     
  blkCnt = blockSize % 0x4u;     
     
  while(blkCnt > 0u)     
  {     
#ifdef CCS   
    *pOut++ = (q15_t) __SSATA(*pScr2++, 15, 16);     
#else   
    *pOut++ = (q15_t) __SSAT(*pScr2++ >> 15, 16);     
#endif	   
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of FIR_Sparse group      
 */     
