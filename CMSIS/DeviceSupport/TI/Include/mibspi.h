/** @file mibspi.h
*   @brief MIBSPI Driver Definition File
*   @date 15.December.2011
*   @version 03.00.00
*   
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */


#ifndef __MIBSPI_H__
#define __MIBSPI_H__

#include "sys_common.h"
#include "gio.h"


/** @enum triggerEvent
*   @brief Transfer Group Trigger Event
*/
enum triggerEvent
{
    TRG_NEVER   = 0,
    TRG_RISING  = 1,
    TRG_FALLING = 2,
    TRG_BOTH    = 3,
    TRG_HIGH    = 5,
    TRG_LOW     = 6,
    TRG_ALWAYS  = 7
};

/** @enum triggerSource
*   @brief Transfer Group Trigger Source
*/
enum triggerSource
{
    TRG_DISABLED,
    TRG_GIOA0,
    TRG_GIOA1,
    TRG_GIOA2,
    TRG_GIOA3,
    TRG_GIOA4,
    TRG_GIOA5,
    TRG_GIOA6,
    TRG_GIOA7,
    TRG_HET8,
    TRG_HET10,
    TRG_HET12,
    TRG_HET14,
    TRG_HET16,
    TRG_HET18,
    TRG_TICK
};


/** @enum mibspiPinSelect
*   @brief mibspi Pin Select
*/
enum mibspiPinSelect
{
    PIN_CS0   = 0,
    PIN_CS1 = 1,
    PIN_CS2 = 2,
    PIN_CS3  = 3,
    PIN_CS4 = 4,
    PIN_CS5    = 5,
    PIN_CS6    = 6,
    PIN_CS7  = 7,
    PIN_ENA = 8,
    PIN_CLK = 9,
    PIN_SIMO = 10,
    PIN_SOMI = 11,
   PIN_SIMO_1 = 17,
   PIN_SIMO_2 = 18,
   PIN_SIMO_3 = 19,
   PIN_SIMO_4 = 20,
   PIN_SIMO_5 = 21,
   PIN_SIMO_6 = 22,
   PIN_SIMO_7 = 23,
   PIN_SOMI_1 = 25,
   PIN_SOMI_2 = 26,
   PIN_SOMI_3 = 27,
   PIN_SOMI_4 = 28,
   PIN_SOMI_5 = 29,
   PIN_SOMI_6 = 30,
   PIN_SOMI_7 = 31
};


/** @enum chipSelect
*   @brief Transfer Group Chip Select
*/
enum chipSelect
{
    CS_NONE = 0xFF,
    CS_0    = 0xFE,
    CS_1    = 0xFD,
    CS_2    = 0xFB,
    CS_3    = 0xF7,
    CS_4    = 0xEF,
    CS_5    = 0xDF,
    CS_6    = 0xBF,
    CS_7    = 0x7F
};


