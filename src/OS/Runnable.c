
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
                 .Periodicty=50,
                 .Callback=Switch_APP,
                 .FirstDelay=0,

              },

   /*
  [Runnable_3]={
                 .Periodicty=100,
                 .Callback=fun3,
                 .FirstDelay=0,

              },

    */
};