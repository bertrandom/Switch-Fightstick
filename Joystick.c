/*
Nintendo Switch Fightstick - Proof-of-Concept

Based on the LUFA library's Low-Level Joystick Demo
    (C) Dean Camera
Based on the HORI's Pokken Tournament Pro Pad design
    (C) HORI

This project implements a modified version of HORI's Pokken Tournament Pro Pad
USB descriptors to allow for the creation of custom controllers for the
Nintendo Switch. This also works to a limited degree on the PS3.

Since System Update v3.0.0, the Nintendo Switch recognizes the Pokken
Tournament Pro Pad as a Pro Controller. Physical design limitations prevent
the Pokken Controller from functioning at the same level as the Pro
Controller. However, by default most of the descriptors are there, with the
exception of Home and Capture. Descriptor modification allows us to unlock
these buttons for our use.
*/

#include "Joystick.h"

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UPLEFT,
    UPRIGHT,
    DOWNLEFT, 
    DOWNRIGHT,
    LEFTB,
    RIGHTB,
    DOWNB,
    X,
    Y,
    A,
    B,
    L,
    R,
    PLUS,
    MINUS,
    NOTHING,
    HOME,
    TRIGGERS
} Buttons_t;

typedef struct {
    Buttons_t button;
    uint16_t duration;
} command; 

