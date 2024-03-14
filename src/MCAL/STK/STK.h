#ifndef MCAL_STK_STK_H_
#define MCAL_STK_STK_H_

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "STD_TYPE.h" 
#include "STK_cfg.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
typedef enum{
      STK_NOK,
      STK_OK,
      STK_NotValidTicks
}STK_ErrorStatus_t;


/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

/* Select the source Clock of SYSTick*/
void STK_Init(void);

void STK_SetBusyWait_ms(u32 Copy_u32Time);

void STK_SetTimeSingle_ms(u32 Copy_u32Time , void (*Copy_Ptr) (void));

void STK_SetTimePeriodic_ms(u32 Copy_u32Time ,void (*Copy_Ptr) (void));

void STK_GetRemainTime_ms(u32*  Copy_u32Time);

void STK_Stop(void);




#endif // MCAL_STK_STK_H_