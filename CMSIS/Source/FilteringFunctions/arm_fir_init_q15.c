/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:        arm_fir_init_q15.c      
*      
* Description:  Q15 FIR filter initialization function.      
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
* ------------------------------------------------------------------- */     
     
#include "arm_math.h"     
     
/**      
 * @ingroup groupFilters      
 */     
     
/**      
 * @addtogroup FIR      
 * @{      
 */     
     
/**      
 * @param[in,out]  *S points to an instance of the Q15 FIR filter structure.      
 * @param[in] 	   numTaps  Number of filter coefficients in the filter. Must be even and greater than or equal to 4.      
 * @param[in]      *pCoeffs points to the filter coefficients buffer.      
 * @param[in]      *pState points to the state buffer.      
 * @param[in]      blockSize is number of samples processed per call.      
 * @return The function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_ARGUMENT_ERROR if      
 * <code>numTaps</code> is not greater than or equal to 4 and even.      
 *      
 * <b>Description:</b>      
 * \par      
 * <code>pCoeffs</code> points to the array of filter coefficients stored in time reversed order:      
 * <pre>      
 *    {b[numTaps-1], b[numTaps-2], b[N-2], ..., b[1], b[0]}      
 * </pre>      
 * Note that <code>numTaps</code> must be even and greater than or equal to 2.      
 * To implement an odd length filter simply increase <code>numTaps</code> by 1 and set the last coefficient to zero.      
 * For example, to implement a filter with <code>numTaps=3</code> and coefficients      
 * <pre>      
 *     {0.3, -0.8, 0.3}      
 * </pre>      
 * set <code>numTaps=4</code> and use the coefficients:      
 * <pre>      
 *     {0.3, -0.8, 0.3, 0}.      
 * </pre>      
 *  
 * \par      
 * <code>pState</code> points to the array of state variables.      
 * <code>pState</code> is of length <code>numTaps+blockSize</code>, where <code>blockSize</code> is the number of input samples processed by each call to <code>arm_fir_q15()</code>.      
 */     
     
arm_status arm_fir_init_q15(     
  arm_fir_instance_q15 * S,     
  uint16_t numTaps,     
  q15_t * pCoeffs,     
  q15_t * pState,     
  uint32_t blockSize)     
{     
  arm_status status;     
     
  /* The Number of filter coefficients in the filter must be even and at least 4 */     
  if(numTaps & 0x1u)  
  {     
    status = ARM_MATH_ARGUMENT_ERROR;     
  }     
  else     
  {     
    /* Assign filter taps */     
    S->numTaps = numTaps;     
     
    /* Assign coefficient pointer */     
    S->pCoeffs = pCoeffs;   
  
    /* Clear the state buffer.  The size is always (blockSize + numTaps ) */     
    memset(pState, 0, (numTaps + (blockSize)) * sizeof(q15_t));     
   
    /* Assign state pointer */     
    S->pState = pState;     
     
    status = ARM_MATH_SUCCESS;     
  }     
     
  return (status);     
}     
     
/**      
 * @} end of FIR group      
 */     
