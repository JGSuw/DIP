/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_negate_q31.c      
*      
* Description:	Negates Q31 vectors.      
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
 * @addtogroup negate      
 * @{      
 */     
     
/**      
 * @brief  Negates the elements of a Q31 vector.      
 * @param[in]  *pSrc points to the input vector      
 * @param[out]  *pDst points to the output vector      
 * @param[in]  blockSize number of samples in the vector      
 * @return none.      
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function uses saturating arithmetic.      
 * The Q31 value -1 (0x80000000) will be saturated to the maximum allowable positive value 0x7FFFFFFF.      
 */     
     
void arm_negate_q31(     
  q31_t * pSrc,     
  q31_t * pDst,     
  uint32_t blockSize)     
{     
  q31_t in1, in2, in3, in4;                      /* Temporary variables */     
  uint32_t blkCnt;                               /* loop counter */     
     
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = -A */     
    /* Negate and then store the results in the destination buffer. */     
	/* read samples from source */  
	in1 = *pSrc;  
	in2 = *(pSrc + 1);  
  
	/* negate input */  
	in1 = __QSUB(0, in1);  
  
	/* read samples from source */  
	in3 = *(pSrc + 2);  
  
	/* negate input */  
	in2 = __QSUB(0, in2);  
  
	/* read samples from source */  
	in4 = *(pSrc + 3);  
  
	/* negate input */  
	in3 = __QSUB(0, in3);  
  
	/* store result to destination */  
	*pDst = in1;  
  
	/* negate input */  
	in4 = __QSUB(0, in4);  
  
	/* store result to destination */  
	*(pDst + 1) = in2;  
	*(pDst + 2) = in3;  
	*(pDst + 3) = in4;  
  
	/* read samples from source */  
	in1 = *(pSrc + 4);  
	in2 = *(pSrc + 5);  
  
	/* negate input */  
	in1 = __QSUB(0, in1);  
  
	/* read samples from source */  
	in3 = *(pSrc + 6);  
  
	/* negate input */  
	in2 = __QSUB(0, in2);  
  
	/* read samples from source */  
	in4 = *(pSrc + 7);  
  
	/* negate input */  
	in3 = __QSUB(0, in3);  
  
	/* store result to destination */  
	*(pDst + 4) = in1;  
  
	/* negate input */  
	in4 = __QSUB(0, in4);  
  
	/* store result to destination */  
	*(pDst + 5) = in2;  
  
	/* increment source by 8 to process next samples */  
	pSrc += 8u;  
  
	/* store result to destination */  
	*(pDst + 6) = in3;  
	*(pDst + 7) = in4;  
  
	/* increment destination by 8 */ 
	pDst += 8u;  
	     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = -A */     
    /* Negate and then store the result in the destination buffer. */     
    in1 = *pSrc++;     
    *pDst++ = __QSUB(0, in1);     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of negate group      
 */     
