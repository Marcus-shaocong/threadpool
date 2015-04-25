#ifndef _CL_REP_THREAD_POOL_H_
#define _CL_REP_THREAD_POOL_H_

//standard includes

// file includes
#include "thread_pool.hxx"
#include <pthread.h>
#include <list>

typedef void* (*task_callback)(void*);
class Task
{
    public:
        void *arg;
        task_callback task_func_;
};

//const int DEFAULT_BL_THREADS = 16;
class CLRepThreadPool : public CLThreadPool
{
    public:
        // ctor

        // manage the number of threads in the pool (unimplemented)
        //int increasePool(int newcount);
        //int decreasePool(int newcount);

        // control access to the pool
        //void lock() { m_PoolLock.lock(); };
        //void unlock() { m_PoolLock.unlock(); };
        static CLRepThreadPool * instance();
        void add_new_task(Task taskItem);
        void get_task(Task &taskItem);

        int get_size();
    private:
        static const int DEFAULT_BL_THREADS = 16;
        // the count of 16 is arbitrary: the optimal number should be
        // empirically determined
        static CLRepThreadPool * _singletonInst;
        CLRepThreadPool(int newcount = DEFAULT_BL_THREADS);
        CLRepThreadPool(CLRepThreadPool const&);
        void operator=(CLRepThreadPool const&);
        // dtor
         ~CLRepThreadPool();
        int m_iCount;           // number of threads in pool
        // semaphore to lock pool when modifying
        
        pthread_mutex_t mutex_;
        
        std::list<Task> workList;

};
#endif // _CL_REP_THREAD_POOL_H__

