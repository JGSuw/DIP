/******************************************************************************
 *  COPYRIGHT
 *  ---------------------------------------------------------------------------
 *  \verbatim
 *
 *      TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION
 *
 *      Property of Texas Instruments, Unauthorized reproduction and/or 
 *      distribution is strictly prohibited. This product is protected under  
 *      copyright law and trade secret law as an  unpublished work.
 *      (C) Copyright Texas Instruments.  All rights reserved.
 *
 *  \endverbatim
 *  ---------------------------------------------------------------------------
 * 
 *  ---------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ---------------------------------------------------------------------------
 *         File:  usbdevicepriv.h
 *    Component:  
 *       Module:  usb
 *    Generator:  -
 *
 *  Description:  Private header file used to share internal variables and
 *                function prototypes between the various device-related
 *                modules in the USB library.  This header MUST NOT be
 *                used by application code.
 * 
 *****************************************************************************/

#ifndef __USBDEVICEPRIV_H__
#define __USBDEVICEPRIV_H__

/******************************************************************************
 *
 * If building with a C++ compiler, make all of the definitions in this header
 * have a C binding.
 *
 *****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 *
 * Device enumeration functions provided by device/usbenum.c and called from
 * the interrupt handler in device/usbhandler.c
 *
 *****************************************************************************/
extern tBoolean USBDeviceConfig(uint32 ulIndex,
                                const tConfigHeader *psConfig,
                                const tFIFOConfig *psFIFOConfig);
extern tBoolean USBDeviceConfigAlternate(uint32 ulIndex,
                                         const tConfigHeader *psConfig,
                                         uint8 ucInterfaceNum,
                                         uint8 ucAlternateSetting);
extern void USBDeviceResumeTickHandler(uint32 ulIndex);

/******************************************************************************
 *
 * Mark the end of the C bindings section for C++ compilers.
 *
 *****************************************************************************/
#ifdef __cplusplus
}
#endif

#endif /* __USBDEVICEPRIV_H__ */
