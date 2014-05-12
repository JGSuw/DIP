/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_power_q7.c      
*      
* Description:	Sum of the squares of the elements of a Q7 vector.      
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
 * @ingroup groupStats      
 */     
     
/**      
 * @addtogroup power      
 * @{      
 */     
     
/**      
 * @brief Sum of the squares of the elements of a Q7 vector.      
 * @param[in]       *pSrc points to the input vector      
 * @param[in]       blockSize length of the input vector      
 * @param[out]      *pResult acc of the squares value returned here      
 * @return none.      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 *      
 * @details      
 * <b>Scaling and Overflow Behavior:</b>      
 *      
 * \par      
 * The function is implemented using a 32-bit internal accumulator.       
 * The input is represented in 1.7 format.     
 * Intermediate multiplication yields a 2.14 format, and this      
 * result is added without saturation to an accumulator in 18.14 format.      
 * With 17 guard bits in the accumulator, there is no risk of overflow, and the      
 * full precision of the intermediate multiplication is preserved.      
 * Finally, the return result is in 18.14 format.       
 *      
 */     
     
void arm_power_q7(     
  q7_t * pSrc,     
  uint32_t blockSize,     
  q31_t * pResult)     
{     
  q31_t acc = 0;                                 /* Temporary result storage */     
  q31_t input1;                                  /* Temporary variable to store packed input */     
  q7_t in;                                       /* Temporary variable to store input */     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t inA1, inA2;	   							 /* Temporary variables to hold intermiediate data */  
  q31_t acc1 = 0;  
     
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {    
  	/* read four samples at a time from soruce buffer */   
  	input1 = _SIMD32_OFFSET(pSrc);  
  
	/* extend two q7_t values to q15_t values */  
#ifdef CCS  
  
	inA1 = __SXTB16(input1, 8);  
	inA2 = __SXTB16(input1, 0);  
  
#else  
  
	inA1 = __SXTB16(__ROR(input1, 8));  
	inA2 = __SXTB16(input1);  
  
#endif	//	#ifdef CCS  
  
    /* calculate power and accumulate to accumulator */  
	acc = __SMLAD(inA1, inA1, acc);     
  
  	/* read four samples at a time from soruce buffer */   
  	input1 = _SIMD32_OFFSET(pSrc + 4);  
  
#ifdef CCS  
  
	/* extend two q7_t values to q15_t values */  
	inA1 = __SXTB16(input1, 8);  
  
    /* calculate power and accumulate to accumulator */  
    acc1 = __SMLAD(inA2, inA2, acc1);     
  
	/* extend two q7_t values to q15_t values */  
	inA2 = __SXTB16(input1, 0);  
  
#else  
  
	/* extend two q7_t values to q15_t values */  
	inA1 = __SXTB16(__ROR(input1, 8));  
  
    /* calculate power and accumulate to accumulator */  
    acc1 = __SMLAD(inA2, inA2, acc1);     
  
	/* extend two q7_t values to q15_t values */  
	inA2 = __SXTB16(input1);  
  
#endif	//	#ifdef CCS  
  
    /* calculate power and accumulate to accumulator */  
    acc = __SMLAD(inA1, inA1, acc);     
    acc1 = __SMLAD(inA2, inA2, acc1);  
      
	/* update source buffer to process next samples */  
	pSrc += 8u;     
    
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
    
  /* add accumulators */  
  acc = acc + acc1;   
    
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A[0] * A[0] + A[1] * A[1] + A[2] * A[2] + ... + A[blockSize-1] * A[blockSize-1] */     
    /* Compute Power and then store the result in a temporary variable, acc. */     
    in = *pSrc++;     
    acc += ((q15_t) in * in);     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* Store the result in 18.14 format  */     
  *pResult = acc;     
}     
     
/**      
 * @} end of power group      
 */     