/** @struct mibspiBase
*   @brief MIBSPI Register Definition
*
*   This structure is used to access the MIBSPI module egisters.
*/
/** @typedef mibspiBASE_t
*   @brief MIBSPI Register Frame Type Definition
*
*   This type is used to access the MIBSPI Registers.
*/
typedef volatile struct mibspiBase
{
    uint32_t  GCR0;                 /**< 0x0000: Global Control 0 */
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
    uint32_t  GCR1          :  8U;  /**< 0x0007: Global Control 1 */
    uint32_t  PD            :  1U;  /**< 0x0006: Power down bit */
    uint32_t                :  7U;
    uint32_t  LB            :  1U;  /**< 0x0005: Loop back bit */
    uint32_t                :  7U;
    uint32_t  ENA           :  1U;  /**< 0x0004: MIBSPI Enable bit */
    uint32_t                :  7U;  
    uint32_t  INT0          : 16U;  /**< 0x000A: Interrupt Enable bits */
    uint32_t  DMAREQEN      :  1U;  /**< 0x0009: DMA Request enable */
    uint32_t                :  7U;
    uint32_t  ENAHIGHZ      :  1U;  /**< 0x0008: Enable HIGHZ outputs */
    uint32_t                :  7U;
#else
    uint32_t                :  7U;  
    uint32_t  ENA           :  1U;  /**< 0x0004: MIBSPI Enable bit */
    uint32_t                :  7U;
    uint32_t  LB            :  1U;  /**< 0x0005: Loop back bit */
    uint32_t                :  7U;
    uint32_t  PD            :  1U;  /**< 0x0006: Power down bit */
    uint32_t  GCR1          :  8U;  /**< 0x0007: Global Control 1 */
    uint32_t                :  7U;
    uint32_t  ENAHIGHZ      :  1U;  /**< 0x0008: Enable HIGHZ outputs */
    uint32_t                :  7U;
    uint32_t  DMAREQEN      :  1U;  /**< 0x0009: DMA Request enable */
    uint32_t  INT0          : 16U;  /**< 0x000A: Interrupt Enable bits */
#endif
    uint32_t  LVL;                  /**< 0x000C: Interrupt Level */
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
    uint32_t  FLG           : 16U;  /**< 0x0012: Interrupt flags */
    uint32_t                :  8U;
    uint32_t  BUFINIT       :  1U;  /**< 0x0010: Buffer inialisation active flag */
    uint32_t                :  7U;
#else
    uint32_t                :  7U;
    uint32_t  BUFINIT       :  1U;  /**< 0x0010: Buffer inialisation active flag */
    uint32_t                :  8U;
    uint32_t  FLG           : 16U;  /**< 0x0012: Interrupt flags */  
#endif
    uint32_t  PCFUN;                /**< 0x0014: Function Pin Enable */
    uint32_t  PCDIR;                /**< 0x0018: Pin Direction */
    uint32_t  PCDIN;                /**< 0x001C: Pin Input Latch */
    uint32_t  PCDOUT;               /**< 0x0020: Pin Output Latch */
    uint32_t  PCSET;                /**< 0x0024: Output Pin Set */
    uint32_t  PCCLR;                /**< 0x0028: Output Pin Clr */
    uint32_t  PCPDR;                /**< 0x002C: Open Drain Output Enable */
    uint32_t  PCDIS;                /**< 0x0030: Pullup/Pulldown Disable */
    uint32_t  PCPSL;                /**< 0x0034: Pullup/Pulldown Selection */
    uint32_t  DAT0;                 /**< 0x0038: Transmit Data */
    uint32_t  DAT1;                 /**< 0x003C: Transmit Data with Format and Chip Select */
    uint32_t  BUF;                  /**< 0x0040: Receive Buffer */
    uint32_t  EMU;                  /**< 0x0044: Emulation Receive Buffer */
    uint32_t  DELAY;                /**< 0x0048: Delays */
    uint32_t  CSDEF;                /**< 0x004C: Default Chip Select */
    uint32_t  FMT0;                 /**< 0x0050: Data Format 0 */
    uint32_t  FMT1;                 /**< 0x0054: Data Format 1 */
    uint32_t  FMT2;                 /**< 0x0058: Data Format 2 */
    uint32_t  FMT3;                 /**< 0x005C: Data Format 3 */
    uint32_t  INTVECT0;             /**< 0x0060: Interrupt Vector 0 */
    uint32_t  INTVECT1;             /**< 0x0064: Interrupt Vector 1 */
    uint32_t  SRSEL;                /**< 0x0068: Slew Rate Select */
    uint32_t  PMCTRL;               /**< 0x006C: Parrallel Mode Control */
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
    uint32_t  MIBSPIE       : 16U;  /**< 0x0072: MibSPI Enable */
    uint32_t  RAMACCESS     : 16U;  /**< 0x0070: RX Ram Write Access Enable */
    uint32_t  SETINTENASUS  : 16U;
    uint32_t  SETINTENARDY  : 16U;  /**< 0x0074: Transfer Group Interrupt Enable Set Register */
    uint32_t  CLRINTENASUS  : 16U;
    uint32_t  CLRINTENARDY  : 16U;  /**< 0x0078: Transfer Group Interrupt Enable Clear Register */
    uint32_t  SETINTLVLSUS  : 16U;
    uint32_t  SETINTLVLRDY  : 16U;  /**< 0x007C: Transfer Group Interrupt Level Set Register */
    uint32_t  CLRINTLVLSUS  : 16U;
    uint32_t  CLRINTLVLRDY  : 16U;  /**< 0x0080: Transfer Group Interrupt Level Clear Register */
    uint32_t  INTFLGSUS     : 16U;
    uint32_t  INTFLGRDY     : 16U;  /**< 0x0084: Transfer Group Interrupt Flags */
#else
    uint32_t  RAMACCESS     : 16U;  /**< 0x0070: RX Ram Write Access Enable */
    uint32_t  MIBSPIE       : 16U;  /**< 0x0072: MibSPI Enable */
    uint32_t  SETINTENARDY  : 16U;  /**< 0x0074: Transfer Group Interrupt Enable Set Register */
    uint32_t  SETINTENASUS  : 16U;
    uint32_t  CLRINTENARDY  : 16U;  /**< 0x0078: Transfer Group Interrupt Enable Clear Register */
    uint32_t  CLRINTENASUS  : 16U;
    uint32_t  SETINTLVLRDY  : 16U;  /**< 0x007C: Transfer Group Interrupt Level Set Register */
    uint32_t  SETINTLVLSUS  : 16U;
    uint32_t  CLRINTLVLRDY  : 16U;  /**< 0x0080: Transfer Group Interrupt Level Clear Register */
    uint32_t  CLRINTLVLSUS  : 16U;
    uint32_t  INTFLGRDY     : 16U;  /**< 0x0084: Transfer Group Interrupt Flags */
    uint32_t  INTFLGSUS     : 16U;
#endif
    uint32_t                : 32U;
    uint32_t                : 32U;
    uint32_t  TICKCNT;              /**< 0x0090: Tick Counter */
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
    uint32_t                :  8U;
    uint32_t  LTGPEND       :  7U;  /**< 0x0096: Transfer Group End Pointer */
    uint32_t                :  9U;
    uint32_t  TGINSERVICE   :  5U;
    uint32_t                :  3U;
#else
    uint32_t                :  3U;
    uint32_t  TGINSERVICE   :  5U;
    uint32_t                :  9U;
    uint32_t  LTGPEND       :  7U;  /**< 0x0096: Transfer Group End Pointer */
    uint32_t                :  8U;
#endif
    uint32_t  TGCTRL[16U];          /**< 0x0098 - 0x00D4: Transfer Group Control */
    uint32_t  DMACTRL[8U];          /**< 0x00D8 - 0x00F4: DMA Control */
    uint32_t  DMACOUNT[8U];         /**< 0x00F8 - 0x0114: DMA Count */
    uint32_t  DMACNTLEN;            /**< 0x0118 - 0x0114: DMA Control length */
    uint32_t                : 32U;
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
    uint32_t  EDEN          :  4U;
    uint32_t                :  4U;
    uint32_t  PTESTEN       :  1U;
    uint32_t                : 23U;
#else
    uint32_t                : 23U;
    uint32_t  PTESTEN       :  1U;
    uint32_t                :  4U;
    uint32_t  EDEN          :  4U;
#endif
    uint32_t  UERRSTAT;
    uint32_t  UERRADDRRX;
    uint32_t  UERRADDRTX;
    uint32_t  RXOVRN_BUF_ADDR;     /**< 0x0130: */
    uint32_t  IOLPKTSTCR;          /**< 0x0134: IO loopback */
    uint32_t  EXT_PRESCALE1;       /**< 0x0138: */
    uint32_t  EXT_PRESCALE2;       /**< 0x013C: */
} mibspiBASE_t;


