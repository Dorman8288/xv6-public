#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
int temp=0;
lock_t* lk;
void ThreadFunc1(void *args1,void *args2)
{
    for(int i=0;i<*(int*)args2;i++){
        temp+=*(int*)args1;
    }
    exit();
}
void ThreadFunc2(void *args1,void *args2)
{
    for(int i=0;i<*(int*)args2;i++){
        temp+=*(int*)args1;
    }
    exit();
}
void ThreadFunc3(void *args1,void *args2)
{
    printf(1,"args2:%d\n",args2);
    printf(1,"args1:%d\n",args1);
    for(int i=0;i<*(int*)args2;i++){
        lock_acquire(lk);
        temp+=*(int*)args1;
        //printf(1,"im here");
        lock_release(lk);

    }
    exit();
}
void ThreadFunc4(void *args1,void *args2)
{
    for(int i=0;i<*(int*)args2;i++){
        lock_acquire(lk);
        temp+=*(int*)args1;
        lock_release(lk);
    }   
    exit();
}
int main()
{
      lock_init(lk);
    int arg1 = 1, arg2 = 1000000;

    thread_create(&ThreadFunc1, (void *)&arg1, (void *)&arg2);
    thread_create(&ThreadFunc2, (void *)&arg1, (void *)&arg2);
    thread_join();
    thread_join();
    printf(1,"temp :%d without lock\n",temp);
    arg1 = 1;
    arg2 = 1000000;
    temp=0;
    thread_create(&ThreadFunc3, (void *)&arg1, (void *)&arg2);
    thread_create(&ThreadFunc4, (void *)&arg1, (void *)&arg2);
    thread_join();
    thread_join();
    printf(1,"temp :%d with lock\n",temp);
    exit();
}