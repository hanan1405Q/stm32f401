#include "MCAL/RCC/RCC.h"
#include "MCAL/STK/STK.h"

//#include "MCAL/GPIO/GPIO.h"

#include "MCAL/NVIC/NVIC.h"
#include "HAL/LED/LED.h"
#include "HAL/SW/SW.h"

void fun (void);

int  App (void)
{

  RCC_EnablePeripheralClock(GPIOA_ID);
  RCC_EnablePeripheralClock(GPIOB_ID);

  LED_Init();
  STK_Init();
  
   /*
        // Test GPIO and LED Driver 
   RCC_EnablePeripheralClock(GPIOB_ID);
   RCC_EnablePeripheralClock(GPIOC_ID);

   GPIO_PinConfig_t pin ={
                        .Port=GPIO_PORTC,
                        .Pin=GPIO_PIN13,
                        .Mode=GPIO_MODE_OUT_PP,
                        .Speed=GPOI_SPEED_LOW
   };
   GPIO_Init(&pin);

   GPIO_SetPinValue(GPIO_PORTC, GPIO_PIN13,GPIO_HIGH);
   */


  /*
    // Switch test
    u8 state;
    while (1)
    {
       SW_GetSwitchState(Switch1,&state);
       if(state==SW_STATE_PRESSED)
       {
          LED_SetState(GreenLed,LED_STATE_ON);
          
       }

       else if(state==SW_STATE_NOT_PRESSED)
       {
        LED_SetState(GreenLed,LED_STATE_OFF);
       }
    }
    
  */
      

/*
   // Test NVIC  Behavior:

   NVIC_EnableIRQ(EXTI0);
   NVIC_EnableIRQ(EXTI1);
   NVIC_SetGroupSubBits(GROUP_2BIT_SUB_2BIT);

   NVIC_SetPriority(EXTI0,0,0);
   NVIC_SetPriority(EXTI1,1,0);

   NVIC_SetPendingIRQ(EXTI0);
   
   
   LED_SetState(YellowLed,LED_STATE_OFF);
   
*/
   


  

      //Test SysTick

    STK_SetTimePeriodic_ms(5000, fun);

     

 
    
    while(1)
    {
        
    };

    return 0;
}


void fun (void)
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


/*
    void  EXTI0_IRQHandler (void)
  {
    NVIC_ClearPendingIRQ(EXTI0);
    NVIC_SetPendingIRQ(EXTI1);
    LED_SetState(GreenLed,LED_STATE_ON);
  }

  void  EXTI1_IRQHandler (void)
  {
    NVIC_ClearPendingIRQ(EXTI1);
    LED_SetState(RedLed,LED_STATE_ON);
  }
*/



