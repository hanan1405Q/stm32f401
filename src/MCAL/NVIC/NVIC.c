/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/

#include "NVIC.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
#define  NVIC_BASE_ADD  0xE000E100 

/*  Interrupt set-enable registers */
#define  NVIC_ISER  ((volatile u32*) (NVIC_BASE_ADD))

/*  Interrupt clear-enable registers */
#define  NVIC_ICER  ((volatile u32*) (NVIC_BASE_ADD+0x80))


/*  Interrupt set-pending registers */
#define  NVIC_ISPR  ((volatile u32*) (NVIC_BASE_ADD+0x100))

/*  Interrupt clear-pending registers */
#define  NVIC_ICPR  ((volatile u32*) (NVIC_BASE_ADD+0x180))


/*  Interrupt Active-Bit registers */
#define  NVIC_IABR   ((volatile u32*) (NVIC_BASE_ADD+0x200))


/*  Interrupt priority registers */
#define NVIC_IPR      ((volatile u8*) (NVIC_BASE_ADD+0x300))

/*Software trigger interrupt register*/
#define NVIC_STIR    *((volatile u32*) (NVIC_BASE_ADD+0xE00))

  
#define OFFSET_4BIT  4

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/

static u32  GroupSubBits ;

/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

NVIC_enuErrorState_t NVIC_EnableIRQ(NVIC_IRQ_ID_t  Copy_u8IRQ_Index)
{

   u8 Reg_Num;
  u8 Bit_Num;
   NVIC_enuErrorState_t  Ret_ErrorState=NVIC_NOT_OK; 

   if(Copy_u8IRQ_Index<85)
   {
     Ret_ErrorState=NVIC_OK;
     Reg_Num=Copy_u8IRQ_Index/32;
     Bit_Num=Copy_u8IRQ_Index%32;
     NVIC_ISER[Reg_Num]|= (1<<Bit_Num);   
   }
   else
   {
     Ret_ErrorState=NVIC_IRQID_Not_Valid;
   }

   return Ret_ErrorState;
};

NVIC_enuErrorState_t NVIC_DisableIRQ(NVIC_IRQ_ID_t  Copy_u8IRQ_Index)
{

   NVIC_enuErrorState_t  Ret_ErrorState=NVIC_NOT_OK; 
   u8 Reg_Num;
   u8 Bit_Num;
   
   if(Copy_u8IRQ_Index<85)
   {
      Ret_ErrorState=NVIC_OK;
      Reg_Num=Copy_u8IRQ_Index/32;
      Bit_Num=Copy_u8IRQ_Index%32;
      NVIC_ICER[Reg_Num]|= (1<<Bit_Num) ;
   }
   else
   {
     Ret_ErrorState=NVIC_IRQID_Not_Valid;
   }

   return Ret_ErrorState;
};

NVIC_enuErrorState_t NVIC_SetPendingIRQ(NVIC_IRQ_ID_t  Copy_u8IRQ_Index)
{
   NVIC_enuErrorState_t  Ret_ErrorState=NVIC_NOT_OK; 
   u8 Reg_Num;
   u8 Bit_Num;

   if(Copy_u8IRQ_Index<85)
   {
     Ret_ErrorState=NVIC_OK;
     Reg_Num=Copy_u8IRQ_Index/32;
     Bit_Num=Copy_u8IRQ_Index%32;
     NVIC_ISPR[Reg_Num]|=(1<<Bit_Num);   
   }
   else
   {
     Ret_ErrorState=NVIC_IRQID_Not_Valid;
   }
   return Ret_ErrorState;
};


NVIC_enuErrorState_t NVIC_ClearPendingIRQ(NVIC_IRQ_ID_t  Copy_u8IRQ_Index)

{
   NVIC_enuErrorState_t  Ret_ErrorState=NVIC_NOT_OK; 
   u8 Reg_Num;
   u8 Bit_Num;
   if(Copy_u8IRQ_Index<85)
   {
     Ret_ErrorState=NVIC_OK;
     Reg_Num=Copy_u8IRQ_Index/32;
     Bit_Num=Copy_u8IRQ_Index%32;
     NVIC_ICPR[Reg_Num]|= (1<<Bit_Num);   
   }
   else
   {
     Ret_ErrorState=NVIC_IRQID_Not_Valid;
   }

   return Ret_ErrorState;
};

NVIC_enuErrorState_t NVIC_GetActiveState(NVIC_IRQ_ID_t  Copy_u8IRQ_Index , u8* Copy_u8State)
{
   NVIC_enuErrorState_t  Ret_ErrorState=NVIC_NOT_OK;
   u32 LocReg; 
   u8 Reg_Num;
   u8 Bit_Num;
   if(Copy_u8IRQ_Index<85)
   {
     Ret_ErrorState=NVIC_OK;
     Reg_Num=Copy_u8IRQ_Index/32;
     Bit_Num=Copy_u8IRQ_Index%32;
     LocReg=NVIC_IABR[Reg_Num];
     *Copy_u8State = (LocReg>>Bit_Num) & 1 ;   
   }
   else
   {
     Ret_ErrorState=NVIC_IRQID_Not_Valid;
   }

   return Ret_ErrorState;
};

void NVIC_SetGroupingPriority(u32 Copy_u32GroupSubBits)
{
    #define SCB_AIRCR   *((volatile u32*)(0xE000ED00C))

    GroupSubBits= Copy_u32GroupSubBits;
    SCB_AIRCR=Copy_u32GroupSubBits;
};

NVIC_enuErrorState_t NVIC_SetPriority(NVIC_IRQ_ID_t  Copy_u8IRQ_Index , u8 Copy_u8GroupPriority ,u8 Copy_u8SubPriority)
{
    NVIC_enuErrorState_t  Ret_ErrorState=NVIC_NOT_OK; 
    u8 Local_Priority;

   if(Copy_u8IRQ_Index<85)
   {
     Ret_ErrorState=NVIC_OK;
     
     Local_Priority= Copy_u8SubPriority|(Copy_u8GroupPriority <<((GroupSubBits-0xFA050300)/256));
     NVIC_IPR[Copy_u8IRQ_Index]= OFFSET_4BIT << Local_Priority;   
   }
   else
   {
     Ret_ErrorState=NVIC_IRQID_Not_Valid;
   }

   return Ret_ErrorState;
};
