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

// This routine causes the player to move in a clockwise circle
// The length parameter increases amonut of time each direction is pressed, thereby increasing circle radius
#define CIRCLE_CW(length) \
    { RIGHT, length }, { DOWNRIGHT, length }, { DOWN, length }, { DOWNLEFT, length }, \
    { LEFT, length }, { UPLEFT, length }, { UP, length }, { UPRIGHT, length }

// This routine performs 6 clockwise circles
#define CIRCLE_CW_6(length) \
    CIRCLE_CW(length), CIRCLE_CW(length), CIRCLE_CW(length), CIRCLE_CW(length),  \
    CIRCLE_CW(length), CIRCLE_CW(length)

// This routine is performs 12 clockwise circles
#define CIRCLE_CW_12(length) \
    CIRCLE_CW(length), CIRCLE_CW(length), CIRCLE_CW(length), CIRCLE_CW(length),  \
    CIRCLE_CW(length), CIRCLE_CW(length), CIRCLE_CW(length), CIRCLE_CW(length),  \
    CIRCLE_CW(length), CIRCLE_CW(length), CIRCLE_CW(length), CIRCLE_CW(length)

// This routine initiates the controller connection
// This routine must be accounted for in box operations using the RELEASE_RESET() macro
#define CONTROLLER_SETUP() \
    { NOTHING, 250 }, { TRIGGERS, 5 }, { NOTHING, 150 }, { TRIGGERS, 5 }, \
    { NOTHING, 150 }, { A, 5 }, { NOTHING, 250 }
    
// This moves the user in bike circles before moving back to the daycare lady
// This code must be used after the SET_UP_BIKE() macro
// Time is variable so this macro is currently part of the nonfunctional multi-hatch project
#define EGG_GET_ROUTINE() \
    CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4), \
    { NOTHING, 20 }, { MINUS, 5 }, { NOTHING, 20 }, { UP, 50 }, \
    { UPRIGHT, 30 }, { DOWNRIGHT, 10 }, { UPRIGHT, 10 }, { UPLEFT, 10 }

// This hatches 2 5120 base step eggs
// Time is variable so this macro is currently part of the nonfunctional multi-hatch project
#define EGG_HATCH_ROUTINE() \
    { DOWNLEFT, 80 }, \
    { LEFTB, 50 },    { LEFT, 50 },    { LEFTB, 50 }, { LEFT, 50 }, \
    { LEFTB, 50 },    { LEFT, 50 },    { LEFTB, 50 },    {LEFT, 50 }, \
    { LEFTB, 50 },    { LEFT, 50 },  { LEFTB, 50 }, { DOWNRIGHT, 30 }, \
    { RIGHTB, 50 },    { RIGHT, 50 },    { RIGHTB, 50 }, { RIGHT, 50 }, \
    { RIGHTB, 50 },    { RIGHT, 50 },    { RIGHTB, 50 },    { RIGHT, 50 },    \
    { RIGHTB, 50 },    { RIGHT, 50 },    { RIGHTB, 50 },    { RIGHT, 50 }

// This performs an egg hatch slowly and safely for the single hatch scripts
// This can be optimized further 
#define EGG_HATCH_SLOW() \
    { B, 5 }, { NOTHING,  250 }, { B, 5 }, { NOTHING,  250 }, \
    { B, 5 }, { NOTHING,  250 }, { B, 5 }, { NOTHING,  250 }, \
    { B, 5 }, { NOTHING,  250 }

// This retrieves an egg and puts it in slot 1
// This code can be optimized in order to implement multi-hatch scripts
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
    
// This retrieves an egg and puts it in slot 2
// This code can be optimized in order to implement multi-hatch scripts
#define GET_EGG_2() \
    { UPLEFT, 10 }, { NOTHING, 20 }, { A, 5 }, { NOTHING, 50 }, \
    { A, 5 }, { NOTHING, 50 }, { A, 5 }, { NOTHING, 50 }, \
    { A, 5 }, { NOTHING, 50 }, { A, 5 }, { NOTHING, 50 }, \
    { A, 5 }, { NOTHING, 50 }, { A, 5 }, { NOTHING, 50 }, \
    { A, 5 }, { NOTHING, 100 }, { DOWN, 5 }, { NOTHING, 20 }, \
    { A, 5 }, { NOTHING, 20 }, { B, 5 }, { NOTHING, 50 }, \
    { B, 5 }, { NOTHING, 40 }, { B, 5 }, { NOTHING, 70 }, \
    { B, 5 }, { NOTHING, 50 }

// This retrieves an egg and puts it in slot 3
// This code can be optimized in order to implement multi-hatch scripts
#define GET_EGG_3() \
    { UPLEFT, 10 }, { NOTHING, 20 }, { A, 5 }, { NOTHING, 50 }, \
    { A, 5 }, { NOTHING, 50 }, { A, 5 }, { NOTHING, 50 }, \
    { A, 5 }, { NOTHING, 50 }, { A, 5 }, { NOTHING, 50 }, \
    { A, 5 }, { NOTHING, 50 }, { A, 5 }, { NOTHING, 50 }, \
    { A, 5 }, { NOTHING, 100 }, { DOWN, 5 }, { NOTHING, 10 }, \
    { DOWN, 5 }, { NOTHING, 20 }, { A, 5 }, { NOTHING, 20 }, \
    { B, 5 }, { NOTHING, 50 }, { B, 5 }, { NOTHING, 40 }, \
    { B, 5 }, { NOTHING, 70 }, { B, 5 }, { NOTHING, 50} 