static const command step1[] = {
    CONTROLLER_SETUP(), // Setup controller

    ///// Basic circles hatcher /////
    /*
    SINGLE_HATCH_2560(), // Used here to repeatedly hatch eggs
    EGG_HATCH_SLOW() // Used here to repeatedly hatch eggs
    */

    ///// Digger automation ///// 
    /*
    { A, 5 }, { NOTHING, 5 },
    */

    ///// 2560 base egg steps multi hatcher /////
    /* 
    UP_TO_DAYCARE(), // Go up to the daycare lady
    GET_EGG_1(), // Get the first egg
    SET_UP_MULTI(), // Sets up the bike path
    SINGLE_HATCH_2560(), // Hatch a single 2560 base steps egg
    EGG_HATCH_SLOW(), // Slowly and safely hatch an egg
    MULTI_TO_DAYCARE(), // Returns to the right side of daycare lady
    GET_EGG_1(), // Get the first egg
    SET_UP_MULTI(), // Sets up the bike path
    SINGLE_HATCH_2560(), // Hatch a single 2560 base steps egg
    EGG_HATCH_SLOW(), // Slowly and safely hatch an egg
    MULTI_TO_DAYCARE(), // Returns to the right side of daycare lady
    GET_EGG_1(), // Get the first egg
    SET_UP_MULTI(), // Sets up the bike path
    SINGLE_HATCH_2560(), // Hatch a single 2560 base steps egg
    EGG_HATCH_SLOW(), // Slowly and safely hatch an egg
    MULTI_TO_DAYCARE(), // Returns to the right side of daycare lady
    GET_EGG_1(), // Get the first egg
    SET_UP_MULTI(), // Sets up the bike path
    SINGLE_HATCH_2560(), // Hatch a single 2560 base steps egg
    EGG_HATCH_SLOW(), // Slowly and safely hatch an egg
    MULTI_TO_DAYCARE(), // Returns to the right side of daycare lady
    GET_EGG_1(), // Get the first egg
    SET_UP_MULTI(), // Sets up the bike path
    SINGLE_HATCH_2560(), // Hatch a single 2560 base steps egg
    EGG_HATCH_SLOW(), // Slowly and safely hatch an egg
    WARP_BACK(), // Warp back to the camp to reset the script
    */ 

    ///// 3840 base egg steps multi hatcher /////
    /* 
    UP_TO_DAYCARE(), // Go up to the daycare lady
    GET_EGG_1(), // Get the first egg
    SET_UP_MULTI(), // Sets up the bike path
    SINGLE_HATCH_3840(), // Hatch a single 3840 base steps egg
    EGG_HATCH_SLOW(), // Slowly and safely hatch an egg
    MULTI_TO_DAYCARE(), // Returns to the right side of daycare lady
    GET_EGG_1(), // Get the first egg
    SET_UP_MULTI(), // Sets up the bike path
    SINGLE_HATCH_3840(), // Hatch a single 3840 base steps egg
    EGG_HATCH_SLOW(), // Slowly and safely hatch an egg
    MULTI_TO_DAYCARE(), // Returns to the right side of daycare lady
    GET_EGG_1(), // Get the first egg
    SET_UP_MULTI(), // Sets up the bike path
    SINGLE_HATCH_3840(), // Hatch a single 3840 base steps egg
    EGG_HATCH_SLOW(), // Slowly and safely hatch an egg
    MULTI_TO_DAYCARE(), // Returns to the right side of daycare lady
    GET_EGG_1(), // Get the first egg
    SET_UP_MULTI(), // Sets up the bike path
    SINGLE_HATCH_3840(), // Hatch a single 3840 base steps egg
    EGG_HATCH_SLOW(), // Slowly and safely hatch an egg
    WARP_BACK(), // Warp back to the camp to reset the script
    */ 

    ///// 5120 base egg steps multi hatcher /////
    /*
    UP_TO_DAYCARE(), // Go up to the daycare lady
    GET_EGG_1(), // Get the first egg
    SET_UP_MULTI(), // Sets up the bike path
    MULTI_HATCH_PIECE(), // Bikes in circles waiting for eggs to be ready
    MULTI_TO_DAYCARE(), // Returns to the right side of daycare lady
    GET_EGG_2(), // Get the second egg
    SET_UP_MULTI(), // Sets up the bike path
    MULTI_HATCH_PIECE(), // Bikes in circles waiting for eggs to be ready
    MULTI_TO_DAYCARE(), // Returns to the right side of daycare lady
    GET_EGG_3(), // Get the third egg
    SET_UP_MULTI(), // Sets up the bike path
    MULTI_HATCH_5120(), // Hatches all of the eggs in the party
    WARP_BACK(), 
    */

    ///// 6400 base egg steps multi hatcher /////
    /* 
    UP_TO_DAYCARE(), // Go up to the daycare lady
    GET_EGG_1(), // Get the first egg
    SET_UP_MULTI(), // Sets up the bike path
    MULTI_HATCH_PIECE(), // Bikes in circles waiting for eggs to be ready
    MULTI_TO_DAYCARE(), // Returns to the right side of daycare lady
    GET_EGG_2(), // Get the second egg
    SET_UP_MULTI(), // Sets up the bike path
    MULTI_HATCH_PIECE(), // Bikes in circles waiting for eggs to be ready
    MULTI_TO_DAYCARE(), // Returns to the right side of daycare lady
    GET_EGG_3(), // Get the third egg
    SET_UP_MULTI(), // Sets up the bike path
    MULTI_HATCH_PIECE(), // Bikes in circles waiting for eggs to be ready
    MULTI_TO_DAYCARE(), // Returns to the right side of daycare lady
    GET_EGG_4(), // Get the third egg
    SET_UP_MULTI(),
    MULTI_HATCH_6400(), // Hatches all of the eggs in the party
    WARP_BACK(), 
    */ 

    ///// 7680 base egg steps multi hatcher /////
    /*
    UP_TO_DAYCARE(), // Go up to the daycare lady
    GET_EGG_1(), // Get the first egg
    SET_UP_MULTI(), // Sets up the bike path
    MULTI_HATCH_PIECE(), // Bikes in circles waiting for eggs to be ready
    MULTI_TO_DAYCARE(), // Returns to the right side of daycare lady
    GET_EGG_2(), // Get the second egg
    SET_UP_MULTI(), // Sets up the bike path
    MULTI_HATCH_PIECE(), // Bikes in circles waiting for eggs to be ready
    MULTI_TO_DAYCARE(), // Returns to the right side of daycare lady
    GET_EGG_3(), // Get the third egg
    SET_UP_MULTI(), // Sets up the bike path
    MULTI_HATCH_PIECE(), // Bikes in circles waiting for eggs to be ready
    MULTI_TO_DAYCARE(), // Returns to the right side of daycare lady
    GET_EGG_4(), // Get the third egg
    SET_UP_MULTI(), // Sets up the bike path
    MULTI_HATCH_7680(), // Hatches all of the eggs in the party
    WARP_BACK(), // Warp back to the camp to reset the script
    */

    ///// 10240 base egg steps multi hatcher /////
    /* 
    UP_TO_DAYCARE(), // Go up to the daycare lady
    GET_EGG_1(), // Get the first egg
    SET_UP_MULTI(), // Step down and get on bike
    MULTI_HATCH_PIECE(), // Bikes in circles waiting for eggs to be ready
    MULTI_TO_DAYCARE(), // Returns to the right side of daycare lady
    GET_EGG_2(), // Get the second egg
    SET_UP_MULTI(), // Step down and get on bike
    MULTI_HATCH_PIECE(), // Bikes in circles waiting for eggs to be ready
    MULTI_TO_DAYCARE(), // Returns to the right side of daycare lady
    GET_EGG_3(), // Get the third egg
    SET_UP_MULTI(), // Step down and get on bike
    MULTI_HATCH_PIECE(), // Bikes in circles waiting for eggs to be ready
    MULTI_TO_DAYCARE(), // Returns to the right side of daycare lady
    GET_EGG_4(), // Get the fourth egg
    SET_UP_MULTI(), // Step down and get on bike
    MULTI_HATCH_PIECE(), // Bikes in circles waiting for eggs to be ready
    MULTI_TO_DAYCARE(), // Returns to the right side of daycare lady
    GET_EGG_5(), // Get the fifth egg
    SET_UP_MULTI(),
    MULTI_HATCH_10240(), // Hatches all of the eggs in the party
    WARP_BACK(), // Warp back to the camp to reset the script
    */ 

    ///// 2560 base egg steps single hatcher /////
    /* 
    UP_TO_DAYCARE(), // Go up to the daycare lady
    GET_EGG_SLOW(), // Get the first egg (non-optimized)
    SET_UP_BIKE(), // Step down and get on bike
    SINGLE_HATCH_2560(), // Hatch a single 2560 base steps egg
    EGG_HATCH_SLOW(), // Slowly and safely hatch an egg
    WARP_BACK(), // Warp back to the camp to reset the script
    */ 

    ///// 3840 base egg steps single hatcher /////
    /* 
    UP_TO_DAYCARE(), // Go up to the daycare lady
    GET_EGG_SLOW(), // Get the first egg (non-optimized)
    SET_UP_BIKE(), // Step down and get on bike
    SINGLE_HATCH_3840(), // Hatch a single 3840 base steps egg
    EGG_HATCH_SLOW(), // Slowly and safely hatch an egg
    WARP_BACK(), // Warp back to the camp to reset the script
    */ 

    ///// 5120 base egg steps single hatcher /////
    /* 
    UP_TO_DAYCARE(), // Go up to the daycare lady
    GET_EGG_SLOW(), // Get the first egg (non-optimized)
    SET_UP_BIKE(), // Step down and get on bike
    SINGLE_HATCH_5120(), // Hatch a single 5120 base steps egg
    EGG_HATCH_SLOW(), // Slowly and safely hatch an egg
    WARP_BACK(), // Warp to the route for a reset
    */ 

    ///// 6400 base egg steps single hatcher /////
    /* 
    UP_TO_DAYCARE(), // Go up to the daycare lady
    GET_EGG_SLOW(), // Get the first egg (non-optimized)
    SET_UP_BIKE(), // Step down and get on bike
    SINGLE_HATCH_6400(), // Hatch a single 6400 base steps egg
    EGG_HATCH_SLOW(), // Slowly and safely hatch an egg
    WARP_BACK(), // Warp to the route for a reset
    */ 

    ///// 7680 base egg steps single hatcher /////
    /* 
    UP_TO_DAYCARE(), // Go up to the daycare lady
    GET_EGG_SLOW(), // Get the first egg (non-optimized)
    SET_UP_BIKE(), // Step down and get on bike
    SINGLE_HATCH_7680(), // Hatch a single 7680 base steps egg
    EGG_HATCH_SLOW(), // Slowly and safely hatch an egg
    WARP_BACK(), // Warp to the route for a reset
    */ 

    ///// 10240 base egg steps single hatcher /////
    /* 
    UP_TO_DAYCARE(), // Go up to the daycare lady
    GET_EGG_SLOW(), // Get the first egg (non-optimized)
    SET_UP_BIKE(), // Step down and get on bike
    SINGLE_HATCH_10240(), // Hatch a single 10240 base steps egg
    EGG_HATCH_SLOW(), // Slowly and safely hatch an egg
    WARP_BACK(), // Warp to the route for a reset
    */ 

    ///// Release script p1 /////
    /*     
    RELEASE_RESET() // Reset box position
    */

    ///// Watt farm script p1/////
    /*     
    DAY_CHANGE(),
    WATT_FARM_DAY()
    */     

    ///// 2560 multi hatch p1 /////
    UP_TO_DAYCARE(),     
    GET_EGG_1() 

};

