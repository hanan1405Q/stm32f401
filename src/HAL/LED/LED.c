#include "MCAL/GPIO/GPIO.h"
#include "LED.h"

extern LED_LedConfig_t Leds[_Led_Num];

void LED_Init(void)
{
   GPIO_PinConfig_t pin;
    pin.Speed= GPOI_SPEED_MED;
    pin.Mode= GPIO_MODE_OUT_PP;
    for(u8 index=0; index < _Led_Num; index ++)
    {
        pin.Port=Leds[index].Port;
        pin.Pin=Leds[index].Pin;
        GPIO_Init(&pin);
        /*using bitwise trick instead of using switch case */
        GPIO_SetPinValue(Leds[index].Port, Leds[index].Pin, (Leds[index].Connect)^(Leds[index].State));
    }
   
}

void LED_SetState(u8 led,u8  state)
{
    GPIO_SetPinValue(Leds[led].Port, Leds[led].Pin, (Leds[led].Connect)^state);
}