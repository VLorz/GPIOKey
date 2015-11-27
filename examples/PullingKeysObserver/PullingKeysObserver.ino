/*
 * KeysObserver
 * 
 * Demonstrates the use of the GPIOKey library for Arduino.
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


GPIOKey Keys[] = {
  GPIOKey( PIN_KEY1 ),
  GPIOKey( PIN_KEY2 ),
  GPIOKey( PIN_KEY3 )
};


// Appplication initialization
void setup() {
  // Setup the serial port
  Serial.begin( 115200 );
}


// Main application loop
void loop() {
  int  Index;
  
  for (Index = 0; Index < sizeof(Keys) / sizeof(Keys[0]); Index++) {
    switch (Keys[Index].Check()) {
      case GPIOKEYPRESSED :
      {
        Serial.print( F("GPIOKey #") );
        Serial.print( Index + 1 );
        Serial.print( F(" Pressed\r\n") );
        break;
      }
      
      case GPIOKEYRELEASED:
      {
        Serial.print( F("GPIOKey #") );
        Serial.print( Index + 1 );
        Serial.print( F(" Released\r\n") );
        break;
      }
    }
  }
}

