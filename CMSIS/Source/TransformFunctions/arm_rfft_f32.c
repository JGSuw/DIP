/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_rfft_f32.c      
*      
* Description:	RFFT & RIFFT Floating point process function      
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
 * @ingroup groupTransforms      
 */     
     
/**      
 * @defgroup RFFT_RIFFT Real FFT Functions      
 *      
 * \par      
 * Complex FFT/IFFT typically assumes complex input and output. However many applications use real valued data in time domain.       
 * Real FFT/IFFT efficiently process real valued sequences with the advantage of requirement of low memory and with less complexity.      
 *      
 * \par      
 * This set of functions implements Real Fast Fourier Transforms(RFFT) and Real Inverse Fast Fourier Transform(RIFFT)      
 * for Q15, Q31, and floating-point data types.        
 *      
 *      
 * \par Algorithm:      
 *      
 * <b>Real Fast Fourier Transform:</b>      
 * \par      
 * Real FFT of N-point is calculated using CFFT of N/2-point and Split RFFT process as shown below figure.      
 * \par      
 * \image html RFFT.gif "Real Fast Fourier Transform"      
 * \par      
 * The RFFT functions operate on blocks of input and output data and each call to the function processes      
 * <code>fftLenR</code> samples through the transform.  <code>pSrc</code>  points to input array containing <code>fftLenR</code> values.      
 * <code>pDst</code>  points to output array containing <code>2*fftLenR</code> values. \n     
 * Input for real FFT is in the order of       
 * <pre>{real[0], real[1], real[2], real[3], ..}</pre>      
 * Output for real FFT is complex and are in the order of      
 * <pre>{real(0), imag(0), real(1), imag(1), ...}</pre>       
 *      
 * <b>Real Inverse Fast Fourier Transform:</b>      
 * \par      
 * Real IFFT of N-point is calculated using Split RIFFT process and CFFT of N/2-point as shown below figure.      
 * \par      
 * \image html RIFFT.gif "Real Inverse Fast Fourier Transform"      
 * \par      
 * The RIFFT functions operate on blocks of input and output data and each call to the function processes      
 * <code>2*fftLenR</code> samples through the transform.  <code>pSrc</code>  points to input array containing <code>2*fftLenR</code> values.      
 * <code>pDst</code>  points to output array containing <code>fftLenR</code> values. \n      
 * Input for real IFFT is complex and are in the order of     
 * <pre>{real(0), imag(0), real(1), imag(1), ...}</pre>     
 *  Output for real IFFT is real and in the order of       
 * <pre>{real[0], real[1], real[2], real[3], ..}</pre>     
 *      
 * \par Lengths supported by the transform:     
 * \par      
 * Real FFT/IFFT supports the lengths [128, 512, 2048], as it internally uses CFFT/CIFFT.      
 *      
 * \par Instance Structure      
 * A separate instance structure must be defined for each Instance but the twiddle factors can be reused.      
 * There are separate instance structure declarations for each of the 3 supported data types.      
 *      
 * \par Initialization Functions      
 * There is also an associated initialization function for each data type.      
 * The initialization function performs the following operations:      
 * - Sets the values of the internal structure fields.      
 * - Initializes twiddle factor tables.     
 * - Initializes CFFT data structure fields.       
 * \par      
 * Use of the initialization function is optional.      
 * However, if the initialization function is used, then the instance structure cannot be placed into a const data section.      
 * To place an instance structure into a const data section, the instance structure must be manually initialized.      
 * Manually initialize the instance structure as follows:      
 * <pre>      
 *arm_rfft_instance_f32 S = {fftLenReal, fftLenBy2, ifftFlagR, bitReverseFlagR, twidCoefRModifier, pTwiddleAReal, pTwiddleBReal, pCfft};      
 *arm_rfft_instance_q31 S = {fftLenReal, fftLenBy2, ifftFlagR, bitReverseFlagR, twidCoefRModifier, pTwiddleAReal, pTwiddleBReal, pCfft};      
 *arm_rfft_instance_q15 S = {fftLenReal, fftLenBy2, ifftFlagR, bitReverseFlagR, twidCoefRModifier, pTwiddleAReal, pTwiddleBReal, pCfft};      
 * </pre>      
 * where <code>fftLenReal</code> length of RFFT/RIFFT; <code>fftLenBy2</code> length of CFFT/CIFFT.       
 * <code>ifftFlagR</code> Flag for selection of RFFT or RIFFT(Set ifftFlagR to calculate RIFFT otherwise calculates RFFT);      
 * <code>bitReverseFlagR</code> Flag for selection of output order(Set bitReverseFlagR to output in normal order otherwise output in bit reversed order);       
 * <code>twidCoefRModifier</code> modifier for twiddle factor table which supports 128, 512, 2048 RFFT lengths with same table;      
 * <code>pTwiddleAReal</code>points to A array of twiddle coefficients; <code>pTwiddleBReal</code>points to B array of twiddle coefficients;      
 * <code>pCfft</code> points to the CFFT Instance structure. The CFFT structure also needs to be initialized, refer to arm_cfft_radix4_f32() for details regarding      
 * static initialization of cfft structure.      
 *      
 * \par Fixed-Point Behavior      
 * Care must be taken when using the fixed-point versions of the RFFT/RIFFT function.      
 * Refer to the function specific documentation below for usage guidelines.      
 */     
     
