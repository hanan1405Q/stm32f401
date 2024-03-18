#ifndef OS_RUNNABLE_H_
#define OS_RUNNABLE_H_

void fun1 (void);
void fun2 (void);
void fun3 (void);
void Trafic_APP(void);

extern void SW_GetState(void);
void Switch_APP(void);


typedef enum
{
    Runnable_1,
    Runnable_2,
    //Runnable_3,
    _Max_Num

}enum_Name_t;


#endif // OS_RUNNABLE_H_