#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/

#include "STD_TYPE.h"
#include "LCD_config.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

typedef enum
{
  Init_State,
  Operation_State,
  Off_State
}LCD_State_t;


typedef struct LCD
{
   
   void* Port;
   u32 Pin;
}LCD_strPinConfig_t;

typedef enum {
	
	LCD_enuNOK,
	LCD_enuOK
	
  }LCD_enuErrorStatus_t;


/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

void LCD_Init(void);
void LCD_WriteString(char* Copy_ptrString, u8 Copy_u8Length);
void LCD_GetState(u8* Copy_addState);
void LCD_ClearScreen(void);


#endif // HAL_LCD_LCD_H_