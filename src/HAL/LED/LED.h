#ifndef _LED_H 
#define _LED_H 

#include "STD_TYPE.h"
#include "LED_config.h"

#define  LED_STATE_ON   1
#define  LED_STATE_OFF  0
#define  LED_CONNECT_FR 0
#define  LED_CONNECT_RV 1



typedef struct
{
    void * Port;
    u32    Pin;
    u8     Connect;
    u8     State;

}LED_LedConfig_t;





void LED_Init(void);
void LED_SetState(u8 led,u8 Led_state);

#endif