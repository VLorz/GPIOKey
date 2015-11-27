/*
 * GPIOKey.h - Library for implementing key/switch input on the Arduino
 * Created by Victor Lorenzo (EDesignsForge), September 10, 2014.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of GNU Lesser General Public License version 3.0,
 * as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 
 * This library makes use of the following libraries which are copied here
 * for convenience:
 *  > PinChangeInt library for the Arduino
 *    https://github.com/GreyGnome/PinChangeInt
 *    Many thanks to Mike Schwager (GreySGnome).
 *
*/
#ifndef  _GPIOKey_H_
#define  _GPIOKey_H_


#include <inttypes.h>
#include <Arduino.h>

#include "Configuration/GPIOKeyConfig.h"


#if !(defined(__stringify))
#define  __stringify_1(x...)     #x
#define  __stringify(x...)       __stringify_1(x)
#endif

// Library version codes
#define  GPIOKEY_VERSION          __stringify(GPIOKEY_VERSION_MAJOR) "." __stringify(GPIOKEY_VERSION_MINOR)
#define  GPIOKEY_VERSION_MAJOR	1
#define  GPIOKEY_VERSION_MINOR	0


typedef enum {
  GPIOKEYNOCHANGE,
  GPIOKEYPRESSED,
  GPIOKEYRELEASED,
} GPIOKeyStates_t;



#if (CONFIG_GPIOKEY_USES_ASYNCH_CALLBACKS >= 1)
void ISR_KeyPressedChangedHandler( void* tag );
class GPIOKey;
typedef void (*GPIOKeyCallback_t)( GPIOKey* lpKey, GPIOKeyStates_t NewState );
#endif  /* mCONFIG_KEY_USES_ASYNCH_CALLBACKS */


class GPIOKey
{
  public:
    GPIOKey( uint8_t arduinoPin );
#if (CONFIG_GPIOKEY_USES_ASYNCH_CALLBACKS >= 1)
    GPIOKey( uint8_t arduinoPin, GPIOKeyCallback_t callback );
    void enableAsynch( GPIOKeyCallback_t callback );
#endif  /* mCONFIG_KEY_USES_ASYNCH_CALLBACKS */

    GPIOKeyStates_t Check();
    GPIOKeyStates_t State();
    bool pressed() { return ( State() == GPIOKEYPRESSED ); };

  private:
    uint8_t m_Input;
    GPIOKeyStates_t  m_PreviousState;
#if (CONFIG_GPIOKEY_USES_ASYNCH_CALLBACKS >= 1)
    GPIOKeyCallback_t m_callback;
    friend void ISR_KeyPressedChangedHandler( void* tag );
#endif  /* CONFIG_GPIOKEY_USES_ASYNCH_CALLBACKS */
};



#endif  /* _GPIOKey_H_ */

