/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_max_q31.c      
*      
* Description:	Maximum value of a Q31 vector.      
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
 * @ingroup groupStats      
 */     
     
/**      
 * @addtogroup Max      
 * @{      
 */     
     
     
/**      
 * @brief Maximum value of a Q31 vector.      
 * @param[in]       *pSrc points to the input vector      
 * @param[in]       blockSize length of the input vector      
 * @param[out]      *pResult maximum value returned here      
 * @param[out]      *pIndex index of maximum value returned here      
 * @return none.      
 */     
     
void arm_max_q31(     
  q31_t * pSrc,     
  uint32_t blockSize,     
  q31_t * pResult,     
  uint32_t * pIndex)     
{     
  q31_t maxVal1, maxVal2, maxVal3, maxVal4,out;                             /* Temporary variables to store the output value. */     
  uint32_t blkCnt, outIndex, count;              /* loop counter */     
     
  /* Initialise the count value. */  
  count =0u;     
  /* Initialise the index value to zero. */     
  outIndex = 0u;     
  /* Load first input value that act as reference value for comparision */     
  out = *pSrc++;     
     
  /* Loop unrolling */   
  blkCnt = (blockSize - 1u) >> 2u;     
     
  while(blkCnt > 0u)     
  {     
    /* Initialize maxVal to the next consecutive values one by one */     
    maxVal1 = *pSrc++;     
	maxVal2 = *pSrc++;     
    maxVal3 = *pSrc++;     
	maxVal4 = *pSrc++;     
     
    /* compare for the maximum value */     
    if(out < maxVal1)     
    {     
      /* Update the maximum value and its index */     
      out = maxVal1;     
      outIndex = count + 1u;     
    }     
    
    /* compare for the maximum value */     
    if(out < maxVal2)     
    {     
      /* Update the maximum value and its index */     
      out = maxVal2;     
      outIndex = count + 2u;     
    }     
     
    /* compare for the maximum value */     
    if(out < maxVal3)     
    {     
      /* Update the maximum value and its index */     
      out = maxVal3;     
      outIndex = count + 3u;     
    }     
    
    /* compare for the maximum value */     
    if(out < maxVal4)     
    {     
      /* Update the maximum value and its index */     
      out = maxVal4;     
      outIndex = count + 4u;     
    }     
  
   	count += 4u;  
  
	/* Decrement the loop counter */    
    blkCnt--;      
  };   
   
  /* if (blockSize - 1u) is not multiple of 4 */  
  blkCnt = (blockSize - 1u) % 4u;     
     
  while(blkCnt > 0u)     
  {     
    /* Initialize maxVal to the next consecutive values one by one */     
    maxVal1 = *pSrc++;     
     
    /* compare for the maximum value */     
    if(out < maxVal1)     
    {     
      /* Update the maximum value and its index */     
      out = maxVal1;     
      outIndex = blockSize - blkCnt;     
    }     
     
	/* Decrement the loop counter */    
    blkCnt--;      
  };     
     
  /* Store the maximum value and its index into destination pointers */     
  *pResult = out;     
  *pIndex = outIndex;     
}     
     
/**      
 * @} end of Max group      
 */     
