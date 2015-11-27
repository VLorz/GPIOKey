#include <string.h>
#include "GPIOKey.h"




#if (CONFIG_GPIOKEY_USES_ASYNCH_CALLBACKS >= 1)
#define  DEBUG
#include "PinChangeInt.h"
#endif  /* mCONFIG_KEY_USES_ASYNCH_CALLBACKS */


GPIOKey::GPIOKey( uint8_t Input  )
  : m_Input( Input ), m_callback( NULL )
{
  pinMode( Input, INPUT );
  digitalWrite( Input, HIGH );      // Activate pull-up;
  
  m_PreviousState = State();
}


void ISR_KeyPressedChangedHandler( void* tag )
{
  GPIOKey* lpKey = (GPIOKey*)tag;
  //, GPIOKeyStates_t NewState
  lpKey->m_callback( lpKey, GPIOKEYNOCHANGE );
}


GPIOKey::GPIOKey( uint8_t Input, GPIOKeyCallback_t callback )
  : m_Input( Input ), m_callback( callback )
{
  pinMode( Input, INPUT );
  digitalWrite( Input, HIGH );      // Activate pull-up;
  
  m_PreviousState = State();
  
  if (callback) {
    PCintPort::attachInterrupt( Input, ISR_KeyPressedChangedHandler, CHANGE, this );
  }
}


void GPIOKey::enableAsynch( GPIOKeyCallback_t callback )
{
  if (m_callback) {
    PCintPort::detachInterrupt( m_Input );
    m_callback = NULL;
  }
  
  if (callback) {
    m_callback = callback;
    PCintPort::attachInterrupt( m_Input, ISR_KeyPressedChangedHandler, CHANGE, this );
  }
}


GPIOKeyStates_t GPIOKey::State()
{
  return digitalRead( m_Input ) ? GPIOKEYRELEASED : GPIOKEYPRESSED;
}


GPIOKeyStates_t GPIOKey::Check()
{
  GPIOKeyStates_t  State = this->State();
  
  if (State == m_PreviousState)
    return GPIOKEYNOCHANGE;
    
  return (m_PreviousState = State);
}


