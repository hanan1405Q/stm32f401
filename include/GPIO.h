#include "STD_TYPE.h"

/****  GPIO  PORT Macros  *****/
#define GPIO_PORTA  (void *) 0x40020000
#define GPIO_PORTB  (void *) 0x40020400
#define GPIO_PORTC  (void *) 0x40020800
#define GPIO_PORTD  (void *) 0x40020C00
#define GPIO_PORTE  (void *) 0x40021000
#define GPIO_PORTH  (void *) 0x40021C00

/***   GPIO  PIN Macros   ***/
#define GPIO_PIN0    0x00
#define GPIO_PIN1    0x01
#define GPIO_PIN2    0x02
#define GPIO_PIN3    0x03
#define GPIO_PIN4    0x04
#define GPIO_PIN5    0x05
#define GPIO_PIN6    0x06
#define GPIO_PIN7    0x07

#define GPIO_PIN8    0x08
#define GPIO_PIN9    0x09
#define GPIO_PIN10   0x0A
#define GPIO_PIN11   0x0B
#define GPIO_PIN12   0x0C
#define GPIO_PIN13   0x0D
#define GPIO_PIN14   0x0E
#define GPIO_PIN15   0x0F

/***  GPIO SPEED  Macros  ****/
#define GPOI_SPEED_LOW        0x00
#define GPOI_SPEED_MED        0x01
#define GPOI_SPEED_HIGH       0x02
#define GPOI_SPEED_VHIGH      0x03

/***  GPIO Mode Macros  ****/
#define GPIO_MODE_IN_FL        0x00
#define GPIO_MODE_IN_PU        0x08
#define GPIO_MODE_IN_PD        0x10

#define GPIO_MODE_IN_ANALOG    0x03

#define GPIO_MODE_OUT_PP       0x01
#define GPIO_MODE_OUT_PP_PU    0x09
#define GPIO_MODE_OUT_PP_PD    0x11
#define GPIO_MODE_OUT_OD       0x05
#define GPIO_MODE_OUT_OD_PU    0x0D
#define GPIO_MODE_OUT_OD_PD    0x15

#define GPIO_MODE_AF_PP        0x02
#define GPIO_MODE_AF_PP_PU     0x0A
#define GPIO_MODE_AF_PP_PD     0x12
#define GPIO_MODE_AF_OD        0x06
#define GPIO_MODE_AF_OD_PU     0x0E
#define GPIO_MODE_AF_OD_PD     0x16


/***   GPIO State  Macro ***/
#define GPIO_LOW       0x00
#define GPIO_HIGH      0x01


typedef struct 
{
   void* Port;
   u32   Pin;
   u32   Mode;
   u32   Speed;

}GPIO_PinConfig_t;






void GPIO_Init(GPIO_PinConfig_t * PinCfg);
void GPIO_SetPinValue(void* port ,u32 pin , u32 value);
void GPIO_GetPinValue(void* port ,u32 pin , u8* value);
