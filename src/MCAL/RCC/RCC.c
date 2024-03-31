
/*****************************      Includes      ********************************/
#include "RCC.h"

/********   Private   Register OF RCC  ************/

#define  RCC_BASE_ADD   0x40023800
#define  RCC_CR         *( volatile u32*)  (RCC_BASE_ADD)   // 1
#define  RCC_PLLCFGR    *((volatile u32*)   (RCC_BASE_ADD + 0x04 ))  // 2
#define  RCC_CFGR       *((volatile u32*)   (RCC_BASE_ADD+ 0x08 ))   // 3
#define  RCC_CIR        *((volatile u32*)   (RCC_BASE_ADD+ 0x0C ))  //4
#define  RCC_AHB1RSTR   *((volatile u32*)   (RCC_BASE_ADD+ 0x10 ))  //5
#define	 RCC_AHB2RSTR	*((volatile u32*)   (RCC_BASE_ADD+ 0x14))   // 6
#define	 RCC_APB1RSTR	*((volatile u32*) 	(RCC_BASE_ADD+ 0x20))	 // 7
#define	 RCC_APB2RSTR	*((volatile u32*) 	(RCC_BASE_ADD+ 0x24))	// 8
#define	 RCC_AHB1ENR	*((volatile u32*) 	(RCC_BASE_ADD+ 0x30))	// 9
#define	 RCC_AHB2ENR	*((volatile u32*) 	(RCC_BASE_ADD+ 0x34))	// 10
#define	 RCC_APB1ENR	*((volatile u32*) 	(RCC_BASE_ADD+ 0x40))	// 11
#define	 RCC_APB2ENR	*((volatile u32*) 	(RCC_BASE_ADD+ 0x44))	// 12
#define	 RCC_AHB1LPENR	*((volatile u32*) 	(RCC_BASE_ADD+ 0x50))	// 13
#define	 RCC_AHB2LPENR	*((volatile u32*) 	(RCC_BASE_ADD+ 0x54))	// 14
#define	 RCC_APB1LPENR	*((volatile u32*) 	(RCC_BASE_ADD+ 0x60))	// 15
#define	 RCC_APB2LPENR	*((volatile u32*) 	(RCC_BASE_ADD+ 0x64))	// 16
#define	 RCC_BDCR	    *((volatile u32*) 	(RCC_BASE_ADD+ 0x70))	// 17
#define	 RCC_CSR	    *((volatile u32*) 	(RCC_BASE_ADD+ 0x74))	// 18
#define	 REG_RCC_SSCG	*((volatile u32*)   (RCC_BASE_ADD+ 0x80))	// 19
#define	 REG_RCC_PLLI2SCFGR	*((volatile u32*)  (RCC_BASE_ADD+ 0x84)) // 20
#define	 REG_RCC_DCKCFGR	*((volatile u32*)  (RCC_BASE_ADD+ 0x8C))// 21


/*   01-Select Clock Masking   */

#define   RCC_SLK_HSI        0x00000000
#define   RCC_SLK_HSE        0x00000001
#define   RCC_SLK_PLL        0x00000010
#define   RCC_SLK_CLEAR      0xFFFFFFFC

/******* Bus ID **********/
#define RCC_BUS_ID_AHB1  0
#define RCC_BUS_ID_AHB2  1
#define RCC_BUS_ID_APB1  2
#define RCC_BUS_ID_APB2  3
#define RCC_BUS_GLAGE_CLEAR  0xfCffffff
#define RCC_24BIT_OFFSET    24

/**     PLL Configuration Masks       **/
#define RCC_PLLM_CLEAR       0xffffffc0
#define RCC_PLLN_CLEAR       0xffff003f
#define RCC_PLLP_CLEAR       0xfff0ffff
#define RCC_PLLQ_CLEAR       0xf0ffffff






/*   Implementation  */
void RCC_EnableSystemClock(u32 copy_u32SysClock)
{
	RCC_CR |= copy_u32SysClock;
}

void RCC_DisableSystemClock(u32 Copy_u32SysClock)
{
	RCC_CR &= ~(Copy_u32SysClock);
}


