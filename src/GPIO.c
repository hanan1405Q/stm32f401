#include "GPIO.h" 

#define GIO_CLEAR_MASK    0x00000003  /*Clear Mask for 2 bits*/
#define GPIO_MODE_MASK     0x00000003  /* This Mask is used to extract bits of MODER in the Mode attribute */
#define GPIO_OTYPE_MASK   0x00000010  /* This Mask is used to extract bits of  OTYPER in the Mode attribute */
#define GPIO_PUPD_MASK    0x0000000C  /* This Mask is used to extract bits of  PUPDR in the Mode attribute */

#define GPIO_2BIT_OFFSET   0x02
#define GPIO_3BIT_OFFSET   0x03
#define GPIO_16BIT_OFFSET  0x10

typedef struct
{
   volatile u32 MODER;
   volatile u32 OTYPER;
   volatile u32 OSPEEDR;
   volatile u32 PUPDR;
   volatile u32 IDR;
   volatile u32 ODR;
   volatile u32 BSRR;
   volatile u32 LCKR;
   volatile u32 AFRL;
   volatile u32 AFRH;
}GPIO_RegDef;



void GPIO_Init(GPIO_PinConfig_t * PinCfg)
{
     u32 Local_Reg=0; 
     u16 PinNum=PinCfg->Pin;
     u32 ModeValue=   (PinCfg->Mode)  & GPIO_MODE_MASK ;
     u32 OpTypeValue= ((PinCfg->Mode) & GPIO_OTYPE_MASK)>> GPIO_2BIT_OFFSET ;
     u32  PuPdValue=  ((PinCfg->Mode)  & GPIO_PUPD_MASK)>> GPIO_3BIT_OFFSET ;
     
     Local_Reg= ((GPIO_RegDef*)PinCfg->Port)->MODER;
     Local_Reg &= ~(GIO_CLEAR_MASK<<(PinNum*GPIO_2BIT_OFFSET));
     Local_Reg |= ModeValue<<(PinNum*GPIO_2BIT_OFFSET);
     ((GPIO_RegDef*)PinCfg->Port)->MODER=Local_Reg;

     Local_Reg= ((GPIO_RegDef*)PinCfg->Port)->PUPDR;
     Local_Reg &= ~(GIO_CLEAR_MASK<<(PinNum*GPIO_2BIT_OFFSET));
     Local_Reg |= PuPdValue<<(PinNum*GPIO_2BIT_OFFSET);
     ((GPIO_RegDef*)PinCfg->Port)->PUPDR=Local_Reg;

     Local_Reg= ((GPIO_RegDef*)PinCfg->Port)->OTYPER;
     Local_Reg &= ~(1<<PinNum);
     Local_Reg |= (OpTypeValue)<<(PinNum);
     ((GPIO_RegDef*)PinCfg->Port)->OTYPER=Local_Reg;
     
     Local_Reg=((GPIO_RegDef*)PinCfg->Port)->OSPEEDR;
     Local_Reg &= ~(GIO_CLEAR_MASK<<(PinNum*GPIO_2BIT_OFFSET));
     Local_Reg |= ((PinCfg->Speed)<<(PinNum*GPIO_2BIT_OFFSET));
     ((GPIO_RegDef*)PinCfg->Port)->OSPEEDR=Local_Reg;

}

void GPIO_SetPinValue(void* Port ,u32 PinNum , u32 value)
{
   switch (value)
   {
      case GPIO_HIGH: ((GPIO_RegDef*)Port)->BSRR=(1<<PinNum);                     break;
      case GPIO_LOW: ((GPIO_RegDef*)Port)->BSRR=(1<<(PinNum+GPIO_16BIT_OFFSET));  break;

   }
      
}
void GPIO_GetPinValue(void* Port ,u32 PinNum , u8* PinValue)
{
   *PinValue=(((GPIO_RegDef*)Port)->IDR >> PinNum)&1;
}