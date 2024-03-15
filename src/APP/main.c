
#include "MCAL/RCC/RCC.h"
#include "HAL/LED/LED.h"
#include "OS/Sched.h"

int main (void)
{
   
    RCC_EnablePeripheralClock(GPIOA_ID);

    LED_Init();
    Sched_Init();
    Sched_Start();
    LED_Init();
    while(1)
    {

    };
 

}


void fun1(void)
{
    static u8  Local_Flag=0;
    if(Local_Flag==0)
    {
        LED_SetState(Led1,LED_STATE_ON);
        Local_Flag=1;
    }
    else if(Local_Flag==1)
    {
        LED_SetState(Led1,LED_STATE_OFF);
        Local_Flag=0;
    }

}


void fun2(void)
{
    static u8  Local_Flag=0;
    if(Local_Flag==0)
    {
        LED_SetState(Led2,LED_STATE_ON);
        Local_Flag=1;
    }
    else if(Local_Flag==1)
    {
        LED_SetState(Led2,LED_STATE_OFF);
        Local_Flag=0;
    }

}


void fun3(void)
{
    static u8  Local_Flag=0;
    if(Local_Flag==0)
    {
        LED_SetState(Led3,LED_STATE_ON);
        Local_Flag=1;
    }
    else if(Local_Flag==1)
    {
        LED_SetState(Led3,LED_STATE_OFF);
        Local_Flag=0;
    }

}