static const command step2[] = {
    ///// Default /////
    /*
    { NOTHING, 10 }
    */

    ///// Release script p2 /////
    /*
    RELEASE_ROW(), MOVE_NEW_ROW()
    */

    ///// Watt farm script p2/////
    /*
    MONTH_CHANGE_P1(),
    MONTH_CHANGE_P2()
    */ 
    SET_UP_MULTI()
    

};

static const command step3[] = {
    ///// Default /////
    /* 
    { NOTHING, 10 }
    */ 

    ///// Release script p3 /////
    /*
    RELEASE_ROW(), 
    MOVE_NEW_BOX()
    */

    ///// Watt farm script p3 /////
    /*
    YEAR_CHANGE_P1(),
    YEAR_CHANGE_P2()
    */

    ///// 2560 multi hatch p3 //////
    CIRCLE_CW(4)

};

static const command step4[] = {
    ///// Default /////
    /*
    { NOTHING, 10 }
    */

    ///// Release script p4 /////
    /*
    { B, 10 }, { NOTHING, 10 },    
    */

    ///// 2560 multi hatch p3 //////
    EGG_HATCH_SLOW(),
    MULTI_TO_DAYCARE(),
    GET_EGG_1()

    
};

static const command step5[] = {
    ///// Default /////
    { NOTHING, 10 }
};

