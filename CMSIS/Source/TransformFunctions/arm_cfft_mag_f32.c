/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_cfft_mag_f32.c      
*      
* Description:	Floating point processing function for Magnitude calculation of CFFT Output        
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
 * @defgroup CFFT_MAG Complex FFT Magnitude Functions      
 *      
 * \par      
 * Caluclates the Magnitude of Complex Fast Fourier Transform(CFFT) output.      
 * \par      
 * This set of functions implements CFFT + Magnitude     
 * for Q15, Q31, and floating-point data types.       
 *      
 * \par      
 * The functions operate on block of input and output data and each call to the function processes      
 * <code>2*fftLen</code> samples through the transform.  <code>pSrc</code>  points to In-place arrays containing <code>2*fftLen</code> values.      
 * \par     
 * The <code>pdst</code> points to the array of buffer of size <code>fftLen</code>. 
 * <pre> {real[0], real[1],..} </pre>      
 *      
 * \par Lengths supported by the transform:     
 * \par      
 * Internally, the function utilize a radix-4 decimation in frequency(DIF) algorithm      
 * and the size of the FFT supported are of the lengths [16, 64, 256, 1024].     
 *       
 *   
 * \par      
 * Refer to the function <code>arm_cfft_radix4_f32()</code> for a detailed description CFFT F32.    
 *      
    
 *     
 * \par Fixed-Point Behavior      
 * Care must be taken when using the fixed-point versions of the CFFT/CIFFT function.      
 * Refer to the function specific documentation below for usage guidelines.      
 */     
     
     
/**      
 * @addtogroup CFFT_MAG      
 * @{      
 */     
     
/**      
 * @details      
 * @brief Processing function for the floating-point CFFT Magnitude.     
 * @param[in]      *S    points to an instance of the floating-point CFFT/CIFFT structure.     
 * @param[in, out] *pSrc points to the complex data buffer of size <code>2*fftLen</code>. Processing occurs in-place.     
 * @return none.     
 */     
     
void arm_cfft_mag_f32(     
  const arm_cfft_radix4_instance_f32 * S,     
  float32_t * pSrc)     
{     
     
  /*  Complex FFT Magnituderadix-4  */     
  arm_cfft_mag_butterfly_f32(pSrc, S->fftLen, S->pTwiddle,     
                             S->twidCoefModifier);     
     
  if(S->bitReverseFlag == 1u)     
  {     
    /*  Bit Reversal */     
    arm_cfft_mag_bitreversal_f32(pSrc, S->fftLen, S->bitRevFactor, S->pBitRevTable);     
  }     
     
}     
     
     
/**      
 * @} end of CFFT_CIFFT group      
 */     
     
     
     
/* ----------------------------------------------------------------------      
** Internal helper function used by the FFTs      
** ------------------------------------------------------------------- */     
     
/*      
 * @brief  Core function for the floating-point CFFT butterfly process.     
 * @param[in, out] *pSrc            points to the in-place buffer of floating-point data type.     
 * @param[in]      fftLen           length of the FFT.     
 * @param[in]      *pCoef           points to the twiddle coefficient buffer.     
 * @param[in]      twidCoefModifier twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table.     
 * @return none.     
 */     
     
