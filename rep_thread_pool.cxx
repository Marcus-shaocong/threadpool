#include "rep_thread.hxx"
#include "rep_thread_pool.hxx"

////////////////////////////////////////////////////////////////////////////
// Externs used in this file.
//
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Constants, static functions etc.
//


///////////////////////////////////////////////////////////////////////////////
// Constructor
CLRepThreadPool * CLRepThreadPool::_singletonInst = NULL; 


CLRepThreadPool * CLRepThreadPool::instance()
{
    if(!_singletonInst)
        _singletonInst = new CLRepThreadPool();
    return _singletonInst;
}
CLRepThreadPool ::CLRepThreadPool(int newcount)
    : m_iCount(newcount)
{
    for (int i = 0; i < newcount; ++i)
    {
        char name[32];
        sprintf(name,"BLT%d",i);
        addThread( new RepRestoreThread(name,name) );
    }
}


CLRepThreadPool::~CLRepThreadPool()
{
}


void CLRepThreadPool::add_new_task(Task taskItem)
{
    workList.push_back(taskItem);
}


void CLRepThreadPool::get_task(Task &taskItem)
{
    taskItem = workList.front();
        workList.pop_front();
}

int CLRepThreadPool::get_size()
{
    return workList.size();
}
