#include "MCAL/RCC/RCC.h"
#include "MCAL/STK/STK.h"

//#include "MCAL/GPIO/GPIO.h"

#include "MCAL/NVIC/NVIC.h"
#include "HAL/LED/LED.h"
#include "HAL/SW/SW.h"
#include "HAL/STP/STP.h"

#include "MCAL/UART/UART.h"
#include "MCAL/GPIO/GPIO.h"

void fun (void);

int  mai (void)
{

  RCC_EnablePeripheralClock(GPIOA_ID);
  RCC_EnablePeripheralClock(GPIOB_ID);
  RCC_EnablePeripheralClock(USART1_ID);

  LED_Init();
  STK_Init();
  //STP_Init();
  UART_Init(UART_1);
  
   /*
        // 01- Test GPIO and LED Driver 

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
        02- // Switch test
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
        // 03- Test NVIC  Behavior:

        NVIC_EnableIRQ(EXTI0);
        NVIC_EnableIRQ(EXTI1);
        NVIC_SetGroupSubBits(GROUP_2BIT_SUB_2BIT);

        NVIC_SetPriority(EXTI0,0,0);
        NVIC_SetPriority(EXTI1,1,0);

        NVIC_SetPendingIRQ(EXTI0);
        
        
        LED_SetState(YellowLed,LED_STATE_OFF);
        
    */
   


  
/*
      04- //Test SysTick

    STK_SetTimePeriodic_ms(5000, fun);

     
*/

/*
    05-//Test Serial To Parallel
    while(1)
    {
      for(u8 i=0;i<8;i++)
      {
          u8 x=(1<<i);
          STP_SendData(x);
          STK_SetBusyWait_ms(500);
      }
        
    };

*/


       //Test UART
        
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
        NVIC_EnableIRQ(USART1);

        /*u8 c=0;
        Uart_RxByte(UART_1,&c);
       if(c==1)
       {
         LED_SetState(0,LED_STATE_ON);
       }*/

       u8 str[20] = "Hello Hanan UART /n";
       //Uart_RxByte(UART_1,&x);
        
  while(1)
  {
       
      UART_TxBufferAsync(UART_1,str,20,NULL);  
      //STK_SetBusyWait_ms(1000);

  }
   

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



