#include "STD_TYPE.h"
#include "HAL/LED/LED.h"

#define Periodicity_sec  1

typedef enum
{
    Green,
    Yellow,
    Red
}enum_satate_t;


void Trafic_APP()
{

    static u8 State=Green;
    static u8 Prev_State;
    static u8 Second =0;
    Second = Second +Periodicity_sec;  
    

    switch (State)
    {
        
    case Green:
         LED_SetState(YellowLed,LED_STATE_OFF);
         LED_SetState(RedLed,LED_STATE_OFF);
         LED_SetState(GreenLed,LED_STATE_ON);
         if(Second==3)
         {
            State=Yellow;
            Prev_State=Green;
            Second=0;
         }
        break;

    case Yellow:
         LED_SetState(GreenLed,LED_STATE_OFF);
         LED_SetState(RedLed,LED_STATE_OFF);
         LED_SetState(YellowLed,LED_STATE_ON);
         
         if(Second==2)
         {
            if(Prev_State==Green)
            {
                State=Red;
                Prev_State=Yellow;
                Second=0;
            }
            
            else if (Prev_State==Red)
            {
                State=Green;
                Prev_State=Yellow;
                Second=0;
            }
         }

        break;
    
    case Red:
         LED_SetState(GreenLed,LED_STATE_OFF);
         LED_SetState(YellowLed,LED_STATE_OFF);
         LED_SetState(RedLed,LED_STATE_ON);
         if(Second==1)
         {
            State=Yellow;
            Prev_State=Red;
            Second=0;
         }
        
        
        break;

    default:
        break;
    }
}