/*--------------------------------------------------------------------      
 *		Internal functions prototypes      
 *--------------------------------------------------------------------*/     
     
void arm_split_rfft_f32(     
  float32_t * pSrc,     
  uint32_t fftLen,     
  float32_t * pATable,     
  float32_t * pBTable,     
  float32_t * pDst,     
  uint32_t modifier);     
void arm_split_rifft_f32(     
  float32_t * pSrc,     
  uint32_t fftLen,     
  float32_t * pATable,     
  float32_t * pBTable,     
  float32_t * pDst,     
  uint32_t modifier);     
     
/**      
 * @addtogroup RFFT_RIFFT      
 * @{      
 */     
     
/**      
 * @brief Processing function for the floating-point RFFT/RIFFT.     
 * @param[in]  *S    points to an instance of the floating-point RFFT/RIFFT structure.     
 * @param[in]  *pSrc points to the input buffer.     
 * @param[out] *pDst points to the output buffer.     
 * @return none.     
 */     
     
void arm_rfft_f32(     
  const arm_rfft_instance_f32 * S,     
  float32_t * pSrc,     
  float32_t * pDst)     
{     
  const arm_cfft_radix4_instance_f32 *S_CFFT = S->pCfft;     
     
     
  /* Calculation of Real IFFT of input */     
  if(S->ifftFlagR == 1u)     
  {     
    /*  Real IFFT core process */     
    arm_split_rifft_f32(pSrc, S->fftLenBy2, S->pTwiddleAReal,     
                        S->pTwiddleBReal, pDst, S->twidCoefRModifier);     
     
     
    /* Complex radix-4 IFFT process */     
    arm_radix4_butterfly_inverse_f32(pDst, S_CFFT->fftLen,     
                                     S_CFFT->pTwiddle,     
                                     S_CFFT->twidCoefModifier,     
                                     S_CFFT->onebyfftLen);     
     
    /* Bit reversal process */     
    if(S->bitReverseFlagR == 1u)     
    {     
      arm_bitreversal_f32(pDst, S_CFFT->fftLen,     
                          S_CFFT->bitRevFactor, S_CFFT->pBitRevTable);     
    }     
  }     
  else     
  {     
     
    /* Calculation of RFFT of input */     
     
    /* Complex radix-4 FFT process */     
    arm_radix4_butterfly_f32(pSrc, S_CFFT->fftLen,     
                             S_CFFT->pTwiddle, S_CFFT->twidCoefModifier);     
     
    /* Bit reversal process */     
    if(S->bitReverseFlagR == 1u)     
    {     
      arm_bitreversal_f32(pSrc, S_CFFT->fftLen,     
                          S_CFFT->bitRevFactor, S_CFFT->pBitRevTable);     
    }     
     
     
    /*  Real FFT core process */     
    arm_split_rfft_f32(pSrc, S->fftLenBy2, S->pTwiddleAReal,     
                       S->pTwiddleBReal, pDst, S->twidCoefRModifier);     
  }     
     
}     
     
/**      
   * @} end of RFFT_RIFFT group      
   */     
     
/**      
 * @brief  Core Real FFT process      
 * @param[in]   *pSrc 				points to the input buffer.      
 * @param[in]   fftLen  			length of FFT.      
 * @param[in]   *pATable 			points to the twiddle Coef A buffer.      
 * @param[in]   *pBTable 			points to the twiddle Coef B buffer.      
 * @param[out]  *pDst 				points to the output buffer.      
 * @param[in]   modifier 	        twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table.     
 * @return none.      
 */     
     
