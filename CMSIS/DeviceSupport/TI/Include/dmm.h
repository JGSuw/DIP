/** @file dmm.h
*   @brief DMM Driver Definition File
*   @date 15.December.2011
*   @version 03.00.00
*   
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */


#ifndef __DMM_H__
#define __DMM_H__

#include "sys_common.h"
#include "gio.h"


/** @struct dmmBase
*   @brief DMM Base Register Definition
*
*   This structure is used to access the DMM module egisters.
*/
/** @typedef dmmBASE_t
*   @brief DMM Register Frame Type Definition
*
*   This type is used to access the DMM Registers.
*/

typedef volatile struct dmmBase
{
    uint32_t  GLBCTRL;    /**< 0x0000: Global control register 0         */
    uint32_t  INTSET;     /**< 0x0004: DMM Interrupt Set Register        */    
    uint32_t  INTCLR;     /**< 0x0008: DMM Interrupt Clear Register      */
    uint32_t  INTLVL;     /**< 0x000C: DMM Interrupt Level Register      */    
    uint32_t  INTFLG;     /**< 0x0010: DMM Interrupt Flag Register       */
    uint32_t  OFF1;       /**< 0x0014: DMM Interrupt Offset 1 Register           */
    uint32_t  OFF2;       /**< 0x0018: DMM Interrupt Offset 2 Register           */
    uint32_t  DDMDEST;    /**< 0x001C: DMM Direct Data Mode Destination Register                */
    uint32_t  DDMBL;      /**< 0x0020: DMM Direct Data Mode Blocksize Register           */
    uint32_t  DDMPT;      /**< 0x0024: DMM Direct Data Mode Pointer Register        */
    uint32_t  INTPT;      /**< 0x0028: DMM Direct Data Mode Interrupt Pointer Register     */
    uint32_t  DEST0REG1;  /**< 0x002C: DMM Destination 0 Region 1           */
    uint32_t  DEST0BL1;   /**< 0x0030: DMM Destination 0 Blocksize 1                     */
    uint32_t  DEST0REG2;  /**< 0x0034: DMM Destination 0 Region 2                  */
    uint32_t  DEST0BL2;   /**< 0x0038: DMM Destination 0 Blocksize 2                 */
    uint32_t  DEST1REG1;  /**< 0x003C: DMM Destination 1 Region 1                  */
    uint32_t  DEST1BL1;   /**< 0x0040: DMM Destination 1 Blocksize 1                 */
    uint32_t  DEST1REG2;  /**< 0x0044: DMM Destination 1 Region 2                   */
    uint32_t  DEST1BL2;   /**< 0x0048: DMM Destination 1 Blocksize 2                  */
    uint32_t  DEST2REG1;  /**< 0x004C: DMM Destination 2 Region 1                  */
    uint32_t  DEST2BL1;   /**< 0x0050: DMM Destination 2 Blocksize 1                  */
    uint32_t  DEST2REG2;  /**< 0x0054: DMM Destination 2 Region 2  */
    uint32_t  DEST2BL2;   /**< 0x0058: DMM Destination 2 Blocksize 2   */
    uint32_t  DEST3REG1;  /**< 0x005C: DMM Destination 3 Region 1 */
    uint32_t  DEST3BL1;   /**< 0x0060: DMM Destination 3 Blocksize 1                       */
    uint32_t  DEST3REG2;  /**< 0x0064: DMM Destination 3 Region 2              */
    uint32_t  DEST3BL2;   /**< 0x0068: DMM Destination 3 Blocksize 2              */
    uint32_t  PC0;        /**< 0x006C: DMM Pin Control 0                          */
    uint32_t  PC1;        /**< 0x0070: DMM Pin Control 1               */     
    uint32_t  PC2;        /**< 0x0074: DMM Pin Control 2              */
    uint32_t  PC3;        /**< 0x0078: DMM Pin Control 3              */
    uint32_t  PC4;        /**< 0x007C: DMM Pin Control 4   */
    uint32_t  PC5;        /**< 0x0080: DMM Pin Control 5                 */
    uint32_t  PC6;        /**< 0x0084: DMM Pin Control 6                              */
    uint32_t  PC7;        /**< 0x0088: DMM Pin Control 7                             */
    uint32_t  PC8;        /**< 0x008C: DMM Pin Control 8                              */
} dmmBASE_t;


/** @def dmmREG
*   @brief DMM Register Frame Pointer
*
*   This pointer is used by the DMM driver to access the DMM module registers.
*/
#define dmmREG ((dmmBASE_t *)0xFFFFF700U)

/** @def dmmPORT
*   @brief DMM Port Register Pointer
*
*   Pointer used by the GIO driver to access I/O PORT of DMM
*   (use the GIO drivers to access the port pins).
*/
#define dmmPORT ((gioPORT_t *)0xFFFFF738U)


/* DMM Interface Functions */

void dmmInit(void);

#endif
