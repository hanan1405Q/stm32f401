
#include "Runnable.h"
#include "Sched.h"


Runnable_t Runnabls [_Max_Num]=
{
  [Runnable_1]={
                 .Periodicty=10,
                 .Callback=fun1,
                 .FirstDelay=1,

              },

   
  [Runnable_1]={
                 .Periodicty=100,
                 .Callback=fun2,
                 .FirstDelay=2,

              },

    
  [Runnable_1]={
                 .Periodicty=500,
                 .Callback=fun3,
                 .FirstDelay=3,

              },
};