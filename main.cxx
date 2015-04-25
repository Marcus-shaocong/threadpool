#include "rep_thread.hxx"
#include "rep_thread_pool.hxx"
#include <iostream>
#include <string>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

using namespace std;
void *computer(void *arg)
{
    long num = (long)arg;
    cout <<"process a number:"<< num <<endl;
}

int main()
{
    CLRepThreadPool * pool1 = CLRepThreadPool::instance(); 
    srand(10086);
    for (int i=0;i<5; i++)
    {
        int tmp = rand()%89;
        std::cout<<"pass tmp:"<<tmp<<endl;
        Task tsk;
        tsk.task_func_ = computer;
        tsk.arg = (void*)tmp;
        pool1->add_new_task(tsk);
    }
    pool1->startThreads();
    return 0;

}
