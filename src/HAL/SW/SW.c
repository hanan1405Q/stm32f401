#include "SW.h"
#include "MCAL/GPIO/GPIO.h"

#define Sw_4BIT_OFFSET 4

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


void SW_GetSwitchState(u8 SwitchName ,u8*  state)
{
    u8 PinValue;
    GPIO_GetPinValue(Switches[SwitchName].Port,Switches[SwitchName ].Pin,&PinValue);

    *state=  (PinValue) ^ (Switches[SwitchName ].Connect >> Sw_4BIT_OFFSET);


}