#include "MCAL/GPIO/GPIO.h"
#include "STP.h"

STP_Pins_t  STP_Pins [_MaxNum]=
{
    [Serial_Data]={
                    .Port=GPIO_PORTA,
                    .Pin=GPIO_PIN0,
                  },

    [Shift_Clk]= {
                    .Port=GPIO_PORTA,
                    .Pin=GPIO_PIN1,
                  },

    [Store_Clk]={
                   .Port=GPIO_PORTA,
                   .Pin=GPIO_PIN2,
                  },
};