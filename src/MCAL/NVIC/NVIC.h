#ifndef MCAL_NVIC_NVIC_H_
#define MCAL_NVIC_NVIC_H_


/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/

#include "NVIC_STM32401.h"
#include "STD_TYPE.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define GROUP_4BIT_SUB_0BIT   0xFA050300   //4 Bits f0r Group - 0 Bit For SubGroup
#define GROUP_3BIT_SUB_1BIT   0xFA050400
#define GROUP_2BIT_SUB_2BIT   0xFA050500
#define GROUP_1BIT_SUB_3BIT   0xFA050600
#define GROUP_0BIT_SUB_4BIT   0xFA050700


/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

typedef enum
{
   NVIC_OK,
   NVIC_NOT_OK,
   NVIC_IRQID_Not_Valid
}NVIC_enuErrorState_t;


/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

NVIC_enuErrorState_t NVIC_EnableIRQ(NVIC_IRQ_ID_t  Copy_u8IRQ_Index);
NVIC_enuErrorState_t NVIC_DisableIRQ(NVIC_IRQ_ID_t  Copy_u8IRQ_Index);

NVIC_enuErrorState_t NVIC_SetPendingIRQ(NVIC_IRQ_ID_t  Copy_u8IRQ_Index);
NVIC_enuErrorState_t NVIC_ClearPendingIRQ(NVIC_IRQ_ID_t  Copy_u8IRQ_Index);

NVIC_enuErrorState_t NVIC_GetActiveState(NVIC_IRQ_ID_t  Copy_u8IRQ_Index , u8* Copy_u8State);

void NVIC_SelectGroupingPriority (u32 Copy_u32GroupSubBits);
NVIC_enuErrorState_t NVIC_SetPriority(NVIC_IRQ_ID_t  Copy_u8IRQ_Index , u8 Copy_u8GroupPriority ,u8 Copy_u8SubPriority);

NVIC_enuErrorState_t NVIC_SetSoftwareINT(NVIC_IRQ_ID_t  Copy_u8IRQ_Index );





#endif // MCAL_NVIC_NVIC_H_
