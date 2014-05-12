/**************************************************************************//**
 * @file     type_defs.h
 * @brief    Cortex-R4 Type defines Header File
 * @version  V0.1
 * @date     26. November 2011
 *
 * Copyright (C) 2010 ARM Limited. All rights reserved.
 */

#ifndef _TYPE_DEFS_H
#define _TYPE_DEFS_H

#ifdef	__cplusplus
extern "C"
{
#endif

  /**
   * @brief 8-bit integer data type.
   */
 typedef signed int int32_t;
 typedef unsigned int uint32_t;

   /**
   * @brief 8-bit integer data type.
   */
 typedef signed char int8_t;
 typedef unsigned char uint8_t;

    /**
   * @brief 8-bit integer data type.
   */
 typedef signed short int16_t;
 typedef unsigned short uint16_t;

  
 #if defined (CCS )
 typedef long long __int64;
 #define __packed	 
 #endif
 
 #if defined (__GNUC__)
 typedef long long __int64;
 #define __packed	__attribute__ ((packed))	 
 #endif
 
 typedef __int64 int64_t ;

 typedef unsigned long long uint64_t;


  /**
   * @brief 8-bit fractional data type in 1.7 format.
   */
  typedef int8_t q7_t;

  /**
   * @brief 16-bit fractional data type in 1.15 format.
   */
  typedef int16_t q15_t;

  /**
   * @brief 32-bit fractional data type in 1.31 format.
   */
  typedef int32_t q31_t;

  /**
   * @brief 64-bit fractional data type in 1.63 format.
   */
  typedef int64_t q63_t;

  /**
   * @brief 32-bit floating-point type definition.
   */
  typedef float float32_t;

  /**
   * @brief 64-bit floating-point type definition.
   */
  typedef double float64_t;

#ifdef __cplusplus
}
#endif

#endif /* _TYPE_DEFS_H */

