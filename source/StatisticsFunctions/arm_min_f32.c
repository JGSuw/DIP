/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_min_f32.c      
*      
* Description:	Minimum value of a floating-point vector.      
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
 * @defgroup Min Minimum      
 *      
 * Computes the minimum value of an array of data.       
 * The function returns both the minimum value and its position within the array.       
 * There are separate functions for floating-point, Q31, Q15, and Q7 data types.      
 */     
     
/**      
 * @addtogroup Min      
 * @{      
 */     
     
     
/**      
 * @brief Minimum value of a floating-point vector.      
 * @param[in]       *pSrc points to the input vector      
 * @param[in]       blockSize length of the input vector      
 * @param[out]      *pResult minimum value returned here      
 * @param[out]      *pIndex index of minimum value returned here      
  * @return none.      
 *      
 */     
     
void arm_min_f32(     
  float32_t * pSrc,     
  uint32_t blockSize,     
  float32_t * pResult,     
  uint32_t * pIndex)     
{     
  float32_t minVal1, minVal2, out;                         /* Temporary variables to store the output value. */     
  uint32_t blkCnt, outIndex, count;              /* loop counter */     
     
  /* Initialise the count value. */     
  count = 0u;  
  /* Initialise the index value to zero. */     
  outIndex = 0u;     
  /* Load first input value that act as reference value for comparision */     
  out = *pSrc++;     
     
  /* Loop unrolling */     
  blkCnt = (blockSize - 1u) >> 2u;     
     
  while(blkCnt > 0)     
  {     
    /* Initialize minVal to the next consecutive values one by one */     
    minVal1 = pSrc[0];      
    minVal2 = pSrc[1];     
   
    /* compare for the minimum value */     
    if(out > minVal1)     
    {     
      /* Update the minimum value and its index */     
      out = minVal1;     
      outIndex = count + 1u;     
    }     
     
    minVal1 = pSrc[2];     
  
    /* compare for the minimum value */     
    if(out > minVal2)     
    {     
      /* Update the minimum value and its index */     
      out = minVal2;     
      outIndex = count + 2u;     
    }     
  
    minVal2 = pSrc[3];   
  
    /* compare for the minimum value */     
    if(out > minVal1)     
    {     
      /* Update the minimum value and its index */     
      out = minVal1;     
      outIndex = count + 3u;     
    }     
	    
    /* compare for the minimum value */     
    if(out > minVal2)     
    {     
      /* Update the minimum value and its index */     
      out = minVal2;     
      outIndex = count + 4u;     
    }     
  
   	count += 4u;  
  
	pSrc += 4u;  
  
    blkCnt--;      
  };     
  
  /* if (blockSize - 1u ) is not multiple of 4 */     
  blkCnt = (blockSize - 1u) % 4u;     
     
  while(blkCnt > 0)     
  {     
    /* Initialize minVal to the next consecutive values one by one */     
    minVal1 = *pSrc++;     
     
    /* compare for the minimum value */     
    if(out > minVal1)     
    {     
      /* Update the minimum value and it's index */     
      out = minVal1;     
      outIndex = blockSize - blkCnt;     
    }     
     
    blkCnt--;     
     
  };     
  
  /* Store the minimum value and it's index into destination pointers */     
  *pResult = out;     
  *pIndex = outIndex;     
}     
     
/**      
 * @} end of Min group      
 */     
