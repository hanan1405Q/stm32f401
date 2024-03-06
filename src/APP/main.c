#include "MCAL/RCC/RCC.h"
//#include "MCAL/GPIO/GPIO.h"
#include "MCAL/NVIC/NVIC.h"
#include "HAL/LED/LED.h"
int main (void)
{

  RCC_EnablePeripheralClock(GPIOA_ID);

  LED_Init();
  
  /*RCC_EnablePeripheralClock(GPIOB_ID);
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
   

 NVIC_EnableIRQ(EXTI0);
 NVIC_SetPendingIRQ(EXTI0);
  
  LED_SetState(AlarmLed,LED_STATE_ON);

    while(1)
    {
        
    };
    return 0;
}

void  EXTI0_IRQHandler (void)
{
   NVIC_ClearPendingIRQ(EXTI0);
   LED_SetState(GreenLed,LED_STATE_ON);
}
