/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_offset_q31.c      
*      
* Description:	Q31 vector offset.      
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
 * @brief  Adds a constant offset to a Q31 vector.      
 * @param[in]  *pSrc points to the input vector      
 * @param[in]  offset is the offset to be added      
 * @param[out]  *pDst points to the output vector      
 * @param[in]  blockSize number of samples in the vector      
 * @return none.      
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function uses saturating arithmetic.      
 * Results outside of the allowable Q31 range [0x80000000 0x7FFFFFFF] are saturated.      
 */     
     
void arm_offset_q31(     
  q31_t * pSrc,     
  q31_t offset,     
  q31_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t in1, in2, in3, in4;		 				 /* temporary variables */  
     
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = A + offset */     
    /* Add offset and then store the results in the destination buffer. */     
	/* read samples from the source */  
	in1 = *pSrc;  
	in2 = *(pSrc + 1);  
  
	/* add offset to the input */  
    in1 = __QADD(in1, offset);     
  
	/* read sample from the source */  
	in3 = *(pSrc + 2);  
  
	/* add offset to the input */  
    in2 = __QADD(in2, offset);     
  
	/* read sample from the source */  
	in4 = *(pSrc + 3);  
  
	/* add offset to the input */  
    in3 = __QADD(in3, offset);     
  
	/* store result to destination buffer */  
  	*pDst = in1;  
  
	/* add offset to the input */  
	in4 = __QADD(in4, offset);   
	    
	/* store result to destination buffer */  
	*(pDst + 1) = in2;  
	*(pDst + 2) = in3;  
	*(pDst + 3) = in4;  
  
	/* read samples from the source */  
	in1 = *(pSrc + 4);  
	in2 = *(pSrc + 5);  
  
	/* add offset to the input */  
    in1 = __QADD(in1, offset);     
  
	/* read sample from the source */  
	in3 = *(pSrc + 6);  
  
	/* add offset to the input */  
    in2 = __QADD(in2, offset);     
	  
	/* read sample from the source */  
	in4 = *(pSrc + 7);  
  
	/* store result to destination buffer */  
	*(pDst + 4) = in1;  
     
	/* add offset to the input */  
    in3 = __QADD(in3, offset);     
  
	/* store result to destination buffer */  
 	*(pDst + 5) = in2;  
  
	/* add offset to the input */  
    in4 = __QADD(in4, offset);     
  
	/* store result to destination buffer */  
	*(pDst + 6) = in3;  
	  
	/* increment source pointer by 8 to process next samples */  
	pSrc += 8u;  
	  
	/* store result to destination buffer */  
	*(pDst + 7) = in4;  
  
	/* increment destination pointer by 8 */  
	pDst += 8u;  
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A + offset */     
    /* Add offset and then store the result in the destination buffer. */     
	in1 = *pSrc++;  
    *pDst++ = __QADD(in1, offset);     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of offset group      
 */     