void stepReport(int stepIndex, USB_JoystickReport_Input_t* const ReportData, int processNum) {
  if (processNum == 1) {
    switch (step1[stepIndex].button) {
      case UP: ReportData->LY = STICK_MIN; break;
      case LEFT: ReportData->LX = STICK_MIN; break;
      case DOWN: ReportData->LY = STICK_MAX; break;
      case RIGHT: ReportData->LX = STICK_MAX; break;
      case HOME: ReportData->Button |= SWITCH_HOME; break;
      case UPLEFT: ReportData->LX = STICK_MIN; ReportData->LY = STICK_MIN; break;
      case UPRIGHT: ReportData->LX = STICK_MAX; ReportData->LY = STICK_MIN; break;
      case DOWNLEFT: ReportData->LX = STICK_MIN; ReportData->LY = STICK_MAX; break;
      case DOWNRIGHT: ReportData->LX = STICK_MAX; ReportData->LY = STICK_MAX; break;
      case LEFTB: ReportData->LX = STICK_MIN; ReportData->Button |= SWITCH_B; break;
      case RIGHTB: ReportData->LX = STICK_MAX; ReportData->Button |= SWITCH_B; break;
      case DOWNB: ReportData->LY = STICK_MAX; ReportData->Button |= SWITCH_B; break;
      case A: ReportData->Button |= SWITCH_A; break;
      case B: ReportData->Button |= SWITCH_B; break;
      case X: ReportData->Button |= SWITCH_X; break;
      case Y: ReportData->Button |= SWITCH_Y; break;
      case L: ReportData->Button |= SWITCH_L; break;
      case R: ReportData->Button |= SWITCH_R; break;
      case PLUS: ReportData->Button |= SWITCH_PLUS; break;    
      case MINUS: ReportData->Button |= SWITCH_MINUS; break;
      case TRIGGERS: ReportData->Button |= SWITCH_L | SWITCH_R; break;
      default: ReportData->LX = STICK_CENTER;
          ReportData->LY = STICK_CENTER;
          ReportData->RX = STICK_CENTER;
          ReportData->RY = STICK_CENTER;
          ReportData->HAT = HAT_CENTER;
          break;
      
    }
  }
  else if (processNum == 2) {
    switch (step2[stepIndex].button) {
      case UP: ReportData->LY = STICK_MIN; break;
      case LEFT: ReportData->LX = STICK_MIN; break;
      case DOWN: ReportData->LY = STICK_MAX; break;
      case RIGHT: ReportData->LX = STICK_MAX; break;
      case HOME: ReportData->Button |= SWITCH_HOME; break;
      case UPLEFT: ReportData->LX = STICK_MIN; ReportData->LY = STICK_MIN; break;
      case UPRIGHT: ReportData->LX = STICK_MAX; ReportData->LY = STICK_MIN; break;
      case DOWNLEFT: ReportData->LX = STICK_MIN; ReportData->LY = STICK_MAX; break;
      case DOWNRIGHT: ReportData->LX = STICK_MAX; ReportData->LY = STICK_MAX; break;
      case LEFTB: ReportData->LX = STICK_MIN; ReportData->Button |= SWITCH_B; break;
      case RIGHTB: ReportData->LX = STICK_MAX; ReportData->Button |= SWITCH_B; break;
      case DOWNB: ReportData->LY = STICK_MAX; ReportData->Button |= SWITCH_B; break;
      case A: ReportData->Button |= SWITCH_A; break;
      case B: ReportData->Button |= SWITCH_B; break;
      case X: ReportData->Button |= SWITCH_X; break;
      case Y: ReportData->Button |= SWITCH_Y; break;
      case L: ReportData->Button |= SWITCH_L; break;
      case R: ReportData->Button |= SWITCH_R; break;
      case PLUS: ReportData->Button |= SWITCH_PLUS; break;    
      case MINUS: ReportData->Button |= SWITCH_MINUS; break;
      case TRIGGERS: ReportData->Button |= SWITCH_L | SWITCH_R; break;
      default: ReportData->LX = STICK_CENTER;
          ReportData->LY = STICK_CENTER;
          ReportData->RX = STICK_CENTER;
          ReportData->RY = STICK_CENTER;
          ReportData->HAT = HAT_CENTER;
          break;
      
    }
  }
  else if (processNum == 3) {
    switch (step3[stepIndex].button) {
      case UP: ReportData->LY = STICK_MIN; break;
      case LEFT: ReportData->LX = STICK_MIN; break;
      case DOWN: ReportData->LY = STICK_MAX; break;
      case RIGHT: ReportData->LX = STICK_MAX; break;
      case HOME: ReportData->Button |= SWITCH_HOME; break;
      case UPLEFT: ReportData->LX = STICK_MIN; ReportData->LY = STICK_MIN; break;
      case UPRIGHT: ReportData->LX = STICK_MAX; ReportData->LY = STICK_MIN; break;
      case DOWNLEFT: ReportData->LX = STICK_MIN; ReportData->LY = STICK_MAX; break;
      case DOWNRIGHT: ReportData->LX = STICK_MAX; ReportData->LY = STICK_MAX; break;
      case LEFTB: ReportData->LX = STICK_MIN; ReportData->Button |= SWITCH_B; break;
      case RIGHTB: ReportData->LX = STICK_MAX; ReportData->Button |= SWITCH_B; break;
      case DOWNB: ReportData->LY = STICK_MAX; ReportData->Button |= SWITCH_B; break;
      case A: ReportData->Button |= SWITCH_A; break;
      case B: ReportData->Button |= SWITCH_B; break;
      case X: ReportData->Button |= SWITCH_X; break;
      case Y: ReportData->Button |= SWITCH_Y; break;
      case L: ReportData->Button |= SWITCH_L; break;
      case R: ReportData->Button |= SWITCH_R; break;
      case PLUS: ReportData->Button |= SWITCH_PLUS; break;    
      case MINUS: ReportData->Button |= SWITCH_MINUS; break;
      case TRIGGERS: ReportData->Button |= SWITCH_L | SWITCH_R; break;
      default: ReportData->LX = STICK_CENTER;
          ReportData->LY = STICK_CENTER;
          ReportData->RX = STICK_CENTER;
          ReportData->RY = STICK_CENTER;
          ReportData->HAT = HAT_CENTER;
          break;
      
    }
  }
  else if (processNum == 4) {
    switch (step4[stepIndex].button) {
      case UP: ReportData->LY = STICK_MIN; break;
      case LEFT: ReportData->LX = STICK_MIN; break;
      case DOWN: ReportData->LY = STICK_MAX; break;
      case RIGHT: ReportData->LX = STICK_MAX; break;
      case HOME: ReportData->Button |= SWITCH_HOME; break;
      case UPLEFT: ReportData->LX = STICK_MIN; ReportData->LY = STICK_MIN; break;
      case UPRIGHT: ReportData->LX = STICK_MAX; ReportData->LY = STICK_MIN; break;
      case DOWNLEFT: ReportData->LX = STICK_MIN; ReportData->LY = STICK_MAX; break;
      case DOWNRIGHT: ReportData->LX = STICK_MAX; ReportData->LY = STICK_MAX; break;
      case LEFTB: ReportData->LX = STICK_MIN; ReportData->Button |= SWITCH_B; break;
      case RIGHTB: ReportData->LX = STICK_MAX; ReportData->Button |= SWITCH_B; break;
      case DOWNB: ReportData->LY = STICK_MAX; ReportData->Button |= SWITCH_B; break;
      case A: ReportData->Button |= SWITCH_A; break;
      case B: ReportData->Button |= SWITCH_B; break;
      case X: ReportData->Button |= SWITCH_X; break;
      case Y: ReportData->Button |= SWITCH_Y; break;
      case L: ReportData->Button |= SWITCH_L; break;
      case R: ReportData->Button |= SWITCH_R; break;
      case PLUS: ReportData->Button |= SWITCH_PLUS; break;    
      case MINUS: ReportData->Button |= SWITCH_MINUS; break;
      case TRIGGERS: ReportData->Button |= SWITCH_L | SWITCH_R; break;
      default: ReportData->LX = STICK_CENTER;
          ReportData->LY = STICK_CENTER;
          ReportData->RX = STICK_CENTER;
          ReportData->RY = STICK_CENTER;
          ReportData->HAT = HAT_CENTER;
          break;
      
    }
  }
  else if (processNum == 5) {
    switch (step5[stepIndex].button) {
      case UP: ReportData->LY = STICK_MIN; break;
      case LEFT: ReportData->LX = STICK_MIN; break;
      case DOWN: ReportData->LY = STICK_MAX; break;
      case RIGHT: ReportData->LX = STICK_MAX; break;
      case HOME: ReportData->Button |= SWITCH_HOME; break;
      case UPLEFT: ReportData->LX = STICK_MIN; ReportData->LY = STICK_MIN; break;
      case UPRIGHT: ReportData->LX = STICK_MAX; ReportData->LY = STICK_MIN; break;
      case DOWNLEFT: ReportData->LX = STICK_MIN; ReportData->LY = STICK_MAX; break;
      case DOWNRIGHT: ReportData->LX = STICK_MAX; ReportData->LY = STICK_MAX; break;
      case LEFTB: ReportData->LX = STICK_MIN; ReportData->Button |= SWITCH_B; break;
      case RIGHTB: ReportData->LX = STICK_MAX; ReportData->Button |= SWITCH_B; break;
      case DOWNB: ReportData->LY = STICK_MAX; ReportData->Button |= SWITCH_B; break;
      case A: ReportData->Button |= SWITCH_A; break;
      case B: ReportData->Button |= SWITCH_B; break;
      case X: ReportData->Button |= SWITCH_X; break;
      case Y: ReportData->Button |= SWITCH_Y; break;
      case L: ReportData->Button |= SWITCH_L; break;
      case R: ReportData->Button |= SWITCH_R; break;
      case PLUS: ReportData->Button |= SWITCH_PLUS; break;    
      case MINUS: ReportData->Button |= SWITCH_MINUS; break;
      case TRIGGERS: ReportData->Button |= SWITCH_L | SWITCH_R; break;
      default: ReportData->LX = STICK_CENTER;
          ReportData->LY = STICK_CENTER;
          ReportData->RX = STICK_CENTER;
          ReportData->RY = STICK_CENTER;
          ReportData->HAT = HAT_CENTER;
          break;
      
    }
  }


}

