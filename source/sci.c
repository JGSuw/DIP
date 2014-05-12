/** @file sci.c 
*   @brief SCI Driver Implementation File
*   @date 15.Mar.2012
*   @version 03.01.00
*
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */

#include "sci.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */
/** @struct g_sciTransfer
*   @brief Interrupt mode globals
*
*/
struct g_sciTransfer
{
    uint32_t       mode;
    uint32_t       length;
    uint8_t *data;
} g_sciTransfer[2];


/** @fn void sciInit(void)
*   @brief Initializes the SCI Driver
*
*   This function initializes the SCI module.
*/
void sciInit(void)
{
/* USER CODE BEGIN (2) */
/* USER CODE END */

    /** @b initialize @b SCI */

    /** - bring SCI out of reset */
    sciREG->GCR0 = 1U;

    /** - Disable all interrupts */
    sciREG->CLRINT    = 0xFFFFFFFFU;
    sciREG->CLRINTLVL = 0xFFFFFFFFU;

    /** - global control 1 */
    sciREG->GCR1 = (1 << 25)  /* enable transmit */
                  | (1 << 24)  /* enable receive */
                  | (1 << 5)   /* internal clock (device has no clock pin) */
                  | ((2-1) << 4)  /* number of stop bits */
                  | (0 << 3)  /* even parity, otherwise odd */
                  | (0 << 2)  /* enable parity */
                  | (1 << 1);  /* asynchronous timing mode */

    /** - set baudrate */
    sciREG->BAUD = 520;  /* baudrate */

    /** - transmission length */
    sciREG->LENGTH = 8 - 1;  /* length */

    /** - set SCI pins functional mode */
    sciREG->FUN = (1 << 2)  /* tx pin */
                 | (1 << 1)  /* rx pin */
                 | (0);  /* clk pin */

    /** - set SCI pins default output value */
    sciREG->DOUT = (0 << 2)  /* tx pin */
                  | (0 << 1)  /* rx pin */
                  | (0);  /* clk pin */

    /** - set SCI pins output direction */
    sciREG->DIR = (0 << 2)  /* tx pin */
                 | (0 << 1)  /* rx pin */
                 | (0);  /* clk pin */

    /** - set SCI pins open drain enable */
    sciREG->ODR = (0 << 2)  /* tx pin */
                 | (0 << 1)  /* rx pin */
                 | (0);  /* clk pin */

    /** - set SCI pins pullup/pulldown enable */
    sciREG->PD = (0 << 2)  /* tx pin */
                | (0 << 1)  /* rx pin */
                | (0);  /* clk pin */

    /** - set SCI pins pullup/pulldown select */
    sciREG->PSL = (1 << 2)  /* tx pin */
                 | (1 << 1)  /* rx pin */
                 | (1);  /* clk pin */

    /** - set interrupt level */
    sciREG->SETINTLVL = (0 << 26)  /* Framing error */
                       | (0 << 25)  /* Overrun error */
                       | (0 << 24)  /* Parity error */
                       | (0 << 9)  /* Receive */
                       | (0 << 8)  /* Transmit */
                       | (0 << 1)  /* Wakeup */
                       | (0);  /* Break detect */

    /** - set interrupt enable */
    sciREG->SETINT = (0 << 26)  /* Framing error */
                    | (0 << 25)  /* Overrun error */
                    | (0 << 24)  /* Parity error */
                    | (0 << 9)  /* Receive */
                    | (0 << 1)  /* Wakeup */
                    | (0);  /* Break detect */

    /** - initialize global transfer variables */
    g_sciTransfer[0].mode   = 0 << 8;
    g_sciTransfer[0].length = 0;

    /** - Finaly start SCI */
    sciREG->GCR1 |= (1 << 7);


/* USER CODE BEGIN (3) */
/* USER CODE END */
}


