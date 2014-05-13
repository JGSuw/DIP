/* ----------------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_copy_f32.c      
*      
* Description:	Copies the elements of a floating-point vector.    
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
* ---------------------------------------------------------------------------- */     
#include "arm_math.h"     
     
/**      
 * @ingroup groupSupport      
 */     
     
/**      
 * @defgroup copy Vector Copy      
 *      
 * Copies sample by sample from source vector to destination vector.      
 *      
 * <pre>      
 * 	pDst[n] = pSrc[n];   0 <= n < blockSize.      
 * </pre>      
 *     
 * There are separate functions for floating point, Q31, Q15, and Q7 data types.       
 */     
     
/**      
 * @addtogroup copy      
 * @{      
 */     
     
/**      
 * @brief Copies the elements of a floating-point vector.       
 * @param[in]       *pSrc points to input vector      
 * @param[out]      *pDst points to output vector      
 * @param[in]       blockSize length of the input vector     
 * @return none.      
 *      
 */     
     
     
void arm_copy_f32(     
  float32_t * pSrc,     
  float32_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  float32_t in1, in2, in3, in4, in5, in6, in7, in8;  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = A */     
    /* Copy and then store the results in the destination buffer */     
	in1 = pSrc[0];  
	in2 = pSrc[1];  
	in3 = pSrc[2];  
	in4 = pSrc[3];  
	in5 = pSrc[4];  
	in6 = pSrc[5];  
	in7 = pSrc[6];  
	in8 = pSrc[7];  
  
	pDst[0] = in1;  
	pDst[1] = in2;  
	pDst[2] = in3;  
	pDst[3] = in4;  
	pDst[4] = in5;  
	pDst[5] = in6;  
	pDst[6] = in7;  
	pDst[7] = in8;  
  
	pSrc += 8u;  
	pDst += 8u;  
    
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
