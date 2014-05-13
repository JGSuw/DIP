/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_mult_f32.c      
*      
* Description:	Floating-point vector multiplication.      
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
 * @ingroup groupMath      
 */     
     
/**      
 * @defgroup BasicMult Vector Multiplication      
 *      
 * Element-by-element multiplication of two vectors.      
 *      
 * <pre>      
 *     pDst[n] = pSrcA[n] * pSrcB[n],   0 <= n < blockSize.      
 * </pre>      
 *      
 * There are separate functions for floating-point, Q7, Q15, and Q31 data types.      
 */     
     
/**      
 * @addtogroup BasicMult      
 * @{      
 */     
     
/**      
 * @brief Floating-point vector multiplication.      
 * @param[in]       *pSrcA points to the first input vector      
 * @param[in]       *pSrcB points to the second input vector      
 * @param[out]      *pDst points to the output vector      
 * @param[in]       blockSize number of samples in each vector      
 * @return none.      
 */     
     
void arm_mult_f32(     
  float32_t * pSrcA,     
  float32_t * pSrcB,     
  float32_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counters */     
  float32_t inA1, inA2, inA3, inA4;	  			 /* temporary input variables */  
  float32_t inB1, inB2, inB3, inB4;				 /* temporary input variables */  
  float32_t out1, out2, out3, out4;				 /* temporary output variables */  
     
  /* loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = A * B */     
    /* Multiply the inputs and store the results in output buffer */  
	/* read sample from sourceA */  
	inA1 = *pSrcA;  
	/* read sample from sourceB */  
	inB1 = *pSrcB;  
	/* read sample from sourceA */  
	inA2 = *(pSrcA + 1);  
	/* read sample from sourceB */  
	inB2 = *(pSrcB + 1);  
  
	/* out = sourceA * sourceB */  
	out1 = inA1 * inB1;  
  
	/* read sample from sourceA */  
	inA3 = *(pSrcA + 2);  
	/* read sample from sourceB */  
	inB3 = *(pSrcB + 2);  
  
	/* out = sourceA * sourceB */  
 	out2 = inA2 * inB2;  
  
	/* read sample from sourceA */  
	inA4 = *(pSrcA + 3);  
  
	/* store result to destination buffer */  
	*pDst = out1;  
  
	/* read sample from sourceB */  
	inB4 = *(pSrcB + 3);  
  
	/* out = sourceA * sourceB */  
 	out3 = inA3 * inB3;  
  
	/* read sample from sourceA */  
	inA1 = *(pSrcA + 4);  
  
	/* store result to destination buffer */  
	*(pDst + 1) = out2;  
  
	/* read sample from sourceB */  
	inB1 = *(pSrcB + 4);  
  
	/* out = sourceA * sourceB */  
	out4 = inA4 * inB4;  
  
	/* read sample from sourceA */  
	inA2 = *(pSrcA + 5);  
  
	/* store result to destination buffer */  
	*(pDst + 2) = out3;  
  
	/* read sample from sourceB */  
	inB2 = *(pSrcB + 5);  
  
	/* out = sourceA * sourceB */  
	out1 = inA1 * inB1;  
  
	/* read sample from sourceA */  
	inA3 = *(pSrcA + 6);  
  
	/* store result to destination buffer */  
	*(pDst + 3) = out4;  
  
	/* read sample from sourceB */  
	inB3 = *(pSrcB + 6);  
  
	/* out = sourceA * sourceB */  
	out2 = inA2 * inB2;  
  
	/* read sample from sourceA */  
	inA4 = *(pSrcA + 7);  
	/* read sample from sourceB */  
	inB4 = *(pSrcB + 7);  
  
	/* store result to destination buffer */  
	*(pDst + 4) = out1;  
  
	/* out = sourceA * sourceB */  
	out3 = inA3 * inB3;  
  
	/* store result to destination buffer */  
	*(pDst + 5) = out2;  
  
	/* out = sourceA * sourceB */  
	out4 = inA4 * inB4;  
  
	/* increment sourceA by 8 to process next samples */  
	pSrcA += 8u;  
  
	/* store result to destination buffer */  
	*(pDst + 6) = out3;  
  
	/* increment sourceB by 8 to process next samples */  
	pSrcB += 8u;  
  
	/* store result to destination buffer */  
	*(pDst + 7) = out4;  
  
	/* increment destination buffer by 8 to process next samples */  
	pDst += 8u;  
  
    /* Decrement the blockSize loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A * B */     
    /* Multiply the inputs and store the results in output buffer */     
	inA1 = *pSrcA++;  
	inB1 = *pSrcB++;  
  
    *pDst++ = inA1 * inB1;     
     
    /* Decrement the blockSize loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of BasicMult group      
 */     
