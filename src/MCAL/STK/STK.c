/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/

#include "STK.h"


/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
#define  STK              ((volatile STK_RegDef_t*)(BASEADD))
#define  BASEADD               0xE000E010
#define  FACTOR_1000           1000
#define  ENABLE_AND__INT_MASK  0xfffffffC
#define  CLK_MASK              0xfffffffB


#if (STK_CLK == AHB)
    #define STK_FRQ  FRQ_MHZ
#else
    #define STK_FRQ  (FRQ_MHZ / 8)
#endif

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

typedef struct 
{
   u32 STK_CTRL;
   u32 STK_LOAD;
   u32 STK_VAL;
   u32 STK_CALIB;
}STK_RegDef_t;



/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/

static void (* Callback)  (void);
static u8 Single_Flage;
/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

void STK_Init(void)
{
    u32 Loc_Reg= STK->STK_CTRL;
    Loc_Reg&=CLK_MASK;
    Loc_Reg |=STK_CLK;
    STK->STK_CTRL=Loc_Reg;
    
}

void STK_SetBusyWait_ms(u32 Copy_u32Time)
{
    u32 Local_Ticks= (Copy_u32Time*FACTOR_1000*STK_FRQ)-1;
    u32 Loc_Reg= STK->STK_CTRL;
    /* Set Tick Count in Load Reg*/
    STK->STK_LOAD=Local_Ticks;

    /*Enable the SYSTK*/
      Loc_Reg &= ENABLE_AND__INT_MASK;
      Loc_Reg |= 1;
      STK->STK_CTRL=Loc_Reg;

    /*POlling on Count Flag*/
    while(((STK->STK_CTRL>>16)&1)==0);


    STK->STK_LOAD=0;  //OneTime Delay
    STK->STK_VAL=0;   //Clear Count Flage



}

void STK_SetTimeSingle_ms(u32 Copy_u32Time , void (*Copy_Ptr) (void))
{

   Single_Flage=1;
   Callback=Copy_Ptr;

   /*Mape FromTime to Ticks Based on SystemClock (1M)*/
    u32 Local_Ticks= (Copy_u32Time*FACTOR_1000*STK_FRQ)-1;;

    /* Set Tick Count in Load Reg*/
    STK->STK_LOAD=Local_Ticks;

    /*Enable the SYSTK   And Intrupt Flag*/
      STK->STK_CTRL |= 3;
}



void STK_SetTimePeriodic_ms(u32 Copy_u32Time ,void (*Copy_Ptr) (void))
{
   Single_Flage=0;
   Callback=Copy_Ptr;

   /*Mabe FromTime to Ticks Based on SystemClock (1M)*/
   u32 Local_Ticks=(Copy_u32Time*FACTOR_1000*STK_FRQ)-1;;

    /* Set Tick Count in Load Reg*/
    STK->STK_LOAD=Local_Ticks;

    /*Enable the SYSTK   And Intrupt Flag*/
      STK->STK_CTRL |= 3;
}


void STK_GetRemainTime_ms(u32*  Copy_u32Time)
{
   *Copy_u32Time = (STK->STK_VAL * STK_FRQ *1000);
}


void STK_Stop(void)
{
    /*DisAble STK*/

    STK->STK_CTRL =0;
}


void  SysTick_Handler (void)
{
    if(Single_Flage==1)
    {
         STK->STK_LOAD=0;  //OneTime Delay
         STK->STK_VAL=0;   //Clear Count Flage
         Callback();

    }
    else
    {
        Callback();

    }
}