/** @fn void sciSetFunctional(sciBASE_t *sci, uint32_t port)
*   @brief Change functional behavior of pins at runtime.
*   @param[in] sci   - sci module base address
*   @param[in] port  - Value to write to FUN register
*
*   Change the value of the PCFUN register at runtime, this allows to
*   dynaimcaly change the functionality of the SCI pins between functional
*   and GIO mode.
*/
void sciSetFunctional(sciBASE_t *sci, uint32_t port)
{
/* USER CODE BEGIN (4) */
/* USER CODE END */

    sci->FUN = port;

/* USER CODE BEGIN (5) */
/* USER CODE END */
}


/** @fn void sciSetBaudrate(sciBASE_t *sci, uint32_t baud)
*   @brief Change baudrate at runtime.
*   @param[in] sci  - sci module base address
*   @param[in] baud - baudrate in Hz
*
*   Change the SCI baudrate at runtime.
*/
void sciSetBaudrate(sciBASE_t *sci, uint32_t baud)
{
    double   vclk = 80.000 * 1000000.0;
    uint32_t f    = sci->GCR1 & 2 ? 16 : 1;

/* USER CODE BEGIN (6) */
/* USER CODE END */

    sci->BAUD = ((uint32_t)((vclk /(f*baud) + 0.5)) - 1) & 0x00FFFFFF;

/* USER CODE BEGIN (7) */
/* USER CODE END */
}


/** @fn uint32_t sciIsTxReady(sciBASE_t *sci)
*   @brief Check if Tx buffer empty
*   @param[in] sci - sci module base address
*
*   @return The TX ready flag
*
*   Checks to see if the Tx buffer ready flag is set, returns
*   0 is flags not set otherwise will return the Tx flag itself.
*/
uint32_t sciIsTxReady(sciBASE_t *sci)
{
/* USER CODE BEGIN (8) */
/* USER CODE END */

    return sci->FLR & SCI_TX_INT;
}


/** @fn void sciSendByte(sciBASE_t *sci, uint8_t byte)
*   @brief Send Byte
*   @param[in] sci  - sci module base address
*   @param[in] byte - byte to transfer
*
*   Sends a single byte in polling mode, will wait in the
*   routine until the transmit buffer is empty before sending
*   the byte.  Use sciIsTxReady to check for Tx buffer empty
*   before calling sciSendByte to avoid waiting.
*/
void sciSendByte(sciBASE_t *sci, uint8_t byte)
{
/* USER CODE BEGIN (9) */
/* USER CODE END */

    while ((sci->FLR & SCI_TX_INT) == 0) { /* wait */ };
    sci->TD = byte;

/* USER CODE BEGIN (10) */
/* USER CODE END */
}


/** @fn void sciSend(sciBASE_t *sci, uint32_t length, uint8_t *data)
*   @brief Send Data
*   @param[in] sci    - sci module base address
*   @param[in] length - number of data words to transfer
*   @param[in] data   - pointer to data to send
*
*   Send a block of data pointed to by 'data' and 'length' bytes
*   long.  If interrupts have been enabled the data is sent using
*   interrupt mode, otherwise polling mode is used.  In interrupt
*   mode transmission of the first byte is started and the routine
*   returns immediately, sciSend must not be called again until the
*   transfer is complete, when the sciNotification callback will
*   be called.  In polling mode, sciSend will not return  until 
*   the transfer is complete.
*
*   @note if data word is less than 8 bits, then the data must be left
*         aligned in the data byte.
*/
void sciSend(sciBASE_t *sci, uint32_t length, uint8_t *data)
{
    uint32_t index = sci == sciREG ? 0 : 1;

/* USER CODE BEGIN (11) */
/* USER CODE END */

    if ((g_sciTransfer[index].mode & SCI_TX_INT) != 0)
    {
        /* we are in interrupt mode */
        
        g_sciTransfer[index].length = length;
        g_sciTransfer[index].data   = data;

        /* start transmit by sending first byte */        
        sci->TD     = *g_sciTransfer[index].data++;
        sci->SETINT = SCI_TX_INT;
    }
    else
    {
        /* send the data */
        while (length-- > 0)
        {
            while ((sci->FLR & SCI_TX_INT) == 0) { /* wait */ };
            sci->TD = *data++;
        }
    }

/* USER CODE BEGIN (12) */
/* USER CODE END */
}


