/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:        arm_mat_init_q15.c      
*      
* Description:	Q15 matrix initialization.      
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
* -------------------------------------------------------------------------- */     
     
     
#include "arm_math.h"     
     
/**      
 * @ingroup groupMatrix      
 */     
     
/**      
 * @addtogroup MatrixInit      
 * @{      
 */     
     
  /**      
   * @brief  Q15 matrix initialization.      
   * @param[in,out] *S             points to an instance of the floating-point matrix structure.      
   * @param[in]     nRows          number of rows in the matrix.      
   * @param[in]     nColumns       number of columns in the matrix.      
   * @param[in]     *pData	   points to the matrix data array.      
   * @return        none      
   */     
     
void arm_mat_init_q15(     
  arm_matrix_instance_q15 * S,     
  uint16_t nRows,     
  uint16_t nColumns,     
  q15_t * pData)     
{     
  /* Assign Number of Rows */     
  S->numRows = nRows;     
     
  /* Assign Number of Columns */     
  S->numCols = nColumns;     
     
  /* Assign Data pointer */     
  S->pData = pData;     
}     
     
/**      
 * @} end of MatrixInit group      
 */     
