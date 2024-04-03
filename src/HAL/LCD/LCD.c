/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "BIT_MATH.h"

#include "MCAL/GPIO/GPIO.h"
#include "LCD.h"



/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define PERIODCITY_OF_TASK      2


/*********** This Secion  Contain The  LCD Commands *********/

/************** Function Set Command Configurations *********************/
#define LCD_FOUR_BIT_MODE		0
#define LCD_EIGHT_BIT_MODE		1

#define LCD_ONE_LINE			0
#define LCD_TWO_LINE			1

#define LCD_FONT_5X7			0
#define LCD_FONT_5X10			1
/************** Display Contror Command Configurations *********************/
#define LCD_DISPLAY_OFF			0
#define LCD_DISPLAY_ON			1

#define NOT_DISPLAYED_CURSOR    0
#define DISPLAY_NO_BLINKING		2
#define DISPLAY_BLINKING		3
/************** Entry Mode Set  Command Configurations *********************/
#define LCD_SHIFT_OFF			0
#define LCD_SHIFT_ON			1

#define LCD_DECREMENT			0
#define LCD_INCREMENT			1
/*************************** OTHER  Macros Service To The Implementation  ***************/
#define  NUM_OF_ROW 2
#define  NUM_OF_COLUMN 16

#define  END_OF_ROW1   16
#define  END_OF_ROW2   32
/*************************************************************************************************/
#define FUN_SET           (0b00100000|(LCD_DATA_MODE<<4)|(LCD_LINES<<3)|(LCD_FONT<<2))
#define DISPLAY_CTRL      (0b00001000|(LCD_DISPLAY_MODE<<2)|LCD_CURSOR_MODE)
#define ENTRY_MODE_SET    (0b00000100|(INCREMENT_DECREMENT_MODE<<1)|LCD_SHIFT_MODE)

/*  Supported  Commands*/
#define CLEAR_SCREEN             0X01
#define RETURN_HOME              0X02
#define EIGHT_BIT_FUNCTION_SET   0X38
#define FOUR_BIT_FUNCTION_SET    0x28

#define ENTRY_MODE_INCR          0x06
#define ENTRY_MODE_DECR          0x04
#define DISPLAY_OFF_CURSOR_OFF	         0x08
#define DISPLAY_ON_CURSOR_OFF	         0x0C
#define DISPLAY_ON_CURSOR_ON_BLINK_OFF	 0x0E
#define DISPLAY_ON_CURSOR_ON_BLINK_ON	 0x0F
#define SHIFT_CURSOR_LEFT                0X10
#define SHIFT_CURSOR_RIGHT               0X14
#define SHIFT_ENTIRE_DISPLAY_LEFT        0X18
#define SHIFT_ENTIRE_DISPLAY_RIGHT       0X1C


/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
typedef struct 
{
    char* Data;
    u8 Length;
    u8 Pos_X;
    u8 Pos_Y;
    s16 Num;
    u8 Req_type;
    u8 Req_State;

}User_Request_t;


typedef enum
{
    None,
    WriteStr,
    WriteNum,
    GOTO,
    Shift_Currsor_Left,
    Shift_Currsor_Right,
    Clear,

}Req_Type_t;

typedef enum
{
    Step_1,
    Step_2,
    Step_3,
    Step_4,
    Step_5

}Stage_t;


typedef enum
{
    Power_on,
    FunSet,
    DisplayControl,
    ClearScreen,
    EntryMode,
    end
}Init_Stage_t;
/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/

extern LCD_strPinConfig_t LCD_PinCfg [_NUM_OF_PINS];

//static u8 IndexOfCursor=0;

static u8 LCD_State;
User_Request_t User_Request;

static u8 WriteFlage;
static u8 CommandFlage;



/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