// Main entry point.
int main(void) {
    // We'll start by performing hardware and peripheral setup.
    SetupHardware();
    // We'll then enable global interrupts for our use.
    GlobalInterruptEnable();
    // Once that's done, we'll enter an infinite loop.
    for (;;)
    {
        // We need to run our task to process and deliver data for our IN and OUT endpoints.
        HID_Task();
        // We also need to run the main USB management task.
        USB_USBTask();
    }
}

// Configures hardware and peripherals, such as the USB peripherals.
void SetupHardware(void) {
    // We need to disable watchdog if enabled by bootloader/fuses.
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    // We need to disable clock division before initializing the USB hardware.
    clock_prescale_set(clock_div_1);
    // We can then initialize our hardware and peripherals, including the USB stack.

    #ifdef ALERT_WHEN_DONE
    // Both PORTD and PORTB will be used for the optional LED flashing and buzzer.
    #warning LED and Buzzer functionality enabled. All pins on both PORTB and \
PORTD will toggle when printing is done.
    DDRD  = 0xFF; //Teensy uses PORTD
    PORTD =  0x0;
                  //We'll just flash all pins on both ports since the UNO R3
    DDRB  = 0xFF; //uses PORTB. Micro can use either or, but both give us 2 LEDs
    PORTB =  0x0; //The ATmega328P on the UNO will be resetting, so unplug it?
    #endif
    // The USB stack should be initialized last.
    USB_Init();
}

