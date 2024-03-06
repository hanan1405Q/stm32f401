#include "MCAL/GPIO/GPIO.h"
#include "LED.h"


LED_LedConfig_t Leds [_Led_Num]=
{
   [AlarmLed]={

        .Port=GPIO_PORTA,
        .Pin=GPIO_PIN0,
        .Connect=LED_CONNECT_FR,
        .State=LED_STATE_OFF

      },

   [GreenLed]={

        .Port=GPIO_PORTA,
        .Pin=GPIO_PIN1,
        .Connect=LED_CONNECT_FR,
        .State=LED_STATE_OFF

      }


};