/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_dot_prod_q7.c      
*      
* Description:	Q7 dot product.      
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
 * @brief Dot product of Q7 vectors.      
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
 * The intermediate multiplications are in 1.7 x 1.7 = 2.14 format and these      
 * results are added to an accumulator in 18.14 format.      
 * Nonsaturating additions are used and there is no danger of wrap around as long as      
 * the vectors are less than 2^18 elements long.      
 * The return result is in 18.14 format.      
 */     
     
void arm_dot_prod_q7(     
  q7_t * pSrcA,     
  q7_t * pSrcB,     
  uint32_t blockSize,     
  q31_t * result)     
{     
  q31_t input1, input2;                          /* Temporary variables to store input */     
  q31_t sum = 0;                                 /* Temporary variables to store output */     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t inA1, inB1, inA2, inB2;   
  
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {  
  	/* read 4 samples at a time from sourceA */  
  	input1 = *__SIMD32(pSrcA)++;  
  	/* read 4 samples at a time from sourceB */  
	input2 = *__SIMD32(pSrcB)++;  
  
#ifdef CCS  
  
	/* extract two q7_t samples to q15_t samples */  
	inA1 = __SXTB16(input1, 8);  
	/* extract reminaing two samples */  
	inA2 = __SXTB16(input1, 0);  
	/* extract two q7_t samples to q15_t samples */  
	inB1 = __SXTB16(input2, 8);  
	/* extract reminaing two samples */  
	inB2 = __SXTB16(input2, 0);  
  
#else  
  
	/* extract two q7_t samples to q15_t samples */  
	inA1 = __SXTB16(__ROR(input1, 8));  
	/* extract reminaing two samples */  
	inA2 = __SXTB16(input1);  
	/* extract two q7_t samples to q15_t samples */  
	inB1 = __SXTB16(__ROR(input2, 8));  
	/* extract reminaing two samples */  
	inB2 = __SXTB16(input2);  
  
#endif  
  
	/* multiply and accumulate two samples at a time */  
	sum = __SMLAD(inA1, inB1, sum);     
    sum = __SMLAD(inA2, inB2, sum);     
  
  	/* read 4 samples at a time from sourceA */  
  	input1 = *__SIMD32(pSrcA)++;  
  	/* read 4 samples at a time from sourceB */  
	input2 = *__SIMD32(pSrcB)++;  
  
#ifdef CCS  
  
	/* extract two q7_t samples to q15_t samples */  
	inA1 = __SXTB16(input1, 8);  
	/* extract reminaing two samples */  
	inA2 = __SXTB16(input1, 0);  
	/* extract two q7_t samples to q15_t samples */  
	inB1 = __SXTB16(input2, 8);  
	/* extract reminaing two samples */  
	inB2 = __SXTB16(input2, 0);  
  
#else  
  
	/* extract two q7_t samples to q15_t samples */  
	inA1 = __SXTB16(__ROR(input1, 8));  
	/* extract reminaing two samples */  
	inA2 = __SXTB16(input1);  
	/* extract two q7_t samples to q15_t samples */  
	inB1 = __SXTB16(__ROR(input2, 8));  
	/* extract reminaing two samples */  
	inB2 = __SXTB16(input2);  
  
#endif  
  
	/* multiply and accumulate two samples at a time */  
	sum = __SMLAD(inA1, inB1, sum);     
    sum = __SMLAD(inA2, inB2, sum);     
  
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */     
    /* Dot product and then store the results in a temporary buffer. */     
    sum = __SMLAD(*pSrcA++, *pSrcB++, sum);     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* Store the result in the destination buffer in 18.14 format */     
  *result = sum;     
}     
     
/**      
 * @} end of dot_prod group      
 */     
