/** @file sys_common.h
*   @brief Common Header File
*   @date 15.December.2011
*   @version 03.00.00
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


/* General Definitios */

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

/* USER CODE BEGIN (1) */
/* USER CODE END */

#endif
