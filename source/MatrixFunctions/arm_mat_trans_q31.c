/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_mat_trans_q31.c      
*      
* Description:	Q31 matrix transpose.      
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
 * @ingroup groupMatrix      
 */     
     
/**      
 * @addtogroup MatrixTrans      
 * @{      
 */     
     
/*      
  * @brief Q31 matrix transpose.      
  * @param[in]  *pSrc points to the input matrix      
  * @param[out] *pDst points to the output matrix      
  * @return 	The function returns either  <code>ARM_MATH_SIZE_MISMATCH</code>      
  * or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.      
 */     
     
arm_status arm_mat_trans_q31(     
  const arm_matrix_instance_q31 * pSrc,     
  arm_matrix_instance_q31 * pDst)     
{     
  q31_t *pIn = pSrc->pData;                      /* input data matrix pointer  */     
  q31_t *pOut = pDst->pData;                     /* output data matrix pointer  */     
  q31_t *px;                                     /* Temporary output data matrix pointer */     
  uint16_t nRows = pSrc->numRows;                /* number of nRows */     
  uint16_t nColumns = pSrc->numCols;             /* number of nColumns  */     
  uint16_t blkCnt, i = 0u, row = nRows;          /* loop counters */     
  arm_status status;                             /* status of matrix transpose */     
  q31_t in1, in2, in3, in4;  
     
#ifdef ARM_MATH_MATRIX_CHECK     
  /* Check for matrix mismatch condition */     
  if((pSrc->numRows != pDst->numCols) || (pSrc->numCols != pDst->numRows))     
  {     
    /* Set status as ARM_MATH_SIZE_MISMATCH */     
    status = ARM_MATH_SIZE_MISMATCH;     
  }     
  else     
#endif     
  {     
    /* Matrix transpose by exchanging the rows with columns */     
    /* row loop     */     
    do     
    {     
      /* Apply loop unrolling and exchange the columns with row elements */     
      blkCnt = nColumns >> 3u;     
     
      /* The pointer px is set to starting address of the column being processed */     
      px = pOut + i;     
     
      /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.      
       ** a second loop below computes the remaining 1 to 3 samples. */     
      while(blkCnt > 0u)     
      {     
        /* Read and store the input element in the destination */     
		in1 = pIn[0];  
		*px = in1;  
  
        /* Update the pointer px to point to the next row of the transposed matrix */     
		px += nRows;  
  
        /* Read and store the input element in the destination */     
		in2 = pIn[1];  
		*px = in2;  
  
        /* Update the pointer px to point to the next row of the transposed matrix */     
		px += nRows;  
  
        /* Read and store the input element in the destination */     
		in3 = pIn[2];  
		*px = in3;  
  
        /* Update the pointer px to point to the next row of the transposed matrix */     
		px += nRows;  
  
        /* Read and store the input element in the destination */     
		in4 = pIn[3];  
		*px = in4;  
  
        /* Update the pointer px to point to the next row of the transposed matrix */     
		px += nRows;  
  
        /* Read and store the input element in the destination */     
		in1 = pIn[4];  
		*px = in1;  
  
        /* Update the pointer px to point to the next row of the transposed matrix */     
		px += nRows;  
  
        /* Read and store the input element in the destination */     
		in2 = pIn[5];  
		*px = in2;  
  
        /* Update the pointer px to point to the next row of the transposed matrix */     
		px += nRows;  
  
        /* Read and store the input element in the destination */     
		in3 = pIn[6];  
		*px = in3;  
  
        /* Update the pointer px to point to the next row of the transposed matrix */     
		px += nRows;  
  
        /* Read and store the input element in the destination */     
		in4 = pIn[7];  
		*px = in4;  
  
        /* Update the pointer px to point to the next row of the transposed matrix */     
		px += nRows;  
  
        /* Update the pointer pIn to point to the next column of the matrix */     
		pIn += 8u;  
		   
        /* Decrement the column loop counter */     
        blkCnt--;     
      }     
     
      /* Perform matrix transpose for last 3 samples here. */     
      blkCnt = nColumns % 0x8u;     
     
      while(blkCnt > 0u)     
      {     
        /* Read and store the input element in the destination */     
        *px = *pIn++;     
     
        /* Update the pointer px to point to the next row of the transposed matrix */     
        px += nRows;     
     
        /* Decrement the column loop counter */     
        blkCnt--;     
      }     
     
      i++;     
     
      /* Decrement the row loop counter */     
      row--;     
     
    }     
    while(row > 0u);            /* row loop end */     
     
    /* set status as ARM_MATH_SUCCESS */     
    status = ARM_MATH_SUCCESS;     
  }     
     
  /* Return to application */     
  return (status);     
}     
     
/**      
 * @} end of MatrixTrans group      
 */     
