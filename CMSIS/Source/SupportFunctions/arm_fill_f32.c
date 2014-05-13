/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_fill_f32.c      
*      
* Description:	Fills a constant value into a floating-point vector.     
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
 * @defgroup Fill Vector Fill      
 *      
 * Fills the destination vector with a constant value.      
 *      
 * <pre>      
 * 	pDst[n] = value;   0 <= n < blockSize.      
 * </pre>      
 *     
 * There are separate functions for floating point, Q31, Q15, and Q7 data types.       
 */     
     
/**      
 * @addtogroup Fill      
 * @{      
 */     
     
/**      
 * @brief Fills a constant value into a floating-point vector.       
 * @param[in]       value input value to be filled     
 * @param[out]      *pDst points to output vector      
 * @param[in]       blockSize length of the output vector     
 * @return none.      
 *      
 */     
     
     
void arm_fill_f32(     
  float32_t value,     
  float32_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  float32_t value1 = value;  
  float32_t value2 = value;  
  float32_t value3 = value;  
  float32_t value4 = value;  
  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = value */     
    /* Fill the value in the destination buffer */     
	pDst[0] = value1;  
	pDst[1] = value2;  
	pDst[2] = value3;  
	pDst[3] = value4;  
	pDst[4] = value1;  
	pDst[5] = value2;  
	pDst[6] = value3;  
	pDst[7] = value4;  
	pDst += 8u;  
    
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
