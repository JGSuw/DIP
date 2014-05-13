/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_shift_q31.c      
*      
* Description:	Shifts the elements of a Q31 vector by a specified number of bits.      
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
 * @defgroup shift Vector Shift      
 *      
 * Shifts the elements of a fixed-point vector by a specified number of bits.      
 * There are separate functions for Q7, Q15, and Q31 data types.      
 * The underlying algorithm used is:      
 *      
 * <pre>      
 *     pDst[n] = pSrc[n] << shift,   0 <= n < blockSize.      
 * </pre>      
 *      
 * If <code>shift</code> is positive then the elements of the vector are shifted to the left.      
 * If <code>shift</code> is negative then the elements of the vector are shifted to the right.      
 */     
     
/**      
 * @addtogroup shift      
 * @{      
 */     
     
/**      
 * @brief  Shifts the elements of a Q31 vector a specified number of bits.      
 * @param[in]  *pSrc points to the input vector      
 * @param[in]  shiftBits number of bits to shift.  A positive value shifts left; a negative value shifts right.      
 * @param[out]  *pDst points to the output vector      
 * @param[in]  blockSize number of samples in the vector      
 * @return none.      
 *      
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function uses saturating arithmetic.      
 * Results outside of the allowable Q31 range [0x80000000 0x7FFFFFFF] will be saturated.      
 */     
     
void arm_shift_q31(     
  q31_t * pSrc,     
  int8_t shiftBits,     
  q31_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  uint8_t sign;                                  /* Sign of shiftBits */     
  q31_t in1, in2, in3, in4;						 /* Temporary input variables */  
  q31_t out1, out2, out3, out4;   				 /* Temporary output variables */  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* Getting the sign of shiftBits */     
  sign = (shiftBits & 0x80);  
  
  if(sign == 0u)  
  {				 	    
	  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
	   ** a second loop below computes the remaining 1 to 7 samples. */     
	  while(blkCnt > 0u)     
	  {     
	    /* C = A  << shiftBits */     
	    /* Shift the input and then store the results in the destination buffer. */     
		in1 = *pSrc;  
		in2 = *(pSrc + 1);  
		out1 = in1 << shiftBits;  
		in3 = *(pSrc + 2);  
		out2 = in2 << shiftBits;  
		in4 = *(pSrc + 3);  
	  	if(in1 != (out1 >> shiftBits))   
		    out1 = 0x7FFFFFFF ^(in1 >> 31);   
		  
	  	if(in2 != (out2 >> shiftBits))   
		    out2 = 0x7FFFFFFF ^(in2 >> 31);   
	  
		*pDst = out1;  
		out3 = in3 << shiftBits;  
		*(pDst + 1) = out2;  
		out4 = in4 << shiftBits;  
  
		if(in3 != (out3 >> shiftBits))   
		    out3 = 0x7FFFFFFF ^(in3 >> 31);   
  
	  	if(in4 != (out4 >> shiftBits))   
		    out4 = 0x7FFFFFFF ^(in4 >> 31);   
  
		*(pDst + 2) = out3;  
		*(pDst + 3) = out4;  
		  
		in1 = *(pSrc + 4);  
		in2 = *(pSrc + 5);  
		out1 = in1 << shiftBits;  
		in3 = *(pSrc + 6);  
		out2 = in2 << shiftBits;  
		in4 = *(pSrc + 7);  
	  	if(in1 != (out1 >> shiftBits))   
		    out1 = 0x7FFFFFFF ^(in1 >> 31);   
		  
	  	if(in2 != (out2 >> shiftBits))   
		    out2 = 0x7FFFFFFF ^(in2 >> 31);   
	  
		*(pDst + 4) = out1;  
		out3 = in3 << shiftBits;  
		*(pDst + 5) = out2;  
		out4 = in4 << shiftBits;  
  
		if(in3 != (out3 >> shiftBits))   
		    out3 = 0x7FFFFFFF ^(in3 >> 31);   
  
	  	if(in4 != (out4 >> shiftBits))   
		    out4 = 0x7FFFFFFF ^(in4 >> 31);   
  
		*(pDst + 6) = out3;  
		/* Update source pointer to process next sampels */  
		pSrc += 8u;  
		*(pDst + 7) = out4;  
  
		/* Update destination pointer to process next sampels */  
		pDst += 8u;  
  
	    /* Decrement the loop counter */     
	    blkCnt--;     
	  }     
	     
	  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
	   ** No loop unrolling is used. */     
	  blkCnt = blockSize % 0x8u;     
	     
	  while(blkCnt > 0u)     
	  {     
	    /* C = A (>> or <<) shiftBits */     
	    /* Shift the input and then store the result in the destination buffer. */   
		in1 = *pSrc++;  
		out1 = in1 << shiftBits;  
 	  	if(in1 != (out1 >> shiftBits))   
		    out1 = 0x7FFFFFFF ^(in1 >> 31);   
   
	    *pDst++ = out1;     
	     
	    /* Decrement the loop counter */     
	    blkCnt--;     
	  }     
	}  
	else  
	{  
	  shiftBits = -shiftBits;  
  
 	  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
	   ** a second loop below computes the remaining 1 to 7 samples. */     
	  while(blkCnt > 0u)     
	  {     
	    /* C = A >>  shiftBits */     
	    /* Shift the input and then store the results in the destination buffer. */     
		in1 = *pSrc;  
		in2 = *(pSrc + 1);  
		in3 = *(pSrc + 2);  
		in4 = *(pSrc + 3);  
  
		*pDst = (in1 >> shiftBits);  
		*(pDst + 1) = (in2 >> shiftBits);  
		*(pDst + 2) = (in3 >> shiftBits);  
		*(pDst + 3) = (in4 >> shiftBits);  
  
		in1 = *(pSrc + 4);  
		in2 = *(pSrc + 5);  
		in3 = *(pSrc + 6);  
		in4 = *(pSrc + 7);  
  
		*(pDst + 4) = (in1 >> shiftBits);  
		*(pDst + 5) = (in2 >> shiftBits);  
		*(pDst + 6) = (in3 >> shiftBits);  
		*(pDst + 7) = (in4 >> shiftBits);  
  
		pSrc += 8u;  
		pDst += 8u;  
		  
		blkCnt--;  
	  }     
	     
	  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
	   ** No loop unrolling is used. */     
	  blkCnt = blockSize % 0x8u;     
	     
	  while(blkCnt > 0u)     
	  {     
	    /* C = A (>> or <<) shiftBits */     
	    /* Shift the input and then store the result in the destination buffer. */     
		in1 = *pSrc++;  
	    *pDst++ = (in1 >> shiftBits);     
	     
	    /* Decrement the loop counter */     
	    blkCnt--;     
	  }   
	}    
  
}     
     
/**      
 * @} end of shift group      
 */     
