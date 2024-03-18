#include "SW.h"
#include "MCAL/GPIO/GPIO.h"

#define Sw_4BIT_OFFSET 4

static  u8 Sw_State=1 ;
static  u8 G_SwitchName;

extern SW_SwitchConfig_t Switches[_Switch_Num];

void SW_Init(void)
{

    GPIO_PinConfig_t pin;

     pin.Speed=GPOI_SPEED_MED;
     for (u8 index=0 ;index < _Switch_Num ; index++)
     {
        pin.Port=Switches[index].Port;
        pin.Pin=Switches[index].Pin;
        pin.Mode=Switches[index].Connect;
        GPIO_Init(&pin);
     }


}

/*it gonna be runneble which run each 5 ms*/
 void SW_GetState(void)
{
   static u8 Counter=0;
   u8 cur_state=0;
   u8 prev_state=0;

   u8 PinValue;
   u8 SwitchName=G_SwitchName;
   
    GPIO_GetPinValue(Switches[SwitchName].Port,Switches[SwitchName ].Pin,&PinValue);
    cur_state=  (PinValue) ^ (Switches[SwitchName ].Connect >> Sw_4BIT_OFFSET);
    if(cur_state==prev_state)
    {
        Counter++;
    }

    if(Counter==5)
    {
        Sw_State=cur_state;
        Counter=0  ;
    }
    prev_state=cur_state;

}


void SW_GetSwitchState(u8 SwitchName ,u8*  state)
{
  
   G_SwitchName=SwitchName ;
   *state=Sw_State;

}

/*
void SW_GetSwitchState(u8 SwitchName ,u8*  state)
{
     u8 PinValue;
     GPIO_GetPinValue(Switches[SwitchName].Port,Switches[SwitchName ].Pin,&PinValue);
     *state=  (PinValue) ^ (Switches[SwitchName ].Connect >> Sw_4BIT_OFFSET);
}
*/