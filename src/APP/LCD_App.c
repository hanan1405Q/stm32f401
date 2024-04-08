
#include "HAL/LCD/LCD.h"

void LCD_App(void)
{
    static u8 state=0;
    u8 ReqState;

    char* str="Hello ITI_44";
    s16 num=1405;

    LCD_GetReqState(&ReqState);

    switch (state)
    {
         case 0:
            LCD_ClearScreen();
            if(ReqState==Ready)
            {
                state=1;
            }
        break;

        case 1:
            LCD_WriteString(str,12);
            if(ReqState==Ready)
            {
                state=2;
            }
        break;

        case 2:
            LCD_GOTO_XY(1,7);
            if(ReqState==Ready)
            {
                state=3;
            }
        break;
        case 3:
            LCD_WriteNumber(num);
            if(ReqState==Ready)
            {
                state=4;
            }
        break;

        case 4:
            LCD_GOTO_XY(0,0);
            if(ReqState==Ready)
            {
                state=1;
            }
        break;
    }
}