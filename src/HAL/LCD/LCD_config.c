
#include "MCAL/GPIO/GPIO.h"
#include "LCD.h"

LCD_strPinConfig_t LCD_PinCfg [_NUM_OF_PINS]=
{
	[D0_PIN]={
				.Port=GPIO_PORTA,
				.Pin=GPIO_PIN0,
	         },
			 
	[D1_PIN]={
				.Port=GPIO_PORTA,
				.Pin=GPIO_PIN1,
			 },
			 
	[D2_PIN]={
				.Port=GPIO_PORTA,
				.Pin=GPIO_PIN2,

			 },
			 
			 
	[D3_PIN]={
				.Port=GPIO_PORTA,
				.Pin=GPIO_PIN3,
			
			 },
	
	[D4_PIN]={
				.Port=GPIO_PORTA,
				.Pin=GPIO_PIN4,
				
			},
	
	[D5_PIN]={
				.Port=GPIO_PORTA,
				.Pin=GPIO_PIN5,
				
			},
			
	[D6_PIN]={
				.Port=GPIO_PORTA,
				.Pin=GPIO_PIN6,
			},

	[D7_PIN]={
				.Port=GPIO_PORTA,
				.Pin=GPIO_PIN7,
			},

	[RS_PIN]={
				.Port=GPIO_PORTB,
				.Pin=GPIO_PIN0,
				
			},
			
	[RW_PIN]={
				.Port=GPIO_PORTB,
				.Pin=GPIO_PIN1,
			},
			
	[E_PIN]={
				.Port=GPIO_PORTB,
				.Pin=GPIO_PIN2,
			
			},
};