void arm_split_rfft_f32(     
  float32_t * pSrc,     
  uint32_t fftLen,     
  float32_t * pATable,     
  float32_t * pBTable,     
  float32_t * pDst,     
  uint32_t modifier)     
{     
  uint32_t i, blkCnt;                            /* Loop Counter */  
  float32_t *pCoefA, *pCoefB;                    /* Temporary pointers for twiddle factors */  
  float32_t *pDst1 = &pDst[2], *pDst2 = &pDst[(4u * fftLen) - 1u];      /* temp pointers for output buffer */  
  float32_t *pSrc1 = &pSrc[2], *pSrc2 = &pSrc[(2u * fftLen) - 1u];      /* temp pointers for input buffer */  
  float32_t inR1, inR2, inR4, inI1, inI2, inI4;  
  float32_t CoefA1, CoefA2, CoefA3, CoefA4, CoefB1, CoefB2;  
  float32_t outR1, outR2, outI1, outI2;  
  
  /* Init coefficient pointers */  
  pCoefA = &pATable[modifier * 2u];  
  pCoefB = &pBTable[modifier * 2u];  
  
  blkCnt = fftLen - 1u;  
  
  /* Unroll by 2 */  
  i = blkCnt >> 1u;  
  
  while(i > 0u)     
  {     
    /*      
       outR = (pSrc[2 * i] * pATable[2 * i] - pSrc[2 * i + 1] * pATable[2 * i + 1]      
       + pSrc[2 * n - 2 * i] * pBTable[2 * i] +      
       pSrc[2 * n - 2 * i + 1] * pBTable[2 * i + 1]);      
     */     
     
    /* outI = (pIn[2 * i + 1] * pATable[2 * i] + pIn[2 * i] * pATable[2 * i + 1] +      
       pIn[2 * n - 2 * i] * pBTable[2 * i + 1] -      
       pIn[2 * n - 2 * i + 1] * pBTable[2 * i]); */     
     /*      
       outR = (pSrc[2 * i] * pATable[2 * i] - pSrc[2 * i + 1] * pATable[2 * i + 1]      
       + pSrc[2 * n - 2 * i] * pBTable[2 * i] +      
       pSrc[2 * n - 2 * i + 1] * pBTable[2 * i + 1]);      
     */     
     
    /* outI = (pIn[2 * i + 1] * pATable[2 * i] + pIn[2 * i] * pATable[2 * i + 1] +      
       pIn[2 * n - 2 * i] * pBTable[2 * i + 1] -      
       pIn[2 * n - 2 * i + 1] * pBTable[2 * i]); */     
     
	inR1 = *pSrc1;   
	inI1 = pSrc1[1];   
   
    /* read pATable[2 * i] */     
    CoefA1 = pCoefA[0];     
    /* pATable[2 * i + 1] */     
    CoefA2 = pCoefA[1];     
   
    /* read pABTable[2 * i] */     
    CoefB1 = *pCoefB;         
  
    /* update coefficient pointer */     
    pCoefA = pCoefA + (modifier * 2u);    
    pCoefB = pCoefB + (modifier * 2u);     
  
	pSrc2 -= 4u;   
   
    /* read pATable[2 * i] */     
    CoefA3 = pCoefA[0];     
    /* pATable[2 * i + 1] */     
    CoefA4 = pCoefA[1];     
   
    CoefB2 = *pCoefB;     
     
    /* update coefficient pointer */     
    pCoefA = pCoefA + (modifier * 2u);   
    pCoefB = pCoefB + (modifier * 2u);     
  
    /* pSrc[2 * i] * pATable[2 * i] */     
    outR1 = inR1 * CoefA1; 	   
	   
	inR2 = pSrc2[4];   
	inI2 = pSrc2[3];   
	     
    /* pSrc[2 * i] * CoefA2 */     
    outI1 = inR1 * CoefA2;     
    
    /* (pSrc[2 * i + 1] + pSrc[2 * fftLen - 2 * i + 1]) * CoefA2 */     
    outR1 -= (inI1 + inR2) * CoefA2;   
	     
    /* pSrc[2 * i + 1] * CoefA1 */     
    outI1 += inI1 * CoefA1;     
   
    /* pSrc[2 * fftLen - 2 * i + 1] * CoefB1 */     
    outI1 -= inR2 * CoefB1;    
   
    /* pSrc[2 * fftLen - 2 * i] * CoefA2 */     
    outI1 -= inI2 * CoefA2;     
     
    /* pSrc[2 * fftLen - 2 * i] * CoefB1 */     
    outR1 += inI2 * CoefB1;    
	  
	pDst2 -= 4u;   
   	     
	inR1 = pSrc1[2];   
	inI1 = pSrc1[3];   
  
	pSrc1 += 4u;  
  
    /* pSrc[2 * i] * pATable[2 * i] */     
    outR2 = inR1 * CoefA3; 			  	   
	   
	inR4 = pSrc2[2];   
	     
    /* pSrc[2 * i] * CoefA2 */     
    outI2 = inR1 * CoefA4;     
  
    /* (pSrc[2 * i + 1] + pSrc[2 * fftLen - 2 * i + 1]) * CoefA2 */     
    outR2 -= (inI1 + inR4) * CoefA4;   
	     
    /* pSrc[2 * i + 1] * CoefA1 */     
    outI2 += inI1 * CoefA3;     
     
	inI4 = pSrc2[1];   
   
    /* pSrc[2 * fftLen - 2 * i + 1] * CoefB1 */     
    outI2 -= inR4 * CoefB2;    
   
    /* pSrc[2 * fftLen - 2 * i] * CoefA2 */     
    outI2 -= inI4 * CoefA4;     
     
    /* pSrc[2 * fftLen - 2 * i] * CoefB1 */     
    outR2 += inI4 * CoefB2;  		  
     
    /* write output */     
    pDst1[0] = outR1;     
    pDst1[1] = outI1;     
    pDst1[2] = outR2;     
    pDst1[3] = outI2;  
	     
    /* write complex conjugate output */     
    pDst2[1] = outR2;     
    pDst2[2] = -outI2;     
    pDst2[3] = outR1;     
    pDst2[4] = -outI1;     
  
     
	pDst1 += 4u;  
  
    /* Decrement loop count */     
    i--;     
     
  }  
  
  i = blkCnt & 1u;  
    
  while(i > 0u)     
  {     
    /*      
       outR = (pSrc[2 * i] * pATable[2 * i] - pSrc[2 * i + 1] * pATable[2 * i + 1]      
       + pSrc[2 * n - 2 * i] * pBTable[2 * i] +      
       pSrc[2 * n - 2 * i + 1] * pBTable[2 * i + 1]);      
     */     
     
    /* outI = (pIn[2 * i + 1] * pATable[2 * i] + pIn[2 * i] * pATable[2 * i + 1] +      
       pIn[2 * n - 2 * i] * pBTable[2 * i + 1] -      
       pIn[2 * n - 2 * i + 1] * pBTable[2 * i]); */     
     
	 inR1 = *pSrc1;   
   
    /* read pATable[2 * i] */     
    CoefA1 = *pCoefA++;     
    /* pATable[2 * i + 1] */     
    CoefA2 = *pCoefA;     
  
	pSrc2 -= 2u;  
   
    /* pSrc[2 * i] * pATable[2 * i] */     
    outR1 = inR1 * CoefA1;   
	   
	inI1 = pSrc1[1];   
	   
	inR2 = pSrc2[2];   
	     
    /* pSrc[2 * i] * CoefA2 */     
    outI1 = inR1 * CoefA2;     
  
	pSrc1 += 2u;  
     
    /* (pSrc[2 * i + 1] + pSrc[2 * fftLen - 2 * i + 1]) * CoefA2 */     
    outR1 -= (inI1 + inR2) * CoefA2;   
	     
    /* pSrc[2 * i + 1] * CoefA1 */     
    outI1 += inI1 * CoefA1;     
   
    CoefB1 = *pCoefB;     
     
	inI2 = pSrc2[1];   
   
    /* pSrc[2 * fftLen - 2 * i + 1] * CoefB1 */     
    outI1 -= inR2 * CoefB1;    
   
    /* pSrc[2 * fftLen - 2 * i] * CoefA2 */     
    outI1 -= inI2 * CoefA2;     
     
    /* pSrc[2 * fftLen - 2 * i] * CoefB1 */     
    outR1 += inI2 * CoefB1;    
	  
	pDst2 -= 2u;   
     
    /* write output */     
    pDst1[0] = outR1;     
    pDst1[1] = outI1;     
     
    /* write complex conjugate output */     
    pDst2[2] = -outI1;     
    pDst2[1] = outR1;     
	  
	pDst1 += 2u;  
     
    /* update coefficient pointer */     
    pCoefB = pCoefB + (modifier * 2u);     
    pCoefA = pCoefA + ((modifier * 2u) - 1u);     
     
    /* Decrement loop count */     
    i--;     
     
  }     
     
  pDst[2u * fftLen] = pSrc[0] - pSrc[1];     
  pDst[(2u * fftLen) + 1u] = 0.0f;     
     
  pDst[0] = pSrc[0] + pSrc[1];     
  pDst[1] = 0.0f;     
     
}     
     
     
/**      
 * @brief  Core Real IFFT process      
 * @param[in]   *pSrc 				points to the input buffer.      
 * @param[in]   fftLen  			length of FFT.     
 * @param[in]   *pATable 			points to the twiddle Coef A buffer.     
 * @param[in]   *pBTable 			points to the twiddle Coef B buffer.     
 * @param[out]  *pDst 				points to the output buffer.     
 * @param[in]   modifier 	        twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table.      
 * @return none.      
 */     
     
