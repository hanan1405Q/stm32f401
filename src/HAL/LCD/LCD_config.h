#ifndef HAL_LCD_LCD_CONFIG_H_
#define HAL_LCD_LCD_CONFIG_H_

typedef enum
{
   D0_PIN,
   D1_PIN,
   D2_PIN,
   D3_PIN,
   D4_PIN,
   D5_PIN,
   D6_PIN,
   D7_PIN,

   RS_PIN,
   RW_PIN,
   E_PIN,

   _NUM_OF_PINS


}LCD_enuPinName_t;

/**
  Here you need to configure LCD_DATA_MODE you have two options:
	 1- LCD_EIGHT_BIT_MODE
	 2- LCD_FOUR_BIT_MODE
**/
#define LCD_DATA_MODE		LCD_EIGHT_BIT_MODE

/**
  Here you need to configure LCD_LINES	you have two options:
	 1- LCD_ONE_LINE
	 2- LCD_TWO_LINE
**/
#define LCD_LINES		LCD_TWO_LINE



/**
  Here you need to configure LCD_FONT you have two options:
	 1-LCD_FONT_5X7
	 2-LCD_FONT_5X10
**/
#define LCD_FONT		LCD_FONT_5X7

/**
  Here you need to configure LCD_DISPLAY_MODE you have two options:
	1-LCD_DISPLAY_ON
	2-LCD_DISPLAY_OFF	
**/
#define LCD_DISPLAY_MODE	LCD_DISPLAY_ON


/**
  Here you need to configure LCD_CURSOR_MODE you have three options:
	1-NOT_DISPLAYED_CURSOR
	2-DISPLAY_NO_BLINKING
	3-DISPLAY_BLINKING	
**/
#define LCD_CURSOR_MODE		NOT_DISPLAYED_CURSOR

/**
  Here you need to configure LCD_SHIFTI_MODE you have two options:
	 1- LCD_SHIFT_ON
	 2- LCD_SHIFT_OFF
**/
#define LCD_SHIFT_MODE LCD_SHIFT_ON

/**
 Here you need to configure INCREMENT_DECREMENT_MODE you have two options:
	 1- LCD_INCREMENT
	 2- LCD_DECREMENT
*/
#define INCREMENT_DECREMENT_MODE	LCD_INCREMENT




#endif // HAL_LCD_LCD_CONFIG_H_