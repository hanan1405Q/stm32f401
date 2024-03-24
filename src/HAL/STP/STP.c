/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/

#include "MCAL/GPIO/GPIO.h"
#include "MCAL/STK/STK.h"

#include "STP.h"


/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/

extern  STP_Pins_t STP_Pins[_MaxNum];

/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/


void STP_Init(void)
{
    GPIO_PinConfig_t pinc;
    pinc.Speed= GPOI_SPEED_MED;
    pinc.Mode= GPIO_MODE_OUT_PP;

   for(u8 index=0 ; index <  _MaxNum ; index++)
   {
       pinc.Port= STP_Pins[index].Port;
       pinc.Pin= STP_Pins[index].Pin;
       GPIO_Init(&pinc);

   }
}
void STP_SendData(u8 Copy_u8Data)
{
     s8 Local_Indx;
     u8 Local_bit;

     for(Local_Indx=7; Local_Indx >=0; Local_Indx--)
     {
      /*Get Bit By Bit Starting From MSB*/
       Local_bit=(Copy_u8Data >> Local_Indx)&1;

       /* Set Bit in the Serial Data Pin*/

       GPIO_SetPinValue(STP_Pins[Serial_Data].Port,STP_Pins[Serial_Data].Pin,Local_bit);

       /*Generat Clock Puls to Shift Reg*/

        GPIO_SetPinValue(STP_Pins[Shift_Clk].Port,STP_Pins[Shift_Clk].Pin,GPIO_HIGH);
        STK_SetBusyWait_ms(1);
        GPIO_SetPinValue(STP_Pins[Shift_Clk].Port,STP_Pins[Shift_Clk].Pin,GPIO_LOW);
        STK_SetBusyWait_ms(1);
        
     }

      /*Generat Clock Puls to Store Reg*/

        GPIO_SetPinValue(STP_Pins[Store_Clk].Port,STP_Pins[Store_Clk].Pin,GPIO_HIGH);
        STK_SetBusyWait_ms(1);
        GPIO_SetPinValue(STP_Pins[Store_Clk].Port,STP_Pins[Store_Clk].Pin,GPIO_LOW);
        STK_SetBusyWait_ms(1);
}