void arm_cfft_mag_butterfly_f32(     
  float32_t * pSrc,     
  uint16_t fftLen,     
  float32_t * pCoef,     
  uint16_t twidCoefModifier)     
{     
     
  float32_t co1, co2, co3, si1, si2, si3;     
  uint32_t ia1, ia2, ia3;     
  uint32_t i0, i1, i2, i3;     
  uint32_t n1, n2, j, k;   
    
  float32_t xaIn, yaIn, xbIn, ybIn, xcIn, ycIn, xdIn, ydIn;  
  float32_t Xaplusc, Xbplusd, Yaplusc, Ybplusd, Xaminusc, Xbminusd, Yaminusc, Ybminusd;  
  float32_t Xb12C_out, Yb12C_out, Xc12C_out, Yc12C_out, Xd12C_out, Yd12C_out;  
  float32_t Xb12_out, Yb12_out, Xc12_out, Yc12_out, Xd12_out, Yd12_out;  
  float32_t Xa12_out, Ya12_out;  
  float32_t *ptr1;    
     
  /*  Initializations for the first stage */     
  n2 = fftLen;     
  n1 = n2;     
     
  /* n2 = fftLen/4 */     
  n2 >>= 2u;     
  i0 = 0u;     
  ia1 = 0u;     
     
  j = n2;     
     
  /*  Calculation of first stage */     
  do     
  {     
    /*  index calculation for the input as, */     
    /*  pSrc[i0 + 0], pSrc[i0 + fftLen/4], pSrc[i0 + fftLen/2], pSrc[i0 + 3fftLen/4] */     
    i1 = i0 + n2;     
    i2 = i1 + n2;     
    i3 = i2 + n2;    
	  
	xaIn = pSrc[(2u * i0)];  
	yaIn = pSrc[(2u * i0) + 1u];  
  
	xcIn = pSrc[(2u * i2)];  
	ycIn = pSrc[(2u * i2) + 1u];  
  
	xbIn = pSrc[(2u * i1)];  
	ybIn = pSrc[(2u * i1) + 1u];  
  
	xdIn = pSrc[(2u * i3)];  
	ydIn = pSrc[(2u * i3) + 1u];  
  
	/* xa + xc */  
	Xaplusc = xaIn + xcIn;  
	/* xb + xd */  
	Xbplusd = xbIn + xdIn;  
	/* ya + yc */  
	Yaplusc = yaIn + ycIn;  
	/* yb + yd */  
	Ybplusd	= ybIn + ydIn;  
  
	/*  index calculation for the coefficients */     
    ia2 = ia1 + ia1;     
    co2 = pCoef[ia2 * 2u];     
    si2 = pCoef[(ia2 * 2u) + 1u];   
  
	/* xa - xc */  
	Xaminusc = xaIn - xcIn;  
	/* xb - xd */  
	Xbminusd = xbIn - xdIn;  
	/* ya - yc */  
	Yaminusc = yaIn - ycIn;  
	/* yb + yd */  
	Ybminusd = ybIn - ydIn;  
  
    /* xa' = xa + xb + xc + xd */  
	pSrc[(2u * i0)] = Xaplusc + Xbplusd;  
    /* ya' = ya + yb + yc + yd */  
	pSrc[(2u * i0) + 1u] = Yaplusc + Ybplusd;  
  
    /* (xa - xc) + (yb - yd) */  
    Xb12C_out = (Xaminusc + Ybminusd);  
    /* (ya - yc) + (xb - xd) */  
    Yb12C_out = (Yaminusc - Xbminusd);  
    /* (xa + xc) - (xb + xd) */  
    Xc12C_out = (Xaplusc - Xbplusd);  
    /* (ya + yc) - (yb + yd) */  
    Yc12C_out = (Yaplusc - Ybplusd);  
    /* (xa - xc) - (yb - yd) */  
    Xd12C_out = (Xaminusc - Ybminusd);  
    /* (ya - yc) + (xb - xd) */  
    Yd12C_out = (Xbminusd + Yaminusc);  
  
	co1 = pCoef[ia1 * 2u];     
    si1 = pCoef[(ia1 * 2u) + 1u];  
  
	/*  index calculation for the coefficients */     
    ia3 = ia2 + ia1;     
    co3 = pCoef[ia3 * 2u];     
    si3 = pCoef[(ia3 * 2u) + 1u];    
  
	Xb12_out = Xb12C_out * co1;  
	Yb12_out = Yb12C_out * co1;  
	Xc12_out = Xc12C_out * co2;  
	Yc12_out = Yc12C_out * co2;  
	Xd12_out = Xd12C_out * co3;  
	Yd12_out = Yd12C_out * co3;  
  
	/* xb' = (xa+yb-xc-yd)co1 + (ya-xb-yc+xd)(si1) */     
	Xb12_out += Yb12C_out  * si1;  
    /* yb' = (ya-xb-yc+xd)co1 - (xa+yb-xc-yd)(si1) */     
	Yb12_out -= Xb12C_out * si1;  
	/* xc' = (xa-xb+xc-xd)co2 + (ya-yb+yc-yd)(si2) */     
	Xc12_out += Yc12C_out  * si2;  
    /* yc' = (ya-yb+yc-yd)co2 - (xa-xb+xc-xd)(si2) */     
	Yc12_out -=  Xc12C_out * si2;  
    /* xd' = (xa-yb-xc+yd)co3 + (ya+xb-yc-xd)(si3) */     
	Xd12_out += Yd12C_out  * si3;  
    /* yd' = (ya+xb-yc-xd)co3 - (xa-yb-xc+yd)(si3) */  
	Yd12_out -=  Xd12C_out * si3;  
  
  
	/* xc' = (xa-xb+xc-xd)co2 + (ya-yb+yc-yd)(si2) */     
    pSrc[2u * i1] = Xc12_out;     
     
    /* yc' = (ya-yb+yc-yd)co2 - (xa-xb+xc-xd)(si2) */     
    pSrc[(2u * i1) + 1u] = Yc12_out;  
  
	/* xb' = (xa+yb-xc-yd)co1 + (ya-xb-yc+xd)(si1) */     
    pSrc[2u * i2] = Xb12_out;     
     
    /* yb' = (ya-xb-yc+xd)co1 - (xa+yb-xc-yd)(si1) */     
    pSrc[(2u * i2) + 1u] = Yb12_out;  
  
    /* xd' = (xa-yb-xc+yd)co3 + (ya+xb-yc-xd)(si3) */     
    pSrc[2u * i3] = Xd12_out;     
     
    /* yd' = (ya+xb-yc-xd)co3 - (xa-yb-xc+yd)(si3) */     
    pSrc[(2u * i3) + 1u] = Yd12_out;   
     
    /*  Twiddle coefficients index modifier */     
    ia1 = ia1 + twidCoefModifier;     
     
    /*  Updating input index */     
    i0 = i0 + 1u;     
     
  }     
  while(--j);     
     
  twidCoefModifier <<= 2u;     
     
  /*  Calculation of second stage to excluding last stage */     
  for (k = fftLen / 4; k > 4u; k >>= 2u)     
  {     
    /*  Initializations for the first stage */     
    n1 = n2;     
    n2 >>= 2u;     
    ia1 = 0u;     
     
    /*  Calculation of first stage */     
    for (j = 0u; j <= (n2 - 1u); j++)     
    {     
      /*  index calculation for the coefficients */     
      ia2 = ia1 + ia1;     
      ia3 = ia2 + ia1;     
      co1 = pCoef[ia1 * 2u];     
      si1 = pCoef[(ia1 * 2u) + 1u];     
      co2 = pCoef[ia2 * 2u];     
      si2 = pCoef[(ia2 * 2u) + 1u];     
      co3 = pCoef[ia3 * 2u];     
      si3 = pCoef[(ia3 * 2u) + 1u];     
     
      /*  Twiddle coefficients index modifier */     
      ia1 = ia1 + twidCoefModifier;     
     
      for (i0 = j; i0 < fftLen; i0 += n1)     
      {     
        /*  index calculation for the input as, */     
        /*  pSrc[i0 + 0], pSrc[i0 + fftLen/4], pSrc[i0 + fftLen/2], pSrc[i0 + 3fftLen/4] */     
        i1 = i0 + n2;     
        i2 = i1 + n2;     
        i3 = i2 + n2;     
  
		xaIn = pSrc[(2u * i0)];  
		yaIn = pSrc[(2u * i0) + 1u];  
	  
		xbIn = pSrc[(2u * i1)];  
		ybIn = pSrc[(2u * i1) + 1u];  
	  
		xcIn = pSrc[(2u * i2)];  
		ycIn = pSrc[(2u * i2) + 1u];  
	  
		xdIn = pSrc[(2u * i3)];  
		ydIn = pSrc[(2u * i3) + 1u];  
	  
        /* xa - xc */  
		Xaminusc = xaIn - xcIn;  
        /* (xb - xd) */  
		Xbminusd = xbIn - xdIn;  
        /* ya - yc */  
		Yaminusc = yaIn - ycIn;  
        /* (yb - yd) */  
		Ybminusd = ybIn - ydIn;  
	  
        /* xa + xc */  
		Xaplusc = xaIn + xcIn;  
        /* xb + xd */  
		Xbplusd = xbIn + xdIn;  
        /* ya + yc */  
		Yaplusc = yaIn + ycIn;  
        /* yb + yd */  
		Ybplusd	= ybIn + ydIn;  
	  
        /* (xa - xc) + (yb - yd) */  
	    Xb12C_out = (Xaminusc + Ybminusd);  
        /* (ya - yc) -  (xb - xd) */  
	    Yb12C_out = (Yaminusc - Xbminusd);  
        /* xa + xc -(xb + xd) */  
	    Xc12C_out = (Xaplusc - Xbplusd);  
        /* (ya + yc) - (yb + yd) */  
	    Yc12C_out = (Yaplusc - Ybplusd);  
        /* (xa - xc) - (yb - yd) */  
	    Xd12C_out = (Xaminusc - Ybminusd);  
        /* (ya - yc) +  (xb - xd) */  
	    Yd12C_out = (Xbminusd + Yaminusc);  
  
		pSrc[(2u * i0)] = Xaplusc + Xbplusd;  
		pSrc[(2u * i0) + 1u] = Yaplusc + Ybplusd;  
	  
		Xb12_out = Xb12C_out * co1;  
		Yb12_out = Yb12C_out * co1;  
		Xc12_out = Xc12C_out * co2;  
		Yc12_out = Yc12C_out * co2;  
		Xd12_out = Xd12C_out * co3;  
		Yd12_out = Yd12C_out * co3;  
	  
		/* xb' = (xa+yb-xc-yd)co1 + (ya-xb-yc+xd)(si1) */     
		Xb12_out += Yb12C_out  * si1;  
	    /* yb' = (ya-xb-yc+xd)co1 - (xa+yb-xc-yd)(si1) */     
		Yb12_out -= Xb12C_out * si1;  
		/* xc' = (xa-xb+xc-xd)co2 + (ya-yb+yc-yd)(si2) */     
		Xc12_out += Yc12C_out  * si2;  
	    /* yc' = (ya-yb+yc-yd)co2 - (xa-xb+xc-xd)(si2) */     
		Yc12_out -=  Xc12C_out * si2;  
	    /* xd' = (xa-yb-xc+yd)co3 + (ya+xb-yc-xd)(si3) */     
		Xd12_out += Yd12C_out  * si3;  
	    /* yd' = (ya+xb-yc-xd)co3 - (xa-yb-xc+yd)(si3) */     
		Yd12_out -=  Xd12C_out * si3;  
  
		/* xc' = (xa-xb+xc-xd)co2 + (ya-yb+yc-yd)(si2) */     
	    pSrc[2u * i1] = Xc12_out;     
	     
	    /* yc' = (ya-yb+yc-yd)co2 - (xa-xb+xc-xd)(si2) */     
	    pSrc[(2u * i1) + 1u] = Yc12_out;  
	  
		/* xb' = (xa+yb-xc-yd)co1 + (ya-xb-yc+xd)(si1) */     
	    pSrc[2u * i2] = Xb12_out;     
	     
	    /* yb' = (ya-xb-yc+xd)co1 - (xa+yb-xc-yd)(si1) */     
	    pSrc[(2u * i2) + 1u] = Yb12_out;  
	  
	    /* xd' = (xa-yb-xc+yd)co3 + (ya+xb-yc-xd)(si3) */     
	    pSrc[2u * i3] = Xd12_out;     
	     
	    /* yd' = (ya+xb-yc-xd)co3 - (xa-yb-xc+yd)(si3) */     
	    pSrc[(2u * i3) + 1u] = Yd12_out;   
		   
      }     
    }     
    twidCoefModifier <<= 2u;     
  }  
  
  j = fftLen >> 2;   
  ptr1 = &pSrc[0];     
  
   /*  Calculations of last stage */   
  do   
  {  
    
  	xaIn = ptr1[0];  
	xcIn = ptr1[4];  
	yaIn = ptr1[1];  
	ycIn = ptr1[5];  
  
    /* xa + xc */  
	Xaplusc = xaIn + xcIn;  
  
	xbIn = ptr1[2];  
  
    /* xa - xc */  
	Xaminusc = xaIn - xcIn;  
  
	xdIn = ptr1[6];  
  
    /* ya + yc */  
	Yaplusc = yaIn +  ycIn;  
  
	ybIn = ptr1[3];  
  
    /* ya - yc */  
	Yaminusc = yaIn -  ycIn;  
  
	ydIn = ptr1[7];  
  
    /* xb + xd */  
	Xbplusd = xbIn + xdIn;  
  
    /* yb + yd */  
	Ybplusd	= ybIn +  ydIn;  
  
    /* xa' = xa + xb + xc + xd */  
	Xa12_out = (Xaplusc + Xbplusd);  
  
    /* (xb-xd) */  
	Xbminusd = xbIn - xdIn;  
  
    /* ya' = ya + yb + yc + yd */  
  	Ya12_out = (Yaplusc + Ybplusd);  
  
    /* (yb-yd) */  
	Ybminusd = ybIn -  ydIn;   
  
    /* xc' = (xa-xb+xc-xd) */  
	Xc12_out = (Xaplusc - Xbplusd);  
    /* yc' = (ya-yb+yc-yd) */  
  	Yc12_out = (Yaplusc - Ybplusd);  
    /* xb' = (xa+yb-xc-yd) */  
  	Xb12_out = (Xaminusc + Ybminusd);  
    /* yb' = (ya-xb-yc+xd) */  
  	Yb12_out = (Yaminusc - Xbminusd);  
    /* xd' = (xa-yb-xc+yd)) */  
  	Xd12_out = (Xaminusc - Ybminusd);  
    /* yd' = (ya+xb-yc-xd) */  
  	Yd12_out = (Xbminusd + Yaminusc);  
  
	/* calculating magnitude to output */  
	Xa12_out = Xa12_out * Xa12_out;  
	Ya12_out = Ya12_out * Ya12_out;  
	  
	Xc12_out = Xc12_out * Xc12_out;  
	Yc12_out = Yc12_out * Yc12_out;  
	  
	Xb12_out = Xb12_out * Xb12_out;  
	Yb12_out = Yb12_out * Yb12_out;  
	  
	Xd12_out = Xd12_out * Xd12_out;  
	Yd12_out = Yd12_out * Yd12_out;  
  
	arm_sqrt_f32(Xa12_out + Ya12_out, pSrc++);  
	arm_sqrt_f32(Xc12_out + Yc12_out, pSrc++);  
	arm_sqrt_f32(Xb12_out + Yb12_out, pSrc++);  
	arm_sqrt_f32(Xd12_out + Yd12_out, pSrc++);  
  
	  
	/* increment pointer by 8 */  
	ptr1 = ptr1 + 8u;  
  
  }while(--j);    
      
}     
  
