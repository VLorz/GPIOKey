#include <string.h>
#include "GPIOKey.h"




#if (CONFIG_GPIOKEY_USES_ASYNCH_CALLBACKS >= 1)
#define  DEBUG
#include "PinChangeInt.h"
#endif  /* mCONFIG_KEY_USES_ASYNCH_CALLBACKS */


GPIOKey::GPIOKey( uint8_t arduinoPin, uint8_t keyCode )
	: m_arduinoPin( arduinoPin ), m_keyCode( keyCode ), m_TimeAtPreviousPress( 0 )
{
  pinMode( arduinoPin, INPUT_PULLUP );
  digitalWrite( arduinoPin, HIGH );      // Activate pull-up;
  
  m_PreviousState = State();
}


GPIOKey::GPIOKey( uint8_t arduinoPin  )
  : GPIOKey( arduinoPin, (uint8_t)0 )
{}


#if (CONFIG_GPIOKEY_USES_ASYNCH_CALLBACKS >= 1)
void ISR_KeyPressedChangedHandler( void* tag )
{
  GPIOKey* lpKey = (GPIOKey*)tag;
  lpKey->m_TimeAtPreviousPress = millis();
  lpKey->m_callback( lpKey, lpKey->Check() );
}


GPIOKey::GPIOKey( uint8_t arduinoPin, uint8_t keyCode, GPIOKeyCallback_t callback )
	: GPIOKey( arduinoPin, keyCode )
{
	m_callback = NULL;
	enableAsynch( callback );
}


GPIOKey::GPIOKey( uint8_t arduinoPin, GPIOKeyCallback_t callback )
  : GPIOKey( arduinoPin, 0, callback )
{}


void GPIOKey::enableAsynch( GPIOKeyCallback_t callback )
{
  if (m_callback) {
    PCintPort::detachInterrupt( m_arduinoPin );
    m_callback = NULL;
  }
  
  if (callback) {
    m_callback = callback;
    PCintPort::attachInterrupt( m_arduinoPin, ISR_KeyPressedChangedHandler, CHANGE, this );
  }
}
#endif  /* mCONFIG_KEY_USES_ASYNCH_CALLBACKS */


GPIOKeyStates_t GPIOKey::State()
{
  return digitalRead( m_arduinoPin ) ? GPIOKEYRELEASED : GPIOKEYPRESSED;
}


GPIOKeyStates_t GPIOKey::Check()
{
  GPIOKeyStates_t  State = this->State();
  
  if (State == m_PreviousState)
    return GPIOKEYNOCHANGE;
  
  if (State == GPIOKEYPRESSED)
    m_TimeAtPreviousPress = millis();
  
  return (m_PreviousState = State);
}


