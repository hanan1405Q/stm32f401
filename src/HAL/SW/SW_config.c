
#include "SW.h"
#include "MCAL/GPIO/GPIO.h"

SW_SwitchConfig_t Switches[_Switch_Num]=
{
   [Switch1]={
                .Port=GPIO_PORTB,
                .Pin=GPIO_PIN0,
                .Connect=GPIO_MODE_IN_PU
             },
    [Switch2]={
                .Port=GPIO_PORTB,
                .Pin=GPIO_PIN1,
                .Connect=GPIO_MODE_IN_PU,
             },

};

