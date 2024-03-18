
#ifndef _RCC_INTERFACE_H 
#define _RCC_INTERFACE_H 

#include "STD_TYPE.h"

/* PLL Mode */
//#define  PLL  	 0x0
//#define  PLLI2S  0x1



/*******			Peripheral ID				********/

/*01- Peripheral on AHB1_Bus*/
#define GPIOA_ID   0x00000001
#define GPIOB_ID   0x00000002
#define GPIOC_ID   0x00000004
#define GPIOD_ID   0x00000008
#define GPIOE_ID   0x00000010
#define GPIOH_ID   0x00000080
#define CRC_ID     0x00001000
#define DMA1_ID    0x00200000
#define DMA2_ID    0x00400000

/*02- Peripheral on AHB2_Bus*/

#define OTGFS_ID   0x01000080

/*03- Peripheral on APB1_Bus*/

#define TIM2_ID      0x02000001
#define TIM3_ID      0x02000002
#define TIM4_ID      0x02000004
#define TIM5_ID      0x02000008
#define WWDG_ID      0x02000800
#define SPI2_ID      0x02004000
#define SPI3_ID      0x02008000
#define USART2_ID    0x02020000
#define I2C1_ID      0x02200000
#define I2C2_ID      0x02400000
#define I2C3_ID      0x02800000
#define PWR_ID       0x12000000

/*04- Peripheral on APB2_Bus*/

#define TIM1_ID      0x03000001
#define USART1_ID    0x03000010
#define USART6_ID    0x03000020
#define ADC1_ID      0x03000100
#define SDIO_ID      0x03000800
#define SPI1_ID      0x03001000
#define SPI4_ID      0x03002000
#define SYSCFG_ID    0x00004000
#define TIM9_ID      0x00010000
#define TIM10_ID     0x00020000
#define TIM11_ID     0x00040000

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
void RCC_EnablePeripheralClock(u32 Copy_u32PerId);
void RCC_DisablePeripheralClock(u32 Copy_u32PerId);


#endif