void arm_split_rifft_f32(     
  float32_t * pSrc,     
  uint32_t fftLen,     
  float32_t * pATable,     
  float32_t * pBTable,     
  float32_t * pDst,     
  uint32_t modifier)     
{    
  uint32_t i, blkCnt;                            /* Loop Counter */  
  float32_t inVal1, inVal2, inVal3;    
  float32_t outR, outI;                          /* Temporary variables for output */     
  float32_t *pCoefA, *pCoefB;                    /* Temporary pointers for twiddle factors */     
  float32_t *pSrc1 = &pSrc[0], *pSrc2 = &pSrc[(2u * fftLen) + 1u];     
  float32_t CoefA1, CoefA2, CoefB1;	  /* Temporary variables for twiddle coefficients */   
  
  pCoefA = &pATable[0];     
  pCoefB = &pBTable[0];     
     
  blkCnt = fftLen - 1u;  
  
  /* Unroll by 2 */  
  i = blkCnt >> 1u;  
  
  while(i > 0u)     
  {     
    /*      
       outR = (pSrc[2 * i] * pATable[2 * i] - pSrc[2 * i + 1] * pATable[2 * i + 1]      
       + pSrc[2 * n - 2 * i] * pBTable[2 * i] +      
       pSrc[2 * n - 2 * i + 1] * pBTable[2 * i + 1]);      
     */     
     
    /* outI = (pIn[2 * i + 1] * pATable[2 * i] + pIn[2 * i] * pATable[2 * i + 1] +      
       pIn[2 * n - 2 * i] * pBTable[2 * i + 1] -      
       pIn[2 * n - 2 * i + 1] * pBTable[2 * i]); */     
     
    /*      
       outR = (pIn[2 * i] * pATable[2 * i] + pIn[2 * i + 1] * pATable[2 * i + 1] +      
       pIn[2 * n - 2 * i] * pBTable[2 * i] -      
       pIn[2 * n - 2 * i + 1] * pBTable[2 * i + 1]);      
     
       outI = (pIn[2 * i + 1] * pATable[2 * i] - pIn[2 * i] * pATable[2 * i + 1] -      
       pIn[2 * n - 2 * i] * pBTable[2 * i + 1] -      
       pIn[2 * n - 2 * i + 1] * pBTable[2 * i]);      
     
     */     
     
	inVal1 = pSrc1[0];   
   
    CoefA1 = pCoefA[0];     
    CoefA2 = pCoefA[1];     
    					   
    CoefB1 = *pCoefB;       
     
    /* update coefficient pointer */     
    pCoefB = pCoefB + (modifier * 2u);     
    pCoefA = pCoefA + (modifier * 2u);   
  
 	pSrc2 -= 2u;  
    /* outR = (pSrc[2 * i] * CoefA1 */     
    outR =  inVal1 * CoefA1;     
     
	inVal2 = pSrc1[1];   
   
	inVal3 = pSrc2[2];   
   
    /* - pSrc[2 * i] * CoefA2 */     
    outI = -(inVal1) * CoefA2;     
     
    /* (pSrc[2 * i + 1] + pSrc[2 * fftLen - 2 * i + 1]) * CoefA2 */     
    outR += (inVal2 + inVal3) * CoefA2;   
	   
	pSrc1 += 2u;     
     
    /* pSrc[2 * i + 1] * CoefA1 */     
    outI += (inVal2) * CoefA1;     
     
	inVal1 = pSrc2[1];   
   
    /* - pSrc[2 * fftLen - 2 * i + 1] * CoefB1 */     
    outI -= inVal3 * CoefB1;     
   
    /* pSrc[2 * fftLen - 2 * i] * CoefB1 */     
    outR += inVal1 * CoefB1;     
     
    /* pSrc[2 * fftLen - 2 * i] * CoefA2 */     
    outI += inVal1 * CoefA2;     
     
    /* write output */     
    pDst[0] = outR;     
    pDst[1] = outI;     
  
	inVal1 = pSrc1[0];   
   
    CoefA1 = pCoefA[0];     
    CoefA2 = pCoefA[1];     
   
    CoefB1 = *pCoefB;     
     
    /* update coefficient pointer */     
    pCoefB = pCoefB + (modifier * 2u);     
    pCoefA = pCoefA + (modifier * 2u);   
  
 	pSrc2 -= 2u;  
    /* outR = (pSrc[2 * i] * CoefA1 */     
    outR =  inVal1 * CoefA1;     
     
	inVal2 = pSrc1[1];   
   
	inVal3 = pSrc2[2];   
   
    /* - pSrc[2 * i] * CoefA2 */     
    outI = -(inVal1) * CoefA2;     
     
    /* (pSrc[2 * i + 1] + pSrc[2 * fftLen - 2 * i + 1]) * CoefA2 */     
    outR += (inVal2 + inVal3) * CoefA2;   
	   
	pSrc1 += 2u;     
     
    /* pSrc[2 * i + 1] * CoefA1 */     
    outI += (inVal2) * CoefA1;     
        
	inVal1 = pSrc2[1];   
   
    /* - pSrc[2 * fftLen - 2 * i + 1] * CoefB1 */     
    outI -= inVal3 * CoefB1;     
   
    /* pSrc[2 * fftLen - 2 * i] * CoefB1 */     
    outR += inVal1 * CoefB1;     
     
    /* pSrc[2 * fftLen - 2 * i] * CoefA2 */     
    outI += inVal1 * CoefA2;     
     
    /* write output */     
    pDst[2] = outR;     
    pDst[3] = outI;     
  
	pDst += 4u;  
  
	/* decrement loop counter */  
    i--;     
     
  }  
  
  i = blkCnt & 1u;  
    
  while(i > 0u)    
  {     
    /*      
       outR = (pIn[2 * i] * pATable[2 * i] + pIn[2 * i + 1] * pATable[2 * i + 1] +      
       pIn[2 * n - 2 * i] * pBTable[2 * i] -      
       pIn[2 * n - 2 * i + 1] * pBTable[2 * i + 1]);      
     
       outI = (pIn[2 * i + 1] * pATable[2 * i] - pIn[2 * i] * pATable[2 * i + 1] -      
       pIn[2 * n - 2 * i] * pBTable[2 * i + 1] -      
       pIn[2 * n - 2 * i + 1] * pBTable[2 * i]);      
     
     */     
     
	inVal1 = pSrc1[0];   
   
    CoefA1 = *pCoefA++;     
    CoefA2 = *pCoefA;     
     
 	pSrc2 -= 2u;  
    /* outR = (pSrc[2 * i] * CoefA1 */     
    outR =  inVal1 * CoefA1;     
     
	inVal2 = pSrc1[1];   
   
	inVal3 = pSrc2[2];   
   
    /* - pSrc[2 * i] * CoefA2 */     
    outI = -(inVal1) * CoefA2;     
     
    /* (pSrc[2 * i + 1] + pSrc[2 * fftLen - 2 * i + 1]) * CoefA2 */     
    outR += (inVal2 + inVal3) * CoefA2;   
	   
	pSrc1 += 2u;     
     
    /* pSrc[2 * i + 1] * CoefA1 */     
    outI += (inVal2) * CoefA1;     
     
   
    CoefB1 = *pCoefB;     
     
	inVal1 = pSrc2[1];   
   
    /* - pSrc[2 * fftLen - 2 * i + 1] * CoefB1 */     
    outI -= inVal3 * CoefB1;     
   
    /* pSrc[2 * fftLen - 2 * i] * CoefB1 */     
    outR += inVal1 * CoefB1;     
     
    /* pSrc[2 * fftLen - 2 * i] * CoefA2 */     
    outI += inVal1 * CoefA2;     
     
    /* write output */     
    pDst[0] = outR;     
    pDst[1] = outI;     
  
	pDst += 2u;  
     
    /* update coefficient pointer */     
    pCoefB = pCoefB + (modifier * 2u);     
    pCoefA = pCoefA + ((modifier * 2u) - 1u);     
     
    /* Decrement loop count */     
    i--;     
  }     
     
}     
     
