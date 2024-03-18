
#include "STD_TYPE.h"
#include "HAL/SW/SW.h"
#include "HAL/LED/LED.h"

void Switch_APP(void)
{
  u8 state;  
  SW_GetSwitchState( Switch1,&state);
  
    if(state==SW_STATE_PRESSED)
    {
        LED_SetState(GreenLed,LED_STATE_ON);
    }
    
   
}