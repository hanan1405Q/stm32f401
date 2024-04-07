
#include "Runnable.h"
#include "Sched.h"


Runnable_t Runnabls [_Max_Num]=
{
  [Runnable_1]={
                 .Periodicty=5,
                 .Callback=SW_GetState,
                 .FirstDelay=0,

              },

    
  [Runnable_2]={
                 .Periodicty=100,
                 .Callback=Switch_APP,
                 .FirstDelay=1,

  
              },

/**/
  [Runnable_3]={
                 .Periodicty=2,
                 .Callback=LCD_Task,
                 .FirstDelay=0,

              },

    [Runnable_4]={
                 .Periodicty=100,
                 .Callback=LCD_App,
                 .FirstDelay=1,

              },
/**/
    
};