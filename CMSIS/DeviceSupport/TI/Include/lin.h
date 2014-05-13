/** @file lin.h
*   @brief LIN Driver Definition File
*   @date 15.December.2011
*   @version 03.00.00
*   
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */


#ifndef __LIN_H__
#define __LIN_H__

#include "sys_common.h"
#include "gio.h"

#ifndef BOOL
#define BOOL  uint32_t char
#endif

/** @def LIN_BREAK_INT
*   @brief Alias for break detect interrupt flag
*
*   Used with linEnableNotification, linDisableNotification.
*/
#define LIN_BREAK_INT 0x00000001U


/** @def LIN_WAKEUP_INT
*   @brief Alias for wakeup interrupt flag
*
*   Used with linEnableNotification, linDisableNotification.
*/
#define LIN_WAKEUP_INT 0x00000002U


/** @def LIN_TO_INT
*   @brief Alias for time out interrupt flag
*
*   Used with linEnableNotification, linDisableNotification.
*/
#define LIN_TO_INT 0x00000010U


/** @def LIN_TOAWUS_INT
*   @brief Alias for time out after wakeup signal interrupt flag
*
*   Used with linEnableNotification, linDisableNotification.
*/
#define LIN_TOAWUS_INT 0x00000040U


/** @def LIN_TOA3WUS_INT
*   @brief Alias for time out after 3 wakeup signals interrupt flag
*
*   Used with linEnableNotification, linDisableNotification.
*/
#define LIN_TOA3WUS_INT 0x00000080U


/** @def LIN_TX_READY
*   @brief Alias for transmit buffer ready flag
*
*   Used with linIsTxReady.
*/
#define LIN_TX_READY 0x00000100U


/** @def LIN_RX_INT
*   @brief Alias for receive buffer ready interrupt flag
*
*   Used with linEnableNotification, linDisableNotification.
*/
#define LIN_RX_INT 0x00000200U


/** @def LIN_ID_INT
*   @brief Alias for received matching identifier interrupt flag
*
*   Used with linEnableNotification, linDisableNotification.
*/
#define LIN_ID_INT 0x00002000U


/** @def LIN_PE_INT
*   @brief Alias for parity error interrupt flag
*
*   Used with linEnableNotification, linDisableNotification.
*/
#define LIN_PE_INT 0x01000000U


/** @def LIN_OE_INT
*   @brief Alias for overrun error interrupt flag
*
*   Used with linEnableNotification, linDisableNotification.
*/
#define LIN_OE_INT 0x02000000U


/** @def LIN_FE_INT
*   @brief Alias for framming error interrupt flag
*
*   Used with linEnableNotification, linDisableNotification.
*/
#define LIN_FE_INT 0x04000000U


/** @def LIN_NRE_INT
*   @brief Alias for no response error interrupt flag
*
*   Used with linEnableNotification, linDisableNotification.
*/
#define LIN_NRE_INT 0x08000000U


/** @def LIN_ISFE_INT
*   @brief Alias for inconsistent sync field error interrupt flag
*
*   Used with linEnableNotification, linDisableNotification.
*/
#define LIN_ISFE_INT 0x10000000U


/** @def LIN_CE_INT
*   @brief Alias for checksum error interrupt flag
*
*   Used with linEnableNotification, linDisableNotification.
*/
#define LIN_CE_INT 0x20000000U


/** @def LIN_PBE_INT
*   @brief Alias for physical bus error interrupt flag
*
*   Used with linEnableNotification, linDisableNotification.
*/
#define LIN_PBE_INT 0x40000000U


/** @def LIN_BE_INT
*   @brief Alias for bit error interrupt flag
*
*   Used with linEnableNotification, linDisableNotification.
*/
#define LIN_BE_INT 0x80000000U


/** @struct linBase
*   @brief LIN Register Definition
*
*   This structure is used to access the LIN module egisters.
*/
/** @typedef linBASE_t
*   @brief LIN Register Frame Type Definition
*
*   This type is used to access the LIN Registers.
*/

enum linPinSelect
{
    PIN_LIN_TX   = 0,
    PIN_LIN_RX = 1
};

/** @struct linBase
*   @brief LIN Base Register Definition
*
*   This structure is used to access the LIN module egisters.
*/
/** @typedef linBASE_t
*   @brief LIN  Register Frame Type Definition
*
*   This type is used to access the LIN Registers.
*/

typedef volatile struct linBase
{
    uint32_t      GCR0;         /**< 0x0000: Global control register 0              */
    uint32_t      GCR1;         /**< 0x0004: Global control register 1              */
    uint32_t      GCR2;         /**< 0x0008: Global control register 2              */
    uint32_t      SETINT;       /**< 0x000C: Set interrupt enable register          */
    uint32_t      CLRINT;       /**< 0x0010: Clear interrupt enable register        */
    uint32_t      SETINTLVL;    /**< 0x0014: Set interrupt level register           */
    uint32_t      CLRINTLVL;    /**< 0x0018: Set interrupt level register           */
    uint32_t      FLR;          /**< 0x001C: interrupt flag register                */
    uint32_t      INTVECT0;     /**< 0x0020: interrupt vector Offset 0              */
    uint32_t      INTVECT1;     /**< 0x0024: interrupt vector Offset 1              */
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1)) 
    uint32_t      CHAR   :  3U; /**< 0x0028: Character length control register      */
    uint32_t             : 13U; /**< 0x0028: Reserved                               */
    uint32_t      LENGTH :  3U; /**< 0x0028: Length control register                */
    uint32_t             : 13U; /**< 0x0028: Reserved                               */
