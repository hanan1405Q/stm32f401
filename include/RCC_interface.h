
#ifndef _RCC_INTERFACE_H 
#define _RCC_INTERFACE_H 

#include "STD_TYPE.h"

/* PLL Mode */
#define  PLL  	 0
#define  PLLI2S  1


/* Bus Id */
#define RCC_BUS_ID_AHB1  0
#define RCC_BUS_ID_AHB2  1
#define RCC_BUS_ID_APB1  2
#define RCC_BUS_ID_APB2  3

/*******			Peripheral ID				********/

/*01- Peripheral on AHB1_Bus*/
#define GPIOA_ID   0x1
#define GPIOB_ID   0x2
#define GPIOC_ID   0x4
#define GPIOD_ID   0x8
#define GPIOE_ID   0x10
#define GPIOH_ID   0x80
#define CRC_ID     0x1000
#define DMA1_ID    0x200000
#define DMA2_ID    0x400000

/*02- Peripheral on AHB2_Bus*/

#define OTGFS_ID   0x80

/*03- Peripheral on APB1_Bus*/

#define TIM2_ID      0x1
#define TIM3_ID      0x2
#define TIM4_ID      0x4
#define TIM5_ID      0x8
#define WWDG_ID      0x800
#define SPI2_ID      0x4000
#define SPI3_ID      0x8000
#define USART2_ID    0x20000
#define I2C1_ID      0x200000
#define I2C2_ID      0x400000
#define I2C3_ID      0x800000
#define PWR_ID       0x10000000

/*04- Peripheral on APB2_Bus*/

#define TIM1_ID      0x1
#define USART1_ID    0x10
#define USART6_ID    0x20
#define ADC1_ID      0x100
#define SDIO_ID      0x800
#define SPI1_ID      0x1000
#define SPI4_ID      0x2000
#define SYSCFG_ID    0x4000
#define TIM9_ID      0x10000
#define TIM10_ID     0x20000
#define TIM11_ID     0x40000

/***********************0x10000000 END of Peripheral ID      *********************************/

/* RCC State */
#define RCC_ENAPLE	 0
#define RCC_DISAPLE	 1


#define  RCC_SYSCLK_HSI                 0x00000001    /*Enable HSI                 */
#define  RCC_SYSCLK_HSE_CRYSTAL         0x00010000   /* Enable HSE without Bypass  */
#define  RCC_SYSCLK_HSE_RC              0x00050000   /* Enable HSE with Bypass     */
#define  RCC_SYSCLK_PLL                 0x01000000   /* Enable pLL                 */

/***** Select the PLL Configuration  ****/
/*
  NOT:Select For PLL_M value from  this range:  [2  to 63 ]
*/
#define  RCC_PLLM     2
/*
  NOT:Select For PLL_N value from  this range:  [ 192 to  432 ]
*/
#define RCC_PLLN     192

/*
  NOT:Select For PLL_P value from  this range:  [ 2 , 4 , 6 , 8 ]
*/
#define RCC_PLLP     2

/*PLL Source Clock */
#define RCC_PLLSOURCE_HSI    0xffBfffff
#define RCC_PLLSOURCE_HSE    0x00400000



//#define  RCC_SYSCLK_PLL_WITH_HSE        0x01010000   /* Enable PLL with HSE source */
//#define  RCC_SYSCLK_PLL_WITH_HSI        0x01000081   /* Enable PLL with HSI source */

typedef enum {
	RCC_NOK,
	RCC_OK,
	RCC_ClockNotReady,
	RCC_ConfigNotValid,
}RCC_enuErrorState_t;



void RCC_EnableSystemClock(u32   Copy_u32SysClock);
void RCC_DisableSystemClock(u32  Copy_u32SysClock);
RCC_enuErrorState_t RCC_SelectClockSystem(u32   Copy_u32SysClock);
RCC_enuErrorState_t RCC_PLLConfig(u32 Copy_u32PLL_M,u32 Copy_u32PLL_N,u32 Copy_u32PLL_P,u32 Copy_u32ClkSourc);
void RCC_EnablePeripheralClock(u8 Copy_BusId, u32 Copy_u32PerId);
void RCC_DisablePeripheralClock(u8 Copy_BusId, u32 Copy_u32PerId);


#endif