static void  LCD_WriteCommand (u8 Copy_u8Command)
{
    u8 static state=Step_1;

    switch (state)
    {
    case Step_1 :
        CommandFlage=0;
        GPIO_SetPinValue(LCD_PinCfg[RS_PIN].Port,LCD_PinCfg[RS_PIN].Pin,GPIO_LOW);
	    GPIO_SetPinValue(LCD_PinCfg[RW_PIN].Port,LCD_PinCfg[RW_PIN].Pin,GPIO_LOW);
	    /* write the command on D0->D7 Pin*/
        for(u8 i=0 ; i<8 ; i++)
        {
            GPIO_SetPinValue(LCD_PinCfg[i].Port,LCD_PinCfg[i].Pin,GET_BIT(Copy_u8Command,i));
        }
        /* Set The Enable Pin of LCD to Receive what sent to her (Triger signal to the Mc of LCd ) */
        GPIO_SetPinValue(LCD_PinCfg[E_PIN].Port,LCD_PinCfg[E_PIN].Pin,GPIO_HIGH);

        state=Step_2;   
    break;

    case Step_2:

         GPIO_SetPinValue(LCD_PinCfg[E_PIN].Port,LCD_PinCfg[E_PIN].Pin,GPIO_LOW);
         state=Step_1;
         CommandFlage=1;

    break;
          /* i think this section should be under step_2 ,for not consuming extra 2msec */
            /*case Step_3:
            CommandFlage=1;
            state=Step_1;
            break;*/
    }
}

static void LCD_Config_Pins(void)
{
    GPIO_PinConfig_t pin;
    pin.Speed= GPOI_SPEED_MED;
    pin.Mode= GPIO_MODE_OUT_PP;

    for(u8 index=0 ; index <  _NUM_OF_PINS ; index++)
    {
        pin.Port=LCD_PinCfg[index].Port;
        pin.Pin=LCD_PinCfg[index].Pin;
        GPIO_Init(&pin);
    }

}

static void LCD_GotoDDRAM_XY_Process()
{      
    static u8 state=Step_1;
    static u8 L_u8DdramAdd=0;

    switch (state)
    {
      case Step_1:
         if(User_Request.Pos_X==0)
            {
            L_u8DdramAdd=0x00+User_Request.Pos_Y;
            //IndexOfCursor=Copy_u8Y;
            }
         else
            {
            L_u8DdramAdd=0x40+User_Request.Pos_Y;	
            // IndexOfCursor=Copy_u8Y+16;
            }
    
            /*we set the DDRAM Address through a command ->  (1 b7 b6 b5 b4 b3 b2 b1 b0)  */
            /* we should set b7 to be 1 and send the address b0...b6  */
            /*this line put the Add in the required format for the command*/
            L_u8DdramAdd=L_u8DdramAdd | 0x80  ;
            state=Step_2;
        break;

        case Step_2:
            if(CommandFlage==0)
            {
            LCD_WriteCommand(L_u8DdramAdd);
            }
            else
            {
            L_u8DdramAdd=0;
            CommandFlage=0;
            state=Step_1;
            User_Request.Pos_X=0;
            User_Request.Pos_Y=0;
            User_Request.Req_type=None;
            User_Request.Req_State=Ready;

            }
        break;

    }

}   	


