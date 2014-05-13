/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_offset_q7.c      
*      
* Description:	Q7 vector offset.      
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
 * @addtogroup offset      
 * @{      
 */     
     
/**      
 * @brief  Adds a constant offset to a Q7 vector.      
 * @param[in]  *pSrc points to the input vector      
 * @param[in]  offset is the offset to be added      
 * @param[out]  *pDst points to the output vector      
 * @param[in]  blockSize number of samples in the vector      
 * @return none.      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function uses saturating arithmetic.      
 * Results outside of the allowable Q7 range [0x80 0x7F] are saturated.      
 */     
     
void arm_offset_q7(     
  q7_t * pSrc,     
  q7_t offset,     
  q7_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t offset_packed;                           /* Offset packed to 32 bit */     
  q31_t in1, in2, in3, in4;						 /* Temporary variabels */  
  q7_t in;										 /* Temporary variable */  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 4u;     
     
  /* Offset is packed to 32 bit in order to use SIMD32 for addition */     
  offset_packed = __PACKq7(offset, offset, offset, offset);     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = A + offset */     
    /* Add offset and then store the results in the destination bufferfor 8 samples at a time. */     
	/* read 4 samples at a time from the source */  
	in1 = _SIMD32_OFFSET(pSrc);  
	in2 = _SIMD32_OFFSET(pSrc + 4);  
  
	/* added offset to the four samples at a time */  
	in1 = __QADD8(in1, offset_packed);  
  
	/* read 4 samples at a time from the source */  
	in3 = _SIMD32_OFFSET(pSrc + 8);  
  
	/* added offset to the four samples at a time */  
	in2 = __QADD8(in2, offset_packed);  
  
	/* read 4 samples at a time from the source */  
	in4 = _SIMD32_OFFSET(pSrc + 12);  
  
	/* store result to the destination four samples at a time */  
	_SIMD32_OFFSET(pDst) = in1;  
  
	/* added offset to the four samples at a time */  
	in3 = __QADD8(in3, offset_packed);  
  
	/* store result to the destination four samples at a time */  
	_SIMD32_OFFSET(pDst + 4) = in2;  
  
	/* added offset to the four samples at a time */  
	in4 = __QADD8(in4, offset_packed);  
  
	/* store result to the destination four samples at a time */  
	_SIMD32_OFFSET(pDst + 8) = in3;  
  
	/* increment source by 16 to process next samples */  
	pSrc += 16u;  
	  
	/* store result to the destination four samples at a time */  
	_SIMD32_OFFSET(pDst + 12) = in4;  
	  
	/* increment destination by 16 */  
	pDst += 16u;  
  
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x10u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A + offset */     
    /* Add offset and then store the result in the destination buffer. */     
	in = *pSrc++;  
	*pDst++ = (q7_t)(__QADD8(in, offset));  
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of offset group      
 */     
