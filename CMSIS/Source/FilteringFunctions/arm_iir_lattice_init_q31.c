/*-----------------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:        arm_iir_lattice_init_q31.c      
*      
* Description:  Initialization function for the Q31 IIR lattice filter.      
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
* ---------------------------------------------------------------------------*/     
#include "arm_math.h"     
     
/**      
 * @ingroup groupFilters      
 */     
     
/**      
 * @addtogroup IIR_Lattice      
 * @{      
 */     
     
  /**      
   * @brief Initialization function for the Q31 IIR lattice filter.      
   * @param[in] *S points to an instance of the Q31 IIR lattice structure.      
   * @param[in] numStages number of stages in the filter.      
   * @param[in] *pkCoeffs points to the reflection coefficient buffer.  The array is of length numStages.      
   * @param[in] *pvCoeffs points to the ladder coefficient buffer.  The array is of length numStages+1.      
   * @param[in] *pState points to the state buffer.  The array is of length numStages+blockSize.      
   * @param[in] blockSize number of samples to process.      
   * @return none.      
   */     
     
void arm_iir_lattice_init_q31(     
  arm_iir_lattice_instance_q31 * S,     
  uint16_t numStages,     
  q31_t * pkCoeffs,     
  q31_t * pvCoeffs,     
  q31_t * pState,     
  uint32_t blockSize)     
{     
  /* Assign filter taps */     
  S->numStages = numStages;     
     
  /* Assign reflection coefficient pointer */     
  S->pkCoeffs = pkCoeffs;     
     
  /* Assign ladder coefficient pointer */     
  S->pvCoeffs = pvCoeffs;     
     
  /* Clear state buffer and size is always blockSize + numStages */     
  memset(pState, 0, (numStages + blockSize) * sizeof(q31_t));     
     
  /* Assign state pointer */     
  S->pState = pState;     
     
     
}     
     
/**      
 * @} end of IIR_Lattice group      
 */     