/** @fn uint32_t sciIsRxReady(sciBASE_t *sci)
*   @brief Check if Rx buffer full
*   @param[in] sci - sci module base address
*
*   @return The Rx ready flag
*
*   Checks to see if the Rx buffer full flag is set, returns
*   0 is flags not set otherwise will return the Rx flag itself.
*/
uint32_t sciIsRxReady(sciBASE_t *sci)
{
/* USER CODE BEGIN (13) */
/* USER CODE END */

    return sci->FLR & SCI_RX_INT;
}

/** @fn uint32_t sciIsIdleDetected(sciBASE_t *sci)
*   @brief Check if Idle Period is Detected
*   @param[in] sci - sci module base address
*
*   @return The Idle flag
*
*   Checks to see if the SCI Idle flag is set, returns 0 is flags 
*   not set otherwise will return the Ilde flag itself.
*/
uint32_t sciIsIdleDetected(sciBASE_t *sci)
{
/* USER CODE BEGIN (14) */
/* USER CODE END */

    return sci->FLR & SCI_IDLE;
}


/** @fn uint32_t sciRxError(sciBASE_t *sci)
*   @brief Return Rx Error flags
*   @param[in] sci - sci module base address
*
*   @return The Rx error flags
*
*   Returns the Rx framing, overrun and parity errors flags,
*   also clears the error flags before returning.
*/
uint32_t sciRxError(sciBASE_t *sci)
{
    uint32_t status = sci->FLR & (SCI_FE_INT | SCI_OE_INT |SCI_PE_INT);

/* USER CODE BEGIN (15) */
/* USER CODE END */

    sci->FLR = SCI_FE_INT | SCI_OE_INT | SCI_PE_INT;
    return status;
}


/** @fn uint32_t sciReceiveByte(sciBASE_t *sci)
*   @brief Receive Byte
*   @param[in] sci - sci module base address
*
*   @return Received byte
*
*    Receives a single byte in polling mode.  If there is
*    not a byte in the receive buffer the routine will wait
*    until one is received.   Use sciIsRxReady to check to
*    see if the buffer is full to avoid waiting.
*/
uint32_t sciReceiveByte(sciBASE_t *sci)
{
/* USER CODE BEGIN (16) */
/* USER CODE END */

    while ((sci->FLR & SCI_RX_INT) == 0) { /* wait */ };

    return sci->RD;
}


/** @fn void sciReceive(sciBASE_t *sci, uint32_t length, uint8_t *data)
*   @brief Receive Data
*   @param[in] sci    - sci module base address
*   @param[in] length - number of data words to transfer
*   @param[in] data   - pointer to data buffer
*
*   Receive a block of 'length' bytes long and place it into the 
*   data buffer pointed to by 'data'.  If interrupts have been 
*   enabled the data is received using interrupt mode, otherwise
*   polling mode is used.  In interrupt mode receive is setup and
*   the routine returns immediately, sciReceive must not be called 
*   again until the transfer is complete, when the sciNotification 
*   callback will be called.  In polling mode, sciReceive will not
*   return  until the transfer is complete.
*/
void sciReceive(sciBASE_t *sci, uint32_t length, uint8_t *data)
{
/* USER CODE BEGIN (17) */
/* USER CODE END */

    if (sci->SETINT & SCI_RX_INT)
    {
        /* we are in interrupt mode */
        uint32_t index = sci == sciREG ? 0 : 1;
        
        /* clear error flags */
        sci->FLR = SCI_FE_INT | SCI_OE_INT | SCI_PE_INT;

        g_sciTransfer[index].length = length;
        g_sciTransfer[index].data   = data;
    }
    else
    {   
        while (length-- > 0)
        {
            while ((sci->FLR & SCI_RX_INT) == 0) { /* wait */ };
            *data++ = sci->RD;
        }
    }
/* USER CODE BEGIN (18) */
/* USER CODE END */
}