static void  LCD_WriteChar (u8 Copy_u8Char)
{
    u8 static state=Step_1;

    switch (state)
    {
      case Step_1 :
            WriteFlage=0;
            /*  write a command should set RW_PIN=0 (Write) RS_PIN=1 (Data)*/
            GPIO_SetPinValue(LCD_PinCfg[RS_PIN].Port,LCD_PinCfg[RS_PIN].Pin,GPIO_HIGH);
            GPIO_SetPinValue(LCD_PinCfg[RW_PIN].Port,LCD_PinCfg[RW_PIN].Pin,GPIO_LOW);
            /* write the command on D0->D7 Pin*/
            for(u8 i=0 ; i<8 ; i++)
            {
                GPIO_SetPinValue(LCD_PinCfg[i].Port,LCD_PinCfg[i].Pin,GET_BIT(Copy_u8Char,i));
            }
            
            /* Set The Enable Pin of LCD to Receive what sent to her (Triger signal to the Mc of LCd ) */
            GPIO_SetPinValue(LCD_PinCfg[E_PIN].Port,LCD_PinCfg[E_PIN].Pin,GPIO_HIGH);
            state=Step_2;   
      break;

      case Step_2:

         GPIO_SetPinValue(LCD_PinCfg[E_PIN].Port,LCD_PinCfg[E_PIN].Pin,GPIO_LOW);
         state=Step_1;
         WriteFlage=1;

      break;

    }
}
/*

static void  LCD_WriteChar (u8 Copy_u8Char)
{
    u8 static state=Step_1;

    switch (state)
    {
    case Step_1 :
        WriteFlage=0;

        // Check if the cursor has reached the end of the first line, move to the second line
        if(IndexOfCursor == END_OF_ROW1)
        {
            if(CommandFlage==0)
            {
                LCD_GotoDDRAM_XY(1, 0);
            }
            else
            {
                CommandFlage=0;
            }
            
        }
        // Check if the cursor has reached the end of the second line, move to the beginning of the first line
        else if(IndexOfCursor == END_OF_ROW2)
        {
            if(CommandFlage==0)
            {
               LCD_GotoDDRAM_XY(0, 0);
            }
            else
            {
                IndexOfCursor = 0;
                CommandFlage=0;
            }
           
           
        }
         // write a command should set RW_PIN=0 (Write) RS_PIN=1 (Data)
        GPIO_SetPinValue(LCD_PinCfg[RS_PIN].Port,LCD_PinCfg[RS_PIN].Pin,GPIO_HIGH);
	    GPIO_SetPinValue(LCD_PinCfg[RW_PIN].Port,LCD_PinCfg[RW_PIN].Pin,GPIO_LOW);
	    // write the command on D0->D7 Pin
        for(u8 i=0 ; i<8 ; i++)
        {
            GPIO_SetPinValue(LCD_PinCfg[i].Port,LCD_PinCfg[i].Pin,GET_BIT(Copy_u8Char,i));
        }
        
        IndexOfCursor++;
        //Set The Enable Pin of LCD to Receive what sent to her (Triger signal to the Mc of LCd ) 
        GPIO_SetPinValue(LCD_PinCfg[E_PIN].Port,LCD_PinCfg[E_PIN].Pin,GPIO_HIGH);
        state=Step_2;   
    break;

    case Step_2:

         GPIO_SetPinValue(LCD_PinCfg[E_PIN].Port,LCD_PinCfg[E_PIN].Pin,GPIO_LOW);
         state=Step_1;
         WriteFlage=1;

    break;

         case Step_3:
         WriteFlage=1;
         state=Step_1;
         break;
    }
}

*/
  

  


  static void LCD_Init_SM(void)
  {
      static u8 init_state=Step_1;
      static u8 Loc_time;
      Loc_time+=PERIODCITY_OF_TASK;

      switch (init_state)
      {
        case Step_1:
          if(Loc_time==40)
          {
            LCD_Config_Pins();
            init_state=Step_2;
             Loc_time=0;
          }

        break;
      
       case Step_2:
             if(CommandFlage==0)
             {
                LCD_WriteCommand(FUN_SET);
             }
             else
             {
                init_state=Step_3;
                CommandFlage=0;
             }
        break;

        case Step_3:
             if(CommandFlage==0)
             {
                LCD_WriteCommand(DISPLAY_CTRL);
             }
             else
             {
                init_state=Step_4;
                CommandFlage=0;
             }
        break;

        case Step_4:
             if(CommandFlage==0)
             {
                LCD_WriteCommand(CLEAR_SCREEN);
             }
             else
             {
                init_state=Step_5;
                CommandFlage=0;
             }
         break;

         case Step_5:
             if(CommandFlage==0)
             {
                LCD_WriteCommand(ENTRY_MODE_SET);
             }
             else
             {
                init_state=Step_1;
                 CommandFlage=0;
                LCD_State=Operation_State;
               
             }
        break;

    }
}