/** @def mibspiREG1
*   @brief MIBSPI1 Register Frame Pointer
*
*   This pointer is used by the MIBSPI driver to access the mibspi module registers.
*/
#define mibspiREG1 ((mibspiBASE_t *)0xFFF7F400U)


/** @def mibspiPORT1
*   @brief MIBSPI1 GIO Port Register Pointer
*
*   Pointer used by the GIO driver to access I/O PORT of MIBSPI1
*   (use the GIO drivers to access the port pins).
*/
#define mibspiPORT1 ((gioPORT_t *)0xFFF7F418U)

/** @def mibspiREG3
*   @brief MIBSPI3 Register Frame Pointer
*
*   This pointer is used by the MIBSPI driver to access the mibspi module registers.
*/
#define mibspiREG3 ((mibspiBASE_t *)0xFFF7F800U)


/** @def mibspiPORT3
*   @brief MIBSPI3 GIO Port Register Pointer
*
*   Pointer used by the GIO driver to access I/O PORT of MIBSPI3
*   (use the GIO drivers to access the port pins).
*/
#define mibspiPORT3 ((gioPORT_t *)0xFFF7F818U)

/** @def mibspiREG5
*   @brief MIBSPI5 Register Frame Pointer
*
*   This pointer is used by the MIBSPI driver to access the mibspi module registers.
*/
#define mibspiREG5 ((mibspiBASE_t *)0xFFF7FC00U)


