/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_offset_q15.c      
*      
* Description:	Q15 vector offset.      
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
 * @brief  Adds a constant offset to a Q15 vector.      
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
 * Results outside of the allowable Q15 range [0x8000 0x7FFF] are saturated.      
 */     
     
void arm_offset_q15(     
  q15_t * pSrc,     
  q15_t offset,     
  q15_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t offset_packed;                           /* Offset packed to 32 bit */     
  q31_t in1, in2;			   					 /* temporary variables */  
  q15_t in;										 /* temporary variables */  
     
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* Offset is packed to 32 bit in order to use SIMD32 for addition */     
  offset_packed = __PKHBT(offset, offset, 16);     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = A + offset */     
    /* Add offset and then store the results in the destination buffer, 2 samples at a time. */     
	/* read two samples at a time from source */  
	in1 = *__SIMD32(pSrc)++;  
	in2 = *__SIMD32(pSrc)++;  
  
    /* add offset to two samples at a time */  
	in1 = __QADD16(in1, offset_packed);     
    in2 = __QADD16(in2, offset_packed);     
  
	/* store result to the destination two samples at a time */  
	*__SIMD32(pDst)++  = in1;  
	*__SIMD32(pDst)++  = in2;  
  
	/* read two samples at a time from source */  
	in1 = *__SIMD32(pSrc)++;  
	in2 = *__SIMD32(pSrc)++;  
  
    /* add offset to two samples at a time */  
    in1 = __QADD16(in1, offset_packed);     
    in2 = __QADD16(in2, offset_packed);     
  
	/* store result to the destination two samples at a time */  
	*__SIMD32(pDst)++  = in1;  
	*__SIMD32(pDst)++  = in2;  
  
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A + offset */     
    /* Add offset and then store the results in the destination buffer. */     
	in = *pSrc++;  
    *pDst++ = (q15_t) __QADD16(in, offset);     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of offset group      
 */     
