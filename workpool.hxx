#ifndef _WORK_POOL_HXX
#define _WORK_POOL_HXX
#include <list>
#include <pthread.h>

class AsyncThreadContext;

typedef void (*FunPtr)(AsyncThreadContext*);

class AsyncThreadContext
{
    public:
        AsyncThreadContext( );
        virtual ~AsyncThreadContext( );

        FunPtr  getProcFun( )
        {
            return m_procFun;
        }

        void setProcFun( FunPtr procCmd )
        {
            m_procFun = procCmd;
        }

        void  setCallbackFun( FunPtr callbackCmd )
        {
            m_calbackFun = callbackCmd;
        }

        FunPtr  getCallbackFun( )
        {
            return m_calbackFun;
        }

    private:
        FunPtr     m_procFun;
        FunPtr     m_calbackFun;
};

class WorkPool
{
    public:
        WorkPool( );
        ~WorkPool( );

        void pushWork( AsyncThreadContext* );

        AsyncThreadContext* popWork( );

        unsigned int size( );


    private:
        typedef   std::list<AsyncThreadContext*>  WorkList;
        WorkList                           m_pool;
        pthread_mutex_t                    m_PoolLock;
};

#endif
