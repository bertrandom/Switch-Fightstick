/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Header file for Joystick.c.
 */

#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

/* Includes: */
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>

#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Drivers/Board/Joystick.h>
#include <LUFA/Drivers/Board/LEDs.h>
#include <LUFA/Drivers/Board/Buttons.h>
#include <LUFA/Platform/Platform.h>

#include "Descriptors.h"

// Type Defines
// Enumeration for joystick buttons.
typedef enum {
	SWITCH_Y       = 0x01,
	SWITCH_B       = 0x02,
	SWITCH_A       = 0x04,
	SWITCH_X       = 0x08,
	SWITCH_L       = 0x10,
	SWITCH_R       = 0x20,
	SWITCH_ZL      = 0x40,
	SWITCH_ZR      = 0x80,
	SWITCH_MINUS   = 0x100,
	SWITCH_PLUS    = 0x200,
	SWITCH_LCLICK  = 0x400,
	SWITCH_RCLICK  = 0x800,
	SWITCH_HOME    = 0x1000,
	SWITCH_CAPTURE = 0x2000,
} JoystickButtons_t;

#define HAT_TOP          0x00
#define HAT_TOP_RIGHT    0x01
#define HAT_RIGHT        0x02
#define HAT_BOTTOM_RIGHT 0x03
#define HAT_BOTTOM       0x04
#define HAT_BOTTOM_LEFT  0x05
#define HAT_LEFT         0x06
#define HAT_TOP_LEFT     0x07
#define HAT_CENTER       0x08

#define STICK_MIN      0
#define STICK_CENTER 128
#define STICK_MAX    255

#define CONTROLLER_SETUP() \
	{ NOTHING, 250 }, { TRIGGERS, 5 }, { NOTHING, 150 }, { TRIGGERS, 5 }, \
	{ NOTHING, 150 }, { A, 5 }, { NOTHING, 250 }
	
#define GET_EGG_1() \
	{ NOTHING,  50 }, { A, 5 }, { NOTHING,  50 }, { A, 5 }, \
	{ NOTHING,  50 }, { A, 5 }, { NOTHING,  50 }, { A, 5 }, \
	{ NOTHING,  50 }, { A, 5 }, { NOTHING,  50 }, { A, 5 }, \
	{ NOTHING,  50 }, { A, 5 }, { NOTHING,  50 }, { A, 5 }, \
	{ NOTHING,  50 }, { A, 5 }, { NOTHING,  50 }, { A, 5 }, \
	{ NOTHING,  50 }, { A, 5 }, { NOTHING,  50 }, { A, 5 }, \
	{ NOTHING,  30 }, { B, 5 }, { NOTHING,  10 }, { B, 5 }, \
	{ NOTHING,  10 }, { B, 5 }, { NOTHING,  10 }, { B, 5 }, \
	{ NOTHING,  10 }
	
#define GET_EGG_2() \
	{ UPLEFT, 10 }, { NOTHING, 20 }, { A, 5 }, { NOTHING, 50 }, \
	{ A, 5 }, { NOTHING, 50 }, { A, 5 }, { NOTHING, 50 }, \
	{ A, 5 }, { NOTHING, 50 }, { A, 5 }, { NOTHING, 50 }, \
	{ A, 5 }, { NOTHING, 50 }, { A, 5 }, { NOTHING, 50 }, \
	{ A, 5 }, { NOTHING, 100 }, { DOWN, 5 }, { NOTHING, 20 }, \
	{ A, 5 }, { NOTHING, 20 }, { B, 5 }, { NOTHING, 50 }, \
	{ B, 5 }, { NOTHING, 40 }, { B, 5 }, { NOTHING, 70 }, \
	{ B, 5 }, { NOTHING, 50 }

#define GET_EGG_3() \
	{ UPLEFT, 10 }, { NOTHING, 20 }, { A, 5 }, { NOTHING, 50 }, \
	{ A, 5 }, { NOTHING, 50 }, { A, 5 }, { NOTHING, 50 }, \
	{ A, 5 }, { NOTHING, 50 }, { A, 5 }, { NOTHING, 50 }, \
	{ A, 5 }, { NOTHING, 50 }, { A, 5 }, { NOTHING, 50 }, \
	{ A, 5 }, { NOTHING, 100 }, { DOWN, 5 }, { NOTHING, 10 }, \
	{ DOWN, 5 }, { NOTHING, 20 }, { A, 5 }, { NOTHING, 20 }, \
	{ B, 5 }, { NOTHING, 50 }, { B, 5 }, { NOTHING, 40 }, \
	{ B, 5 }, { NOTHING, 70 }, { B, 5 }, { NOTHING, 50}, 

#define CIRCLE_CW(length) \
	{ RIGHT, length }, { DOWNRIGHT, length }, { DOWN, length }, { DOWNLEFT, length }, \
	{ LEFT, length }, { UPLEFT, length }, { UP, length }, { UPRIGHT, length }
 
#define CIRCLE_CW_12(length) \
	CIRCLE_CW(length), CIRCLE_CW(length), CIRCLE_CW(length), CIRCLE_CW(length),  \
	CIRCLE_CW(length), CIRCLE_CW(length), CIRCLE_CW(length), CIRCLE_CW(length),  \
	CIRCLE_CW(length), CIRCLE_CW(length), CIRCLE_CW(length), CIRCLE_CW(length)

#define CIRCLE_CW_6(length) \
	CIRCLE_CW(length), CIRCLE_CW(length), CIRCLE_CW(length), CIRCLE_CW(length),  \
	CIRCLE_CW(length), CIRCLE_CW(length)

#define SET_UP_BIKE() \
	{ DOWN, 15 }, { NOTHING,  25 }, { PLUS,  5 }, { NOTHING,  50 }
	