// Fired to indicate that the device is enumerating.
void EVENT_USB_Device_Connect(void) {
}

// Fired to indicate that the device is no longer connected to a host.
void EVENT_USB_Device_Disconnect(void) {
}

// Fired when the host set the current configuration of the USB device after enumeration.
void EVENT_USB_Device_ConfigurationChanged(void) {
    bool ConfigSuccess = true;

    // We setup the HID report endpoints.
    ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK_OUT_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);
    ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK_IN_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);

    // We can read ConfigSuccess to indicate a success or failure at this point.
}

// Process control requests sent to the device from the USB host.
void EVENT_USB_Device_ControlRequest(void) {
}

// Process and deliver data from IN and OUT endpoints.
void HID_Task(void) {
    // If the device isn't connected and properly configured, we can't do anything here.
    if (USB_DeviceState != DEVICE_STATE_Configured)
        return;

    // We'll start with the OUT endpoint.
    Endpoint_SelectEndpoint(JOYSTICK_OUT_EPADDR);
    // We'll check to see if we received something on the OUT endpoint.
    if (Endpoint_IsOUTReceived())
    {
        // If we did, and the packet has data, we'll react to it.
        if (Endpoint_IsReadWriteAllowed())
        {
            // We'll create a place to store our data received from the host.
            USB_JoystickReport_Output_t JoystickOutputData;
            // We'll then take in that data, setting it up in our storage.
            while(Endpoint_Read_Stream_LE(&JoystickOutputData, sizeof(JoystickOutputData), NULL) != ENDPOINT_RWSTREAM_NoError);
            // At this point, we can react to this data.

            // However, since we're not doing anything with this data, we abandon it.
        }
        // Regardless of whether we reacted to the data, we acknowledge an OUT packet on this endpoint.
        Endpoint_ClearOUT();
    }

    // We'll then move on to the IN endpoint.
    Endpoint_SelectEndpoint(JOYSTICK_IN_EPADDR);
    // We first check to see if the host is ready to accept data.
    if (Endpoint_IsINReady())
    {
        // We'll create an empty report.
        USB_JoystickReport_Input_t JoystickInputData;
        // We'll then populate this report with what we want to send to the host.
        GetNextReport(&JoystickInputData);
        // Once populated, we can output this data to the host. We do this by first writing the data to the control stream.
        while(Endpoint_Write_Stream_LE(&JoystickInputData, sizeof(JoystickInputData), NULL) != ENDPOINT_RWSTREAM_NoError);
        // We then send an IN packet on this endpoint.
        Endpoint_ClearIN();
    }
}