static void  LCD_WriteProcess(void)
{
    static u8 Position=0;
    if(Position<User_Request.Length)
    {
        if(WriteFlage==0)
        {
            LCD_WriteChar(User_Request.Data[Position]);
        }
        else
        {
            Position++;
            WriteFlage=0;
        }
    }

    else
       {
          Position=0;
         /*End Mechanisim*/
         User_Request.Data=NULL;
         User_Request.Length=0;
         User_Request.Req_State=None;
         User_Request.Req_State=Ready;

       }

}

 static void LCD_ClearProcess(void)
 {
      if(CommandFlage==0)
      {
        LCD_WriteCommand(CLEAR_SCREEN);
      }
      else
      {
         CommandFlage=0;
         User_Request.Data=NULL;
         User_Request.Length=0;
         User_Request.Req_State=None;
         User_Request.Req_State=Ready;
      }
 }

static void LCD_WriteNumProcees(void)
{
   static u8 Local_Arr[8]={0};
   static u8 L_counter=0;
		
	if(User_Request.Num<0)
	{
		//Convert Negative Number to Positive and write the Sign 
		User_Request.Num=User_Request.Num*-1;
        if(WriteFlage==0)
        {
          LCD_WriteChar('-');
        }
        else
        {
            WriteFlage=0;
        }
		
    }
	
	/*This Part Parse digits And append them in array */
    while (User_Request.Num>0)
    {
       Local_Arr[L_counter]=User_Request.Num%10;
        User_Request.Num/=10;
        L_counter++;
    }
    
    if(L_counter>0)
    {
        if(WriteFlage==0)
        {
            LCD_WriteChar('0'+Local_Arr[L_counter-1]);
        }
        else
        {
            L_counter--;
            WriteFlage=0;
        }
    }

    else
    {
        L_counter=0;
        //Local_Arr[8]={0};
        User_Request.Num=0;
        User_Request.Req_type=None;
        User_Request.Req_State=Ready;
      

    }
	
   
}




void LCD_Task(void)
{
    if(LCD_State==Init_State)
    {
         LCD_Init_SM();
    }

    if( (LCD_State==Operation_State) && (User_Request.Req_State==Busy) )
    {
        switch(User_Request.Req_type)
        {
            case WriteStr:
                 LCD_WriteProcess();
            break;

            case WriteNum:
                 LCD_WriteNumProcees();
            break;

            case GOTO:
                 LCD_GotoDDRAM_XY_Process();
            break;
           
           case Shift_Currsor_Left:
                //LCD_ShiftLeft_Process();
           break;

           case Shift_Currsor_Right:
                //LCD_ShiftRightt_Process();
           break;

            case Clear:
                LCD_ClearProcess();
            break;
        }

    }
   
}



/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/
void LCD_Init(void)
{
    LCD_State=Init_State;
}

void LCD_GetState(u8* Copy_addState)
{
   *Copy_addState=LCD_State;
}

void LCD_GetReqState(u8* Copy_addReqState)
{
   *Copy_addReqState=User_Request.Req_State;
}

void LCD_WriteString(char* Copy_ptrString, u8 Copy_u8Length)
{
    if(User_Request.Req_State==Ready)
    {
        User_Request.Data=Copy_ptrString;
        User_Request.Length=Copy_u8Length;
        User_Request.Req_type=WriteStr;
        User_Request.Req_State=Busy;
    }
  
}

void LCD_WriteNumber(s16 Copy_s16Number)
{
    if(User_Request.Req_State==Ready)
    {
        User_Request.Num= Copy_s16Number;
        User_Request.Req_type=WriteNum;
        User_Request.Req_State=Busy;
    }
  
}

void LCD_GOTO_XY(u8 Copy_u8X,u8 Copy_u8Y)
{
    if(User_Request.Req_State==Ready)
    {
        User_Request.Pos_X=Copy_u8X;
        User_Request.Pos_Y=Copy_u8Y;
        User_Request.Req_type=GOTO;
        User_Request.Req_State=Busy;
    }
  
}

void LCD_ClearScreen(void)
{
     if(User_Request.Req_State==Ready)
    {
        User_Request.Data=NULL;
        User_Request.Length=0;
        User_Request.Req_type=Clear;
        User_Request.Req_State=Busy;
    }
}