#else
    uint32_t             : 13U; /**< 0x0028: Reserved                               */
    uint32_t      LENGTH :  3U; /**< 0x0028: Length control register                */
    uint32_t             : 13U; /**< 0x0028: Reserved                               */
    uint32_t      CHAR   :  3U; /**< 0x0028: Character length control register      */
#endif
    uint32_t      BRSR;         /**< 0x002C: Baud rate selection register           */
    uint32_t      ED;           /**< 0x0030: Emulation register                     */
    uint32_t      RD;           /**< 0x0034: Receive data register                  */
    uint32_t      TD;           /**< 0x0038: Transmit data register                 */
    uint32_t      FUN;          /**< 0x003C: Pin function register                  */
    uint32_t      DIR;          /**< 0x0040: Pin direction register                 */
    uint32_t      DIN;          /**< 0x0044: Pin data in register                   */
    uint32_t      DOUT;         /**< 0x0048: Pin data out register                  */
    uint32_t      SET;          /**< 0x004C: Pin data set register                  */
    uint32_t      CLR;          /**< 0x0050: Pin data clr register                  */
    uint32_t      ODR;          /**< 0x0054: Pin open drain output enable register  */
    uint32_t      PD;           /**< 0x0058: Pin pullup/pulldown disable register   */
    uint32_t      PSL;          /**< 0x005C: Pin pullup/pulldown selection register */
    uint32_t      COMP;         /**< 0x0060: Compare register                       */
    uint8_t       RDx[8U];      /**< 0x0064-0x0068: RX buffer register              */
    uint32_t      MASK;         /**< 0x006C: Mask register                          */
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1)) 
    uint8_t       IDBYTE;       /**< 0x0070: Identifier byte register               */
    uint8_t       IDSTB;        /**< 0x0070: Identifier slave task byte register    */
    uint8_t       RXID;         /**< 0x0070: Received identifier register           */
    uint32_t      : 8U;         /**< 0x0070: Reserved                               */
#else
    uint32_t      : 8U;         /**< 0x0070: Reserved                               */
    uint8_t       RXID;         /**< 0x0070: Received identifier register           */
    uint8_t       IDSTB;        /**< 0x0070: Identifier Slave task byte register    */
    uint8_t       IDBYTE;       /**< 0x0070: Identifier byte register               */
#endif
    uint8_t       TDx[8U];      /**< 0x0074-0x0078: TX buffer register              */
    uint32_t      MBRSR;        /**< 0x007C: Maximum baud rate selection register   */
    uint32_t      SL;           /**< 0x0080: Pin slew rate register                 */
    uint32_t      : 32U;        /**< 0x0084: Reserved                               */
    uint32_t      : 32U;        /**< 0x0088: Reserved                               */
    uint32_t      : 32U;        /**< 0x008C: Reserved                               */
    uint32_t      DFT;          /**< 0x0090: Pin slew rate register                 */
} linBASE_t;


/** @def linREG
*   @brief LIN Register Frame Pointer
*
*   This pointer is used by the LIN driver to access the lin module registers.
*/
#define linREG ((linBASE_t *)0xFFF7E400U)


/** @def linPORT
*   @brief LIN GIO Port Register Pointer
*
*   Pointer used by the GIO driver to access I/O PORT of LIN
*   (use the GIO drivers to access the port pins).
*/
#define linPORT ((gioPORT_t *)0xFFF7E440U)

/* LIN Interface Functions */
void     linInit(void);
void     linSetFunctional(linBASE_t *lin, uint32_t port);
void     linSendHeader(linBASE_t *lin, uint8_t identifier);
void     linSendWakupSignal(linBASE_t *lin);
void     linEnterSleep(linBASE_t *lin);
void     linSoftwareReset(linBASE_t *lin);
uint32_t linIsTxReady(linBASE_t *lin);
void     linSetLength(linBASE_t *lin, uint32_t length);
void     linSend(linBASE_t *lin, const uint8_t *data);
uint32_t linIsRxReady(linBASE_t *lin);
uint32_t linTxRxError(linBASE_t *lin);
uint32_t linGetIdentifier(linBASE_t *lin);
void     linGetData(linBASE_t *lin, uint8_t * const data);
void     linEnableNotification(linBASE_t *lin, uint32_t flags);
void     linDisableNotification(linBASE_t *lin, uint32_t flags);


/** @fn void linNotification(linBASE_t *lin, uint32_t flags)
*   @brief Interrupt callback
*   @param[in] lin   - lin module base address
*   @param[in] flags - copy of error interrupt flags
*
* This is a callback that is provided by the application and is called apon
* an interrupt.  The parameter passed to the callback is a copy of the 
* interrupt flag register.
*/
void linNotification(linBASE_t *lin, uint32_t flags);
#endif
