
#include "STD_TYPE.h"
#include "HAL/SW/SW.h"
#include "HAL/LED/LED.h"
#include "MCAL/NVIC/NVIC.h"
#include "MCAL/UART/UART.h"


void Switch_APP(void)
{
  u8 state1; 
  u8 state2; 
  u8 str[12] = "S1_Done";
  NVIC_EnableIRQ(USART1);
  SW_GetSwitchState( Switch1,&state1);
  SW_GetSwitchState( Switch2,&state2);
  
  //state1=0;

  if(state1==SW_STATE_PRESSED)
  {
      LED_SetState(GreenLed,LED_STATE_ON);
      UART_TxBufferAsync(UART_1,str, 12,NULL);
  }
  else
  {
    LED_SetState(GreenLed,LED_STATE_OFF);
  }

  
  if(state2==SW_STATE_PRESSED)
  {
      LED_SetState(YellowLed,LED_STATE_ON);    
  }
  else
  {
    LED_SetState(YellowLed,LED_STATE_OFF);
  }

    
    
   
}