/** @fn void sciEnableLoopback(sciBASE_t *sci, Loopbacktype_t Loopbacktype)
*   @brief Enable Loopback mode for self test
*   @param[in] sci        - sci module base address
*   @param[in] Loopbacktype  - Digital or Analog
*
*   This function enables the Loopback mode for self test.
*/
void sciEnableLoopback(sciBASE_t *sci, Loopbacktype_t Loopbacktype)
{
/* USER CODE BEGIN (19) */
/* USER CODE END */
    
	/* Clear Loopback incase enabled already */
	sci->IODFTCTRL = 0;
	
	/* Enable Loopback either in Analog or Digital Mode */
    sci->IODFTCTRL = 0x00000A00
                   | Loopbacktype << 1;
	
/* USER CODE BEGIN (20) */
/* USER CODE END */
}

/** @fn void sciDisableLoopback(sciBASE_t *sci)
*   @brief Enable Loopback mode for self test
*   @param[in] sci        - sci module base address
*
*   This function disable the Loopback mode.
*/
void sciDisableLoopback(sciBASE_t *sci)
{
/* USER CODE BEGIN (21) */
/* USER CODE END */
    
	/* Disable Loopback Mode */
    sci->IODFTCTRL = 0x00000500;
	
/* USER CODE BEGIN (22) */
/* USER CODE END */
}

/** @fn sciEnableNotification(sciBASE_t *sci, uint32_t flags)
*   @brief Enable interrupts
*   @param[in] sci   - sci module base address
*   @param[in] flags - Interrupts to be enabled, can be ored value of:
*                      SCI_FE_INT    - framing error,
*                      SCI_OE_INT    - overrun error,
*                      SCI_PE_INT    - parity error,
*                      SCI_RX_INT    - receive buffer ready,
*                      SCI_TX_INT    - transmit buffer ready,
*                      SCI_WAKE_INT  - wakeup,
*                      SCI_BREAK_INT - break detect
*/
void sciEnableNotification(sciBASE_t *sci, uint32_t flags)
{
    uint32_t index = sci == sciREG ? 0 : 1;

/* USER CODE BEGIN (23) */
/* USER CODE END */

    g_sciTransfer[index].mode |= (flags & SCI_TX_INT);
    sci->SETINT                = (flags & ~SCI_TX_INT);

/* USER CODE BEGIN (24) */
/* USER CODE END */
}


/** @fn sciDisableNotification(sciBASE_t *sci, uint32_t flags)
*   @brief Disable interrupts
*   @param[in] sci   - sci module base address
*   @param[in] flags - Interrupts to be disabled, can be ored value of:
*                      SCI_FE_INT    - framing error,
*                      SCI_OE_INT    - overrun error,
*                      SCI_PE_INT    - parity error,
*                      SCI_RX_INT    - receive buffer ready,
*                      SCI_TX_INT    - transmit buffer ready,
*                      SCI_WAKE_INT  - wakeup,
*                      SCI_BREAK_INT - break detect
*/
void sciDisableNotification(sciBASE_t *sci, uint32_t flags)
{
    uint32_t index = sci == sciREG ? 0 : 1;

/* USER CODE BEGIN (25) */
/* USER CODE END */

    g_sciTransfer[index].mode &= ~(flags & SCI_TX_INT);
    sci->CLRINT                = (flags & ~SCI_TX_INT);

/* USER CODE BEGIN (26) */
/* USER CODE END */
}

/* USER CODE BEGIN (37) */
/* USER CODE END */

