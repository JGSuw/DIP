/* ----------------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_q7_to_float.c      
*      
* Description:	Converts the elements of the Q7 vector to floating-point vector.      
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
 * @defgroup q7_to_x  Convert 8-bit Integer value      
 */     
     
/**      
 * @addtogroup q7_to_x      
 * @{      
 */     
     
/**      
 * @brief Converts the elements of the Q7 vector to floating-point vector.      
 * @param[in]       *pSrc points to the Q7 input vector      
 * @param[out]      *pDst points to the floating-point output vector     
 * @param[in]       blockSize length of the input vector      
 * @return none.      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 *		       
 * \par Description:      
 *      
 * The equation used for the conversion process is:      
 *     
 * <pre>      
 * 	pDst[n] = (float32_t) pSrc[n] / 128;   0 <= n < blockSize.      
 * </pre>      
 *     
 */     
     
     
void arm_q7_to_float(     
  q7_t * pSrc,     
  float32_t * pDst,     
  uint32_t blockSize)     
{     
  q7_t *pIn = pSrc;                              /* Src pointer */     
  uint32_t blkCnt;                               /* loop counter */     
     
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = (float32_t) A / 128 */     
    /* convert from q7 to float and then store the results in the destination buffer */     
    *pDst++ = ((float32_t) * pIn++ / 128.0f);     
    *pDst++ = ((float32_t) * pIn++ / 128.0f);     
    *pDst++ = ((float32_t) * pIn++ / 128.0f);     
    *pDst++ = ((float32_t) * pIn++ / 128.0f);     
    *pDst++ = ((float32_t) * pIn++ / 128.0f);     
    *pDst++ = ((float32_t) * pIn++ / 128.0f);     
    *pDst++ = ((float32_t) * pIn++ / 128.0f);     
    *pDst++ = ((float32_t) * pIn++ / 128.0f);     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = (float32_t) A / 128 */     
    /* convert from q7 to float and then store the results in the destination buffer */     
    *pDst++ = ((float32_t) * pIn++ / 128.0f);     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of q7_to_x group      
 */     