/*      
 * @brief  In-place bit reversal function.     
 * @param[in, out] *pSrc        points to the in-place buffer of floating-point data type.     
 * @param[in]      fftSize      length of the FFT.     
 * @param[in]      bitRevFactor bit reversal modifier that supports different size FFTs with the same bit reversal table.     
 * @param[in]      *pBitRevTab  points to the bit reversal table.     
 * @return none.     
 */     
     
void arm_cfft_mag_bitreversal_f32(     
  float32_t * pSrc,     
  uint16_t fftSize,     
  uint16_t bitRevFactor,     
  uint16_t * pBitRevTab)     
{     
  uint16_t fftLenBy2, fftLenBy2p1;     
  uint16_t i, j;     
  float32_t in;     
     
  /*  Initializations */     
  j = 0u;     
  fftLenBy2 = fftSize >> 1u;     
  fftLenBy2p1 = (fftSize >> 1u) + 1u;     
     
  /* Bit Reversal Implementation */     
  for (i = 0u; i <= (fftLenBy2 - 2u); i += 2u)     
  {     
    if(i < j)     
    {     
      /*  pSrc[i] <-> pSrc[j]; */     
      in = pSrc[i];     
      pSrc[i] = pSrc[j];     
      pSrc[j] = in;     
     
      /*  pSrc[i+fftLenBy2p1] <-> pSrc[j+fftLenBy2p1] */     
      in = pSrc[(i + fftLenBy2p1)];     
      pSrc[(i + fftLenBy2p1)] = pSrc[(j + fftLenBy2p1)];     
      pSrc[(j + fftLenBy2p1)] = in;     
     
    }     
     
    /*  pSrc[i+1u] <-> pSrc[j+1u] */     
    in = pSrc[ (i + 1u)];     
    pSrc[(i + 1u)] = pSrc[(j + fftLenBy2)];     
    pSrc[(j + fftLenBy2)] = in;     
     
    /*  Reading the index for the bit reversal */     
    j = *pBitRevTab;     
     
    /*  Updating the bit reversal index depending on the fft length  */     
    pBitRevTab += bitRevFactor;     
  }     
}     