typedef enum {
    SYNC_CONTROLLER,
    SYNC_POSITION,
    BREATHE,
    PROCESS_1,
    PROCESS_2, 
    PROCESS_3,
    PROCESS_4,
    PROCESS_5,
    CLEANUP,
    DONE
} State_t;
State_t state = SYNC_CONTROLLER;

#define ECHOES 2
int echoes = 0;
USB_JoystickReport_Input_t last_report;

int report_count = 0;
int xpos = 0;
int ypos = 0;
int bufindex = 0;
int duration_count = 0;
int portsval = 0;
int process1iterator = 0;
int process2iterator = 0;
int process3iterator = 0;
int process4iterator = 0;
int process5iterator = 0;

// Prepare the next report for the host.
void GetNextReport(USB_JoystickReport_Input_t* const ReportData) {


    // Prepare an empty report
    memset(ReportData, 0, sizeof(USB_JoystickReport_Input_t));
    ReportData->LX = STICK_CENTER;
    ReportData->LY = STICK_CENTER;
    ReportData->RX = STICK_CENTER;
    ReportData->RY = STICK_CENTER;
    ReportData->HAT = HAT_CENTER;

    // Repeat ECHOES times the last report
    if (echoes > 0)
    {
        memcpy(ReportData, &last_report, sizeof(USB_JoystickReport_Input_t));
        echoes--;
        return;
    }

    // States and moves management
    switch (state)
    {

        case SYNC_CONTROLLER:
            state = BREATHE;
            break;

        case SYNC_POSITION:
            bufindex = 0;

            ReportData->Button = 0;
            ReportData->LX = STICK_CENTER;
            ReportData->LY = STICK_CENTER;
            ReportData->RX = STICK_CENTER;
            ReportData->RY = STICK_CENTER;
            ReportData->HAT = HAT_CENTER;


            state = BREATHE;
            break;

        case BREATHE:
            state = PROCESS_1;
            break;

        case PROCESS_1:
            stepReport(bufindex, ReportData, 1); 

            duration_count++;

            if (duration_count > step1[bufindex].duration) {
                bufindex++;
                duration_count = 0;                
            }


            if (bufindex > (int)( sizeof(step1) / sizeof(step1[0])) - 1) {
                ///// Default script /////
                /*
                state = BREATHE;
                
                bufindex = 7;
                duration_count = 0;
                */ 

                ///// Release script /////
                /* 
                bufindex = 0;
                duration_count = 0;
                
                process1iterator++; 
                process2iterator = 0; 
                process3iterator = 0; 
                process4iterator = 0; 
                process5iterator = 0; 

                state = PROCESS_2;
                */ 

                ///// Watt farm script ////
                /*
                bufindex = 7;
                duration_count = 0;

                if (process1iterator < 23) {
                    bufindex = 7;
                    duration_count = 0;
                    process1iterator++;
                    state = PROCESS_1;
                }
                else {
                    process1iterator = 0;
                    duration_count = 0;
                    bufindex = 0;
                    state = PROCESS_2;
                }
                */

                ///// 2560 multi hatch /////
                bufindex = 0;
                duration_count = 0;
                state = PROCESS_2;


                ReportData->LX = STICK_CENTER;
                ReportData->LY = STICK_CENTER;
                ReportData->RX = STICK_CENTER;
                ReportData->RY = STICK_CENTER;
                ReportData->HAT = HAT_CENTER;
            }

            break;

        case PROCESS_2:
            stepReport(bufindex, ReportData, 2); 

            duration_count++;

            if (duration_count > step2[bufindex].duration) {
                bufindex++;
                duration_count = 0;                
            }

            if (bufindex > (int)( sizeof(step2) / sizeof(step2[0])) - 1) {
                bufindex = 0;
                duration_count = 0;

                ///// Default script /////
                /*
                state = BREATHE;
                
                bufindex = 7;
                duration_count = 0;
                */

                ///// Release script /////
                /* 
                if (process2iterator < 3) {
                    process1iterator = 0; 
                    process2iterator++;
                    state = PROCESS_2;
                }
                else {
                    state = PROCESS_3;
                }
                */

                ///// Watt farm script p2 /////
                /*
                if (process2iterator < 10) {
                    bufindex = 7;
                    duration_count = 0;
                    process2iterator++; 
                    state = PROCESS_1; 
                } 
                else {
                    bufindex = 0;
                    duration_count = 0;
                    process1iterator = 0; 
                    process2iterator = 0; 
                    state = PROCESS_3;
                }
                */

                ///// 2560 multi hatch p2 /////
                bufindex = 0;
                duration_count = 0;
                process3iterator = 0;
                state = PROCESS_3;


                ReportData->LX = STICK_CENTER;
                ReportData->LY = STICK_CENTER;
                ReportData->RX = STICK_CENTER;
                ReportData->RY = STICK_CENTER;
                ReportData->HAT = HAT_CENTER;
            }
            break;

        case PROCESS_3:
            stepReport(bufindex, ReportData, 3); 

            duration_count++;

            if (duration_count > step3[bufindex].duration) {
                bufindex++;
                duration_count = 0;                
            }


            if (bufindex > (int)( sizeof(step3) / sizeof(step3[0])) - 1) {
                bufindex = 0;
                duration_count = 0;

                ///// Default script /////
                /*
                state = BREATHE;
                
                bufindex = 7;
                duration_count = 0;
                */

                ///// Release script /////
                /*
                if (process3iterator < 5) {
                    process3iterator ++;
                    process2iterator = 0; 
                    state = PROCESS_2;
                }
                else {
                    state = PROCESS_4;
                }
                */

                ///// Watt farm script /////
                /*
                bufindex = 7;
                duration_count = 0;

                process1iterator = 0; 
                process2iterator = 0; 
                state = PROCESS_1; 
                */

                ///// 2560 multi hatch /////
                bufindex = 0;
                duration_count = 0;

                process3iterator++;
                if(process3iterator < 35) {
                    state = PROCESS_3;
                }
                else {
                    state = PROCESS_4;
                }

                ReportData->LX = STICK_CENTER;
                ReportData->LY = STICK_CENTER;
                ReportData->RX = STICK_CENTER;
                ReportData->RY = STICK_CENTER;
                ReportData->HAT = HAT_CENTER;
            }
            break;

        case PROCESS_4:
            stepReport(bufindex, ReportData, 4); 

            duration_count++;

            if (duration_count > step4[bufindex].duration) {
                bufindex++;
                duration_count = 0;                
            }


            if (bufindex > (int)( sizeof(step4) / sizeof(step4[0])) - 1) {

                ///// default /////
                /*
                bufindex = 7;
                duration_count = 0;
                state = BREATHE;
                */
                ///// Release /////
                /*
                bufindex = 0;
                duration_count = 0;
                state = PROCESS_4;

                process4iterator++;
                */

                bufindex = 0;
                duration_count = 0;

                state = PROCESS_2;

                ReportData->LX = STICK_CENTER;
                ReportData->LY = STICK_CENTER;
                ReportData->RX = STICK_CENTER;
                ReportData->RY = STICK_CENTER;
                ReportData->HAT = HAT_CENTER;
            }
            break;

        case PROCESS_5:
            stepReport(bufindex, ReportData, 5); 

            duration_count++;

            if (duration_count > step5[bufindex].duration) {
                bufindex++;
                duration_count = 0;                
            }


            if (bufindex > (int)( sizeof(5) / sizeof(step5[0])) - 1) {
                bufindex = 7;
                duration_count = 0;

                state = BREATHE;

                process1iterator = 0; 
                process2iterator = 0; 
                process3iterator = 0; 
                process4iterator = 0; 
                process5iterator++;

                ReportData->LX = STICK_CENTER;
                ReportData->LY = STICK_CENTER;
                ReportData->RX = STICK_CENTER;
                ReportData->RY = STICK_CENTER;
                ReportData->HAT = HAT_CENTER;
            }
            break;

        case CLEANUP:
            state = DONE;
            break;

        case DONE:
            #ifdef ALERT_WHEN_DONE
            portsval = ~portsval;
            PORTD = portsval; //flash LED(s) and sound buzzer if attached
            PORTB = portsval;
            _delay_ms(250);
            #endif
            return;
    }

    memcpy(&last_report, ReportData, sizeof(USB_JoystickReport_Input_t));
    echoes = ECHOES;

}
