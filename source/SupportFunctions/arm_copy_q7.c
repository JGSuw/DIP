/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_copy_q7.c      
*      
* Description:	Copies the elements of a Q7 vector.      
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
 * @ingroup groupSupport      
 */     
     
/**      
 * @addtogroup copy      
 * @{      
 */     
     
/**      
 * @brief Copies the elements of a Q7 vector.      
 * @param[in]       *pSrc points to input vector      
 * @param[out]      *pDst points to output vector      
 * @param[in]       blockSize length of the input vector     
 * @return none.      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 *      
 */     
     
void arm_copy_q7(     
  q7_t * pSrc,     
  q7_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t in1, in2;  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = A */     
    /* Copy and then store the results in the destination buffer */     
    /* 4 samples are copied and stored at a time using SIMD */     
	in1 = *__SIMD32(pSrc)++;  
	*__SIMD32(pDst)++ = in1;  
	in2 = *__SIMD32(pSrc)++;  
	*__SIMD32(pDst)++ = in2;  
  
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A */     
    /* Copy and then store the results in the destination buffer */     
    *pDst++ = *pSrc++;     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of BasicCopy group      
 */     