RCC_enuErrorState_t RCC_SelectClockSystem(u32 Copy_u32SysClock)
{
	u8 ready_state;
	u32 Local_Reg=RCC_CFGR;
	RCC_enuErrorState_t  Ret_ErrorState=RCC_NOK;
	
	/*Reading the ready bit -> through and the mask with the reg */
	ready_state = RCC_CR &  (Copy_u32SysClock<<1);

	if(ready_state)
	{
	  Ret_ErrorState=RCC_OK;

	  /*Clear First 2 bits  to be ready for configuration*/
	   Local_Reg &= RCC_SLK_CLEAR ;
	   switch( Copy_u32SysClock )
		  {
			case RCC_SYSCLK_HSI 	   :Local_Reg|=RCC_SLK_HSI;   break;
			case RCC_SYSCLK_HSE_CRYSTAL:
			case RCC_SYSCLK_HSE_RC     :Local_Reg |= RCC_SLK_HSE;  break;
			case  RCC_SYSCLK_PLL 	   :Local_Reg|=RCC_SLK_PLL;   break;
		  }

	   RCC_CFGR=Local_Reg;
	}
	
	else 
	{
		Ret_ErrorState=RCC_ClockNotReady;
	}
	
	return Ret_ErrorState;
}

RCC_enuErrorState_t RCC_PLLConfig(u32 Copy_u32PLLM,u32 Copy_u32PLLN,u32 Copy_u32PLLP,u32  Copy_u32ClkSourc)
{
   u32 Local_Reg=RCC_PLLCFGR;
   u8 PLL_OnState;
   RCC_enuErrorState_t Ret_ErrorState=RCC_NOK;
   PLL_OnState= RCC_CR & (RCC_SYSCLK_PLL);

   if(PLL_OnState)
   {
	   Ret_ErrorState=RCC_ConfigNotValid;
   }

   else
   {
	   Ret_ErrorState=RCC_OK;

	   /*Set Clock Source Of PLL*/
	  switch (Copy_u32ClkSourc)
	  {
	      case RCC_PLLSOURCE_HSI: Local_Reg &= RCC_PLLSOURCE_HSI;    break;
	      case RCC_PLLSOURCE_HSE: Local_Reg |= RCC_PLLSOURCE_HSE;    break;
	  }

	  Local_Reg &= RCC_PLLM_CLEAR;
	  Local_Reg |= Copy_u32PLLM;

	  Local_Reg &= RCC_PLLN_CLEAR;
	  Local_Reg |= (Copy_u32PLLN)<<6;

	  Local_Reg &= RCC_PLLP_CLEAR;
	  Local_Reg |= (Copy_u32PLLP)<<16;

   }


    RCC_PLLCFGR=Local_Reg;

    return Ret_ErrorState;
	
}




void RCC_EnablePeripheralClock(u32 Copy_u32PerId)
{
	u8 LocFlage = (Copy_u32PerId & ~(RCC_BUS_GLAGE_CLEAR))>>RCC_24BIT_OFFSET;
	
		
		switch (LocFlage)
		{
			case RCC_BUS_ID_AHB1  : RCC_AHB1ENR|=(Copy_u32PerId & RCC_BUS_GLAGE_CLEAR)  ;   break;
			case RCC_BUS_ID_AHB2  : RCC_AHB2ENR|=(Copy_u32PerId & RCC_BUS_GLAGE_CLEAR)  ;   break;
			case RCC_BUS_ID_APB1  : RCC_APB1ENR|=(Copy_u32PerId & RCC_BUS_GLAGE_CLEAR)  ;   break;
			case RCC_BUS_ID_APB2  : RCC_APB2ENR|=(Copy_u32PerId & RCC_BUS_GLAGE_CLEAR)  ;   break;
		}
}

void RCC_DisablePeripheralClock(u32 Copy_u32PerId)
{
		u8 LocFlage = (Copy_u32PerId && ~(RCC_BUS_GLAGE_CLEAR))>>RCC_24BIT_OFFSET;
		switch (LocFlage)
		{
			case RCC_BUS_ID_AHB1  : RCC_AHB1ENR &= ~(Copy_u32PerId & RCC_BUS_GLAGE_CLEAR);   break;
			case RCC_BUS_ID_AHB2  : RCC_AHB2ENR &= ~(Copy_u32PerId & RCC_BUS_GLAGE_CLEAR);   break;
			case RCC_BUS_ID_APB1  : RCC_APB1ENR &= ~(Copy_u32PerId & RCC_BUS_GLAGE_CLEAR);   break;
			case RCC_BUS_ID_APB2  : RCC_APB2ENR &= ~(Copy_u32PerId & RCC_BUS_GLAGE_CLEAR);   break;
		}
}
