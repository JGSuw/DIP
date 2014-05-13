/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_fill_q7.c      
*      
* Description:	Fills a constant value into a Q7 vector.     
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
 * @addtogroup Fill      
 * @{      
 */     
     
/**      
 * @brief Fills a constant value into a Q7 vector.      
 * @param[in]       value input value to be filled     
 * @param[out]      *pDst points to output vector      
 * @param[in]       blockSize length of the output vector     
 * @return none.      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 *      
 */     
     
void arm_fill_q7(     
  q7_t value,     
  q7_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t packedValue;                             /* value packed to 32 bits */     
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* Packing four 8 bit values to 32 bit value in order to use SIMD */     
  packedValue = __PACKq7(value, value, value, value);     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 8 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = value */     
    /* Fill the value in the destination buffer */     
    *__SIMD32(pDst)++ = packedValue;     
    *__SIMD32(pDst)++ = packedValue;     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = value */     
    /* Fill the value in the destination buffer */     
    *pDst++ = value;     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of Fill group      
 */     
