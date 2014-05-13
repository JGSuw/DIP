/******************************************************************************/
/* Serial.c: Low Level Serial Routines                                        */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005-2010 Keil Software. All rights reserved.                */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/

#if defined(UART_SUPPORT)

#include <TMS570.h>

#define pLIN   ((SCI_ST *)LIN)


/*----------------------------------------------------------------------------
  Initialize UART pins, Baudrate
 *----------------------------------------------------------------------------*/
void SER_init (void) {

  pLIN->SCIGR0_UN.SCIGR0_UL   = 1;
  pLIN->SCIGR1_UN.SCIGR1_UL   = 0;          // SWnRST = 0, Clears all Flag and can config SCI
  pLIN->SCIPIO7_UN.SCIPIO7_UL = 0;          // Pull Enable
  pLIN->SCIPIO0_UN.SCIPIO0_UL = 0x6;        // TX/RX Pin Functional
  pLIN->SCIGR1_UN.SCIGR1_UL   = 0x03000022; // Async, no parity, one stop bit
  pLIN->SCICHAR_UN.SCICHAR_UL = 7;          // 8 data bits,
  pLIN->SCIBRSR_UN.SCIBRSR_UL = 0x0000002B; // 115200 baud (at 80MHz VBUSPCLK)
  pLIN->SCIGR1_UN.SCIGR1_UL  |= 0x80;       // SWnRST = 1, SCI Config is done and should not be disturbed
}


/*----------------------------------------------------------------------------
  Write character to Serial Port
 *----------------------------------------------------------------------------*/
int sendchar (int c) {
  while (!(pLIN->SCIFLR_UN.SCIFLR_ST.TX_EMPTY_B1));
  pLIN->SCITD_UN.SCITD_ST.TD_UC = c;

  return (c);
}


/*----------------------------------------------------------------------------
  Read character from Serial Port   (blocking read)
 *----------------------------------------------------------------------------*/
int getkey () {
  while (!(pLIN->SCIFLR_UN.SCIFLR_ST.RXRDY_B1));

  return (pLIN->SCIRD_UN.SCIRD_ST.RD_UC);
}

#endif //defined(UART_SUPPORT)
