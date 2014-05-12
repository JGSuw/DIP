/** @file sys_common.h
*   @brief Common Header File
*   @date 15.Mar.2012
*   @version 03.01.00
*   
*   This file contains:
*   - General Definitions
*   .
*   which are relevant for all drivers.
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */


#ifndef __SYS_COMMON_H__
#define __SYS_COMMON_H__

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* General Definitions */

/** @def NULL
*   @brief NULL definition
*/
#ifndef NULL
    #define NULL ((void *) 0U)
#endif

/** @def TRUE
*   @brief definition for TRUE
*/
#ifndef TRUE
    #define TRUE 1U
#endif

/** @def FALSE
*   @brief BOOLEAN definition for FALSE
*/
#ifndef FALSE
    #define FALSE 0U
#endif

#ifndef _UINT64_T_DECLARED
typedef unsigned long long uint64_t;
#define	_UINT64_T_DECLARED
#endif

#ifndef _UINT32_T_DECLARED
typedef unsigned int uint32_t;
#define	_UINT32_T_DECLARED
#endif

#ifndef _UINT16_T_DECLARED
typedef unsigned short uint16_t;
#define	_UINT16_T_DECLARED
#endif

#ifndef _UINT8_T_DECLARED
typedef unsigned char uint8_t;
#define	_UINT8_T_DECLARED
#endif

#ifndef _BOOLEAN_T_DECLARED
typedef unsigned char boolean_t;
typedef unsigned char tBoolean;
#define	_BOOLEAN_T_DECLARED
#endif

/** @enum Loopbacktype
*   @brief Loopback type definition
*/
/** @typedef Loopbacktype_t
*   @brief Loopback type Type Definition
*
*   This type is used to select the module Loopback type Digital or Analog loopback.
*/
typedef enum Loopbacktype 
{
    Digital = 0, 
    Analog = 1
}Loopbacktype_t;


/* USER CODE BEGIN (1) */
/* USER CODE END */

//*****************************************************************************
//
// The ASSERT macro, which does the actual assertion checking.  Typically, this
// will be for procedure arguments.
//
//*****************************************************************************
#ifdef DEBUG
#define ASSERT(expr) {                                      \
                         if(!(expr))                        \
                         {                                  \
                             __error__(__FILE__, __LINE__); \
                         }                                  \
                     }
#else
#define ASSERT(expr)
#endif

/* USER CODE BEGIN (2) */
/* USER CODE END */

#endif
