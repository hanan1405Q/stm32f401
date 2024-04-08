
#include "MCAL/RCC/RCC.h"
#include "HAL/LED/LED.h"
#include "HAL/SW/SW.h"
#include "HAL/LCD/LCD.h"

#include "MCAL/NVIC/NVIC.h"
#include "MCAL/UART/UART.h"
#include "MCAL/GPIO/GPIO.h"
 
#include "OS/Sched.h"


int main(void)
{
  
    RCC_EnablePeripheralClock(GPIOA_ID);
    RCC_EnablePeripheralClock(GPIOB_ID);
    RCC_EnablePeripheralClock(GPIOC_ID);

     RCC_EnablePeripheralClock(USART1_ID);

    LED_Init();
    SW_Init();
    LCD_Init();
    UART_Init(UART_1);

/*Configure Tx Pin*/
GPIO_PinConfig_t pin0 ={
                        .Port=GPIO_PORTA,
                        .Pin=GPIO_PIN9,
                        .Mode=GPIO_MODE_AF_PP,
                        .Speed=GPOI_SPEED_HIGH
                        };
GPIO_Init(&pin0);

/*Configure Rx Pin*/
GPIO_PinConfig_t pin1 ={
                        .Port=GPIO_PORTA,
                        .Pin=GPIO_PIN10,
                        .Mode=GPIO_MODE_AF_PP,
                        .Speed=GPOI_SPEED_HIGH
                        };
GPIO_Init(&pin1);
GPIO_ConfAltrFun(GPIO_PORTA,GPIO_PIN9,AF7);
GPIO_ConfAltrFun(GPIO_PORTA,GPIO_PIN10,AF7);




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

