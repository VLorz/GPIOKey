/*
 * AsynchKeysObserver
 * 
 * Demonstrates the use of the GPIOKey library for Arduino using
 * asynchronous notifications.
 * 
 * Hardware required :
 *   * Teste on Arduino Uno R3, but should be valid for any Arduino board.
 * 
 * Original by Victor Lorenzo (EDesignsForge), April 26, 2015
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of GNU Lesser General Public License version 3.0,
 * as published by the Free Software Foundation.
 *
 * This demonstration code is distributed in the hope that it will 
 * be useful,but WITHOUT ANY WARRANTY; without even the implied 
 * warranty ofMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this sample code; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 * 
 * This example code is in the public domain.
 *  
 * The circuit:
 *  analog 0: pole 1 of push button #1
 *  analog 1: pole 1 of push button #2
 *  analog 2: pole 1 of push button #3
 * 
 *  The second pole of push buttons must be connected to ground.
 *  No external pull-up is required, the library uses the internal pull-up.
 *  GPIOKey presses are reported through the serial port.
*/
#include <arduino.h>
#include "GPIOKey.h"

#define PIN_KEY1    A0
#define PIN_KEY2    A1
#define PIN_KEY3    A2


/* These variables simply hold the number of times the callback has been
   called */
int Key1TouchCount;
int Key2TouchCount;
int Key3TouchCount;


/* These handlers are call whenever the corresponding key is pressed
   or released.

   Please, note these functions run in interrupt context
*/
void Key1Callback( GPIOKey* lpKey, GPIOKeyStates_t NewState )
{
  Key1TouchCount++;
}

void Key2Callback( GPIOKey* lpKey, GPIOKeyStates_t NewState )
{
  Key2TouchCount++;
}

void Key3Callback( GPIOKey* lpKey, GPIOKeyStates_t NewState )
{
  Key3TouchCount++;
}


GPIOKey Keys[] = {
  GPIOKey( PIN_KEY1 ),
  GPIOKey( PIN_KEY2 ),
  GPIOKey( PIN_KEY3 )
};


// Appplication initialization
void setup() {
  // Setup the serial port
  Serial.begin( 115200 );
  
  Key1TouchCount = 0;
  Key2TouchCount = 0;
  Key3TouchCount = 0;
  
  Keys[0].enableAsynch( Key1Callback );
  Keys[1].enableAsynch( Key2Callback );
  Keys[2].enableAsynch( Key3Callback );
}


// Main application loop
void loop() {
  
  if (Key1TouchCount > 0)
  {
    Serial.print( F("GPIOKey 1 state changed\r\n") );
    Key1TouchCount--;
  }
  
  if (Key2TouchCount > 0)
  {
    Serial.print( F("GPIOKey 2 state changed\r\n") );
    Key2TouchCount--;
  }
  
  if (Key3TouchCount > 0)
  {
    Serial.print( F("GPIOKey 3 state changed\r\n") );
    Key3TouchCount--;
  }
}