// This releases an entire box of pokemon
#define RELEASE_BOX() \
	RELEASE_ROW(), MOVE_NEW_ROW(), RELEASE_ROW(), MOVE_NEW_ROW(), \
	RELEASE_ROW(), MOVE_NEW_ROW(), RELEASE_ROW(), MOVE_NEW_ROW(), \
	RELEASE_ROW()

// This is used to change to the correct box when you first plug in the controller
#define RELEASE_RESET() \
	{ B,  250 }, { NOTHING,  10 }, { UP,   5 }, { NOTHING,  10 }, \
	{ RIGHT,   5 }, { NOTHING,  10 }, { DOWN,   5 }, { NOTHING,  10 }
	
// This releases an indvidual pokemon
#define RELEASE_POKEMON() \
	{ A,  10 }, { NOTHING,  10 }, { UP,  10 }, { NOTHING,  10 }, \
	{ UP,  10 }, { NOTHING,  10 }, { A,  10 }, { NOTHING,  40 }, \
	{ UP,  10 }, { NOTHING,  10 }, { A,  10 }, { NOTHING,  40 }, \
	{ A,  10 }, { NOTHING,  20 }

// This releases a row of pokemon
#define RELEASE_ROW() \
	RELEASE_POKEMON(), { RIGHT,  10 }, { NOTHING,  20 }, \
	RELEASE_POKEMON(), { RIGHT,  10 }, { NOTHING,  20 }, \
	RELEASE_POKEMON(), { RIGHT,  10 }, { NOTHING,  20 }, \
	RELEASE_POKEMON(), { RIGHT,  10 }, { NOTHING,  20 }, \
	RELEASE_POKEMON(), { RIGHT,  10 }, { NOTHING,  20 }, \
	RELEASE_POKEMON()

// This moves from one row to the next
#define MOVE_NEW_ROW() \
	{ RIGHT,  10 }, { NOTHING,  30 }, { RIGHT,  10 }, { NOTHING,  10 }, \
	{ DOWN,  10 }, { NOTHING,  10 }

// This moves to the next box after releasing is finished
#define MOVE_NEW_BOX() \
	{ RIGHT,  10 }, { NOTHING,  30 }, { RIGHT,  10 }, { NOTHING,  10 }, \
	{ DOWN,  10 }, { NOTHING,  10 }, { DOWN,  10 }, { NOTHING,  10 }, \
	{ RIGHT,  10 }, { NOTHING,  20 }, { DOWN,  10 }, { NOTHING,  10 }

// This repeatedly performs the EGG_GET_ROUTINE() for 2 5120 base egg step eggs for multi-hatch scripts
// Time is variable so this macro is currently part of the nonfunctional multi-hatch project
#define ROUTINE_5120() \
    EGG_HATCH_ROUTINE(), EGG_HATCH_ROUTINE(), EGG_HATCH_ROUTINE(), EGG_HATCH_ROUTINE(), \
    EGG_HATCH_ROUTINE()

// This moves the player down from the day care lady and sets up the bike
#define SET_UP_BIKE() \
    { DOWN, 15 }, { NOTHING,  25 }, { PLUS,  5 }, { NOTHING,  50 }
    
// This sets up the route for the ROUTINE_XXXX() macro 
// Time is variable so this macro is currently part of the nonfunctional multi-hatch project
#define SET_UP_ROUTE() \
    { RIGHT, 50 }, { UPRIGHT, 40 }, { RIGHT, 220 }, { DOWNRIGHT, 50 }, \
    { RIGHTB, 50 },    { RIGHT, 50 },    { RIGHTB, 50 }, { RIGHT, 50 }, \
    { RIGHTB, 50 },    { RIGHT, 50 },    { RIGHTB, 50 },    { RIGHT, 50 }

// This moves the player up to the daycare from the camp area
#define UP_TO_DAYCARE() \
    { RIGHT, 60 }, { DOWN, 40 }, { RIGHT, 30 }, { UP, 185 }, \
    { RIGHT, 15 }, { UP, 95 }, { UPLEFT , 7 }

// This warps the player back to the starting location at the camp
#define WARP_BACK() \
    { X, 5 }, { NOTHING,  50 }, { A, 5 }, { NOTHING,  50 }, \
    { A, 5 }, { NOTHING,  50 }, { A, 5 }, { NOTHING,  50 }, \
    { A, 5 }, { NOTHING,  50 }, { A, 5 }, { NOTHING,  250 }, \
    { MINUS, 5 }, { NOTHING,  50 } 

// Single Hatch Egg Step macros are below
// Each macro is acompanies by the pokemon that it works for
// These macros are currently functional but multi-hatch macros are not
   
// Morkpeko
#define SINGLE_HATCH_2560() \
    CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4)

// Rookidee, Blipbu, Nickit, Wooloo, Rolycoly, Zigzagoon
#define SINGLE_HATCH_3840() \
    CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4), CIRCLE_CW_12(4), \
    CIRCLE_CW_12(4)

// Grookey, Scorbunny, Sobble, Skwovet, Gossifleur, Chewtle, Yamper, 
// Applin, Silicobra, Arrokuda, Slizzlipede, Sinistea, Hatenna,
// Impidimp, Perrserker, Cursola, Farfetch'd, Milcery, Pinchurin,
// Snom
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