#define SET_UP_ROUTE() \
	{ RIGHT, 50 }, { UPRIGHT, 40 }, { RIGHT, 220 }, { DOWNRIGHT, 50 }, \
	{ RIGHTB, 50 },	{ RIGHT, 50 },	{ RIGHTB, 50 }, { RIGHT, 50 }, \
	{ RIGHTB, 50 },	{ RIGHT, 50 },	{ RIGHTB, 50 },	{ RIGHT, 50 }
	
#define EGG_HATCH_ROUTINE() \
	{ DOWNLEFT, 80 }, \
	{ LEFTB, 50 },	{ LEFT, 50 },	{ LEFTB, 50 }, { LEFT, 50 }, \
	{ LEFTB, 50 },	{ LEFT, 50 },	{ LEFTB, 50 },	{LEFT, 50 }, \
	{ LEFTB, 50 },	{ LEFT, 50 },  { LEFTB, 50 }, { DOWNRIGHT, 30 }, \
	{ RIGHTB, 50 },	{ RIGHT, 50 },	{ RIGHTB, 50 }, { RIGHT, 50 }, \
	{ RIGHTB, 50 },	{ RIGHT, 50 },	{ RIGHTB, 50 },	{ RIGHT, 50 },	\
	{ RIGHTB, 50 },	{ RIGHT, 50 },	{ RIGHTB, 50 },	{ RIGHT, 50 }

#define ROUTINE_5120() \
	EGG_HATCH_ROUTINE(), EGG_HATCH_ROUTINE(), EGG_HATCH_ROUTINE(), EGG_HATCH_ROUTINE(), \
	EGG_HATCH_ROUTINE()
	

#define UP_TO_DAYCARE() \
	{ RIGHT, 60 }, { DOWN, 40 }, { RIGHT, 30 }, { UP, 185 }, \
	{ RIGHT, 15 }, { UP, 95 }, { UPLEFT , 7 }
	
#define EGG_GET_ROUTINE() \
	CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4), \
	{ NOTHING, 20 }, { MINUS, 5 }, { NOTHING, 20 }, { UP, 50 }, \
	{ UPRIGHT, 30 }, { DOWNRIGHT, 10 }, { UPRIGHT, 10 }, { UPLEFT, 10 }

#define EGG_HATCH_SLOW() \
	{ B, 5 }, { NOTHING,  250 }, { B, 5 }, { NOTHING,  250 }, \
	{ B, 5 }, { NOTHING,  250 }, { B, 5 }, { NOTHING,  250 }, \
	{ B, 5 }, { NOTHING,  250 }

#define WARP_BACK() \
	{ X, 5 }, { NOTHING,  50 }, { A, 5 }, { NOTHING,  50 }, \
	{ A, 5 }, { NOTHING,  50 }, { A, 5 }, { NOTHING,  50 }, \
	{ A, 5 }, { NOTHING,  50 }, { A, 5 }, { NOTHING,  250 }, \
	{ MINUS, 5 }, { NOTHING,  50 } 
	
// Egg hatch stes

// Morkpeko
#define SINGLE_HATCH_2560() \
	CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4)
//Untested


// Rookidee, Blipbu, Nickit, Wooloo, Rolycoly, Zigzagoon
#define SINGLE_HATCH_3840() \
	CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4), \
	CIRCLE_CW_12(4)
//Untested


// Grookey, Scorbunny, Sobble, Skwovet, Gossifleur, Chewtle, Yamper, 
// Applin, Silicobra, Arrokuda, Slizzlipede, Sinistea, Hatenna,
// Impidimp, Perrserker, Cursola, Farfetch'd, Milcery, Pinchurin,
// Snom, 
#define SINGLE_HATCH_5120() \
	CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4), \
	CIRCLE_CW_12(4), CIRCLE_CW_12(4)
	
// Toxel, Clobbopus, Mr. Mime, Runerigus, Falinks, Eiscue, Cufant
#define SINGLE_HATCH_6400() \
	CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4), \
	CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4), \
	CIRCLE_CW_12(4)
//Untested	

// Duraludon
#define SINGLE_HATCH_7680() \
	CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4), \
	CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4), \
	CIRCLE_CW_12(4)
//Untested	

// Indeedee, Dreepy
#define SINGLE_HATCH_10240 \
	CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4), \
	CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4), \
	CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4)
//Untested




// Joystick HID report structure. We have an input and an output.
typedef struct {
	uint16_t Button; // 16 buttons; see JoystickButtons_t for bit mapping
	uint8_t  HAT;    // HAT switch; one nibble w/ unused nibble
	uint8_t  LX;     // Left  Stick X
	uint8_t  LY;     // Left  Stick Y
	uint8_t  RX;     // Right Stick X
	uint8_t  RY;     // Right Stick Y
	uint8_t  VendorSpec;
} USB_JoystickReport_Input_t;

// The output is structured as a mirror of the input.
// This is based on initial observations of the Pokken Controller.
typedef struct {
	uint16_t Button; // 16 buttons; see JoystickButtons_t for bit mapping
	uint8_t  HAT;    // HAT switch; one nibble w/ unused nibble
	uint8_t  LX;     // Left  Stick X
	uint8_t  LY;     // Left  Stick Y
	uint8_t  RX;     // Right Stick X
	uint8_t  RY;     // Right Stick Y
} USB_JoystickReport_Output_t;

// Function Prototypes
// Setup all necessary hardware, including USB initialization.
void SetupHardware(void);
// Process and deliver data from IN and OUT endpoints.
void HID_Task(void);
// USB device event handlers.
void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_Disconnect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_ControlRequest(void);
// Prepare the next report for the host.
void GetNextReport(USB_JoystickReport_Input_t* const ReportData);

#endif
