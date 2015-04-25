
#include "workpool.hxx"

WorkPool::WorkPool( )
{
    pthread_mutex_init(&mutex_,NULL);
}

WorkPool::~WorkPool( )
{
    AsyncThreadContext*  work = NULL;
    pthread_mutex_lock(&mutex_); 
    while( m_pool.size( ) > 0 )
    {
        work = m_pool.front( );
        m_pool.pop_front();
        delete work;
    }        
    pthread_mutex_unlock(&mutex_);
    pthread_mutex_destroy($mutex_);
}


void WorkPool::pushWork( AsyncThreadContext* work)
{
    pthread_mutex_lock(&mutex_); 
    m_pool.push_back( work );
    pthread_mutex_unlock(&mutex_);
}

AsyncThreadContext* WorkPool::popWork( )
{
    AsyncThreadContext*  work = NULL;
    pthread_mutex_lock(&mutex_); 
    if( m_pool.size() > 0 )
    {
        work = m_pool.front( );
        m_pool.pop_front();
    }
    pthread_mutex_unlock(&mutex_);
    return work;
}

unsigned int WorkPool::size( )
{
    return m_pool.size( );
}
