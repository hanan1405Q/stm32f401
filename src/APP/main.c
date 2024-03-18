
#include "MCAL/RCC/RCC.h"
#include "HAL/LED/LED.h"
#include "HAL/SW/SW.h"
#include "OS/Sched.h"


int main (void)
{
   
    RCC_EnablePeripheralClock(GPIOA_ID);
    RCC_EnablePeripheralClock(GPIOB_ID);

    LED_Init();
    SW_Init();

    Sched_Init();
    Sched_Start();
  
    
   
   return 0;

}


void fun1(void)
{
    static u8  Local_Flag=0;
    if(Local_Flag==0)
    {
        LED_SetState(GreenLed,LED_STATE_ON);
        Local_Flag=1;
    }
    else if(Local_Flag==1)
    {
        LED_SetState(GreenLed,LED_STATE_OFF);
        Local_Flag=0;
    }

}


void fun2(void)
{
    static u8  Local_Flag=0;
    if(Local_Flag==0)
    {
        LED_SetState(YellowLed,LED_STATE_ON);
        Local_Flag=1;
    }
    else if(Local_Flag==1)
    {
        LED_SetState(YellowLed,LED_STATE_OFF);
        Local_Flag=0;
    }

}


void fun3(void)
{
    static u8  Local_Flag=0;
    if(Local_Flag==0)
    {
        LED_SetState(RedLed,LED_STATE_ON);
        Local_Flag=1;
    }
    else if(Local_Flag==1)
    {
        LED_SetState(RedLed,LED_STATE_OFF);
        Local_Flag=0;
    }

}

