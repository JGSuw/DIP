/** @file Device_RM46.h
*   @brief This file defines the FLASH details
*   @date 25.April.2014
*   @version 03.09.00
*   
*/

/* (c) Texas Instruments 2009-2014, All rights reserved. */

#ifndef DEVICE_RM46_H
#define DEVICE_RM46_H


/** @def DEVICE_CONFIGURATION_VERSION
*   @brief Device Configuration Version
*
*   @note Indicates the current version of the device files
*/
#define DEVICE_CONFIGURATION_VERSION 0U             /* Indicates the current version of the device files */

/** @def DEVICE_NUMBER_OF_FLASH_BANKS
*   @brief Number of Flash Banks
*
*   @note Defines the number of Flash Banks on the device
*/
#define DEVICE_NUMBER_OF_FLASH_BANKS 1U             /* Defines the number of Flash Banks on the device */


/** @def DEVICE_BANK_MAX_NUMBER_OF_SECTORS
*   @brief Maximum number of Sectors
*
*   @note Defines the maxium number of sectors in all banks
*/
#define DEVICE_BANK_MAX_NUMBER_OF_SECTORS 4U        /* Defines the maxium number of sectors in all banks */

/** @def DEVICE_BANK1_NUMBER_OF_SECTORS
*   @brief Number of Sectors
*
*   @note Defines the number of sectors in bank1
*/
#define DEVICE_BANK1_NUMBER_OF_SECTORS 4U           /* Defines the number of sectors in bank1 */


/** @def DEVICE_NUMBER_OF_READ_CYCLE_THRESHOLDS
*   @brief Number of Sectors
*
*   @note Defines the number of Read Cycle Thresholds 
*/
#define DEVICE_NUMBER_OF_READ_CYCLE_THRESHOLDS 4U   /* Defines the number of Read Cycle Thresholds */


/* Include Files */
#ifndef _PLATFORM_TYPES_H_
#define _PLATFORM_TYPES_H_
#endif
#include "F021.h"
#include "Std_Types.h"
#include "Device_Types.h"

#endif /* DEVICE_RM46_H */

/* End of File */