/** @def mibspiPORT5
*   @brief MIBSPI5 GIO Port Register Pointer
*
*   Pointer used by the GIO driver to access I/O PORT of MIBSPI5
*   (use the GIO drivers to access the port pins).
*/
#define mibspiPORT5 ((gioPORT_t *)0xFFF7FC18U)


/** @struct mibspiRamBase
*   @brief MIBSPI Buffer RAM Definition
*
*   This structure is used to access the MIBSPI buffer memory.
*/
/** @typedef mibspiRAM_t
*   @brief MIBSPI RAM Type Definition
*
*   This type is used to access the MIBSPI RAM.
*/
typedef volatile struct mibspiRamBase
{
    struct 
    {
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
     uint16_t  data;     /**< tx buffer data    */   
					uint16_t  control;  /**< tx buffer control */  
#else
     uint16_t  control;  /**< tx buffer control */
     uint16_t  data;     /**< tx buffer data    */
#endif
    } tx[128];
    struct
    {
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
     uint16_t data;     /**< rx buffer data  */
					uint16_t flags;    /**< rx buffer flags */
#else
					uint16_t flags;    /**< rx buffer flags */
     uint16_t data;     /**< rx buffer data  */
#endif
    } rx[128];
} mibspiRAM_t;


/** @def mibspiRAM1
*   @brief MIBSPI1 Buffer RAM Pointer
*
*   This pointer is used by the MIBSPI driver to access the mibspi buffer memory.
*/
#define mibspiRAM1 ((mibspiRAM_t *)0xFF0E0000U)

/** @def mibspiRAM3
*   @brief MIBSPI3 Buffer RAM Pointer
*
*   This pointer is used by the MIBSPI driver to access the mibspi buffer memory.
*/
#define mibspiRAM3 ((mibspiRAM_t *)0xFF0C0000U)


/** @def mibspiRAM5
*   @brief MIBSPI5 Buffer RAM Pointer
*
*   This pointer is used by the MIBSPI driver to access the mibspi buffer memory.
*/
#define mibspiRAM5 ((mibspiRAM_t *)0xFF0A0000U)


/* MIBSPI Interface Functions */
void mibspiInit(void);
void mibspiSetFunctional(mibspiBASE_t *mibspi, uint32_t port);
void mibspiSetData(mibspiBASE_t *mibspi, uint32_t group, uint16_t data[]);
uint32_t mibspiGetData(mibspiBASE_t *mibspi, uint32_t group, uint16_t data[]);
void mibspiTransfer(mibspiBASE_t *mibspi, uint32_t group);
int  mibspiIsTransferComplete(mibspiBASE_t *mibspi, uint32_t group);
void mibspiEnableGroupNotification(mibspiBASE_t *mibspi, uint32_t group, uint32_t level);
void mibspiDisableGroupNotification(mibspiBASE_t *mibspi, uint32_t group);


/** @fn void mibspiNotification(mibspiBASE_t *mibspi, uint32_t flags)
*   @brief Error interrupt callback
*   @param[in] mibspi   - mibSpi module base address
*   @param[in] flags - Copy of error interrupt flags
*
* This is a error callback that is provided by the application and is call apon
* an error interrupt.  The paramer passed to the callback is a copy of the error
* interrupt flag register.
*/
void mibspiNotification(mibspiBASE_t *mibspi, uint32_t flags);


/** @fn void mibspiGroupNotification(mibspiBASE_t *mibspi, uint32_t group)
*   @brief Transfer complete notification callback
*   @param[in] mibspi   - mibSpi module base address
*   @param[in] group - Transfer group
*
* This is a callback function provided by the application.  It is call when
* a transfer is complete.  The paramter is the transfer group that triggered
* the interrupt.
*/
void mibspiGroupNotification(mibspiBASE_t *mibspi, uint32_t group);

#endif
