#ifndef HAL_SW_SW_H_
#define HAL_SW_SW_H_

#include "STD_TYPE.h"
#include "SW_config.h"

#define SW_STATE_PRESSED      0
#define SW_STATE_NOT_PRESSED  1
   

typedef struct
{
    void* Port;
    u32    Pin;
    u32    Connect; 

}SW_SwitchConfig_t;


void SW_Init(void);
void SW_GetSwitchState(u8 SwitchName ,u8* state);

#endif // HAL_SW_SW_H_