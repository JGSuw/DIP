/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_dot_prod_q15.c      
*      
* Description:	Q15 dot product.      
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
 * @addtogroup dot_prod      
 * @{      
 */     
     
/**      
 * @brief Dot product of Q15 vectors.      
 * @param[in]       *pSrcA points to the first input vector      
 * @param[in]       *pSrcB points to the second input vector      
 * @param[in]       blockSize number of samples in each vector      
 * @param[out]      *result output result returned here      
 * @return none.      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The intermediate multiplications are in 1.15 x 1.15 = 2.30 format and these      
 * results are added to a 64-bit accumulator in 34.30 format.      
 * Nonsaturating additions are used and given that there are 33 guard bits in the accumulator      
 * there is no risk of overflow.      
 * The return result is in 34.30 format.      
 */     
     
void arm_dot_prod_q15(     
  q15_t * pSrcA,     
  q15_t * pSrcB,     
  uint32_t blockSize,     
  q63_t * result)     
{     
  q63_t sum = 0;                                 /* Temporary result storage */     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t inA1, inA2, inB1, inB2; 				 /* Temporary variables to store input data */  
  q31_t inA3, inA4, inB3, inB4;  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */     
    /* Calculate dot product and then store the result in a temporary buffer. */     
	/* read two samples at a time from soruceA buffer */  
	inA1 = _SIMD32_OFFSET(pSrcA);  
	/* read two samples at a time from soruceB buffer */  
	inB1 = _SIMD32_OFFSET(pSrcB);  
	/* read two samples at a time from soruceA buffer */  
	inA2 = _SIMD32_OFFSET(pSrcA+2);  
  
	/* multiply and accumulate two samples at a time */  
    sum = __SMLALD(inA1, inB1, sum);
	    
	/* read two samples at a time from soruceB buffer */  
	inB2 = _SIMD32_OFFSET(pSrcB+2);  
	/* read two samples at a time from soruceA buffer */  
	inA3 = _SIMD32_OFFSET(pSrcA+4);  
	/* read two samples at a time from soruceB buffer */  
	inB3 = _SIMD32_OFFSET(pSrcB+4);  
  
	/* multiply and accumulate two samples at a time */  
    sum = __SMLALD(inA2, inB2, sum);
  
	/* read two samples at a time from soruceA buffer */  
	inA4 = _SIMD32_OFFSET(pSrcA+6);  
	/* read two samples at a time from soruceB buffer */  
	inB4 = _SIMD32_OFFSET(pSrcB+6);  
  
	/* increment source A buffer by 8 */  
	pSrcA += 8u;  
	/* increment sourceB buffer by 8 */  
	pSrcB += 8u;  
  
	/* multiply and accumulate two samples at a time */  
    sum = __SMLALD(inA3, inB3, sum);
    sum = __SMLALD(inA4, inB4, sum);
  
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */     
    /* Calculate dot product and then store the results in a temporary buffer. */     
    sum = __SMLALD(*pSrcA++, *pSrcB++, sum);
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* Store the result in the destination buffer in 34.30 format */     
  *result = sum;     
}     
     
/**      
 * @} end of dot_prod group      
 */     
