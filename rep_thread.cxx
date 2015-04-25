//Copyright (C) 2006, 2007, 2008 All Rights Reserved, by
// EMC Corporation, Hopkinton MA.
//
// This software is furnished under a license and may be used and copied
// only  in  accordance  with  the  terms  of such  license and with the
// inclusion of the above copyright notice. This software or  any  other
// copies thereof may not be provided or otherwise made available to any
// other person. No title to and ownership of  the  software  is  hereby
// transferred.
//
// The information in this software is subject to change without  notice
// and  should  not be  construed  as  a commitment by EMC Corporation.
//
// EMC assumes no responsibility for the use or  reliability of its
// software on equipment which is not supplied by EMC.
//
//
// FACILITY:
//
// 
// ABSTRACT:
//
// See header file (rep_restore_thread.hxx)
//
// AUTHORS:
//
// 
//
// CREATION DATE:
//
// 
//
// MODIFICATION HISTORY:
//
// 
//
// VERSION:
//
// 
// 
//

// standard includes
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/vfs.h>
#include <syslog.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <assert.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
// file includes
#include "rep_thread.hxx"

#include <pthread.h>
#include "rep_thread_pool.hxx"
//////////////////////////////////////////////////////////////////////////////
// Externs used in this file.
//


///////////////////////////////////////////////////////////////////////////////
// Constants, static functions etc.
//

///////////////////////////////////////////////////////////////////////////////
// Constructor
RepRestoreThread::RepRestoreThread(const char* name, std::string arg)
    :   CLBasicThread(name,CLBasicThread::ONCE,0),
        m_bFree(true),
        argument(arg)
{
    cmdStr = "perl /emc/liangs4/test/thread/test.pl " + argument;
    pthread_mutex_init(&mutex_,NULL);
}


///////////////////////////////////////////////////////////////////////////////
// Destructor
RepRestoreThread::~RepRestoreThread()
{
    pthread_mutex_destroy(&mutex_);
}

// ///////////////////////////////////////////////////////////////////////////////
// Main entry point for the thread. Loops here forever.
void RepRestoreThread::run()
{
    int retval = 0, ifexit = 0, exitstatus = 0, ifsignal = 0, termsig = 0, ifstop = 0, stopsig = 0, ifdump = 0;

CLRepThreadPool* pool = CLRepThreadPool::instance();
Task task;
while(1)
{
  pthread_mutex_lock(&mutex_); 
   std::cout<<"thread "<<this->getName()<<" "<<std::endl;
   if(pool->get_size() != 0)
   {
       pool->get_task(task);
       task.task_func_(task.arg); 
   }
   if(pool->get_size()==0)
   {
       break;
   }
   pthread_mutex_unlock(&mutex_); 
}
/* 
    std::string in;
    std::string s = ssystem(cmdStr.c_str());
    std::istringstream iss(s);
    std::string line;
    while ( std::getline(iss, line) )
    {
        //std::cout << "LINE-> " + line + "  length: " << line.length() << std::endl;
        std::cout <<line<< std::endl;
    }
    // gather statistics - thread is no longer idle
    retval = system(cmdStr.c_str());
    std::cout<<"return value:"<<retval<<std::endl;

    ifexit = WIFEXITED(retval);
    if (ifexit)
        exitstatus = WEXITSTATUS(retval);

    ifsignal = WIFSIGNALED(retval);
    if (ifsignal)
        termsig = WTERMSIG(retval);

    ifstop = WIFSTOPPED(retval);
    if (ifstop)
        stopsig = WSTOPSIG(retval);

    ifdump = WCOREDUMP(retval);

    std::cout<<"existstaus: "<<exitstatus<<std::endl;*/
}


///////////////////////////////////////////////////////////////////////////////
// Debugging aid
//
std::string& RepRestoreThread::dumpstats(std::string&
        str) const
{
    char ts[256];

    snprintf(ts, sizeof(ts), "hello world");

    str += ts;
    return str;
}


std::string RepRestoreThread::ssystem(const char* command)
{
    char tmpname [L_tmpnam];
    std::tmpnam ( tmpname );
    std::string scommand = command;
    std::string cmd = scommand + " >> " + tmpname;
    std::system(cmd.c_str());
    std::ifstream file(tmpname, std::ios::in );
    std::string result;
    if (file) {
        while (!file.eof()) result.push_back(file.get());
        file.close();
    }
    remove(tmpname);
    return result;
}

/*
int main()
{
    CLThreadPool* thPool = new CLThreadPool();
    for(int i=0; i<5; i++)
    {
        char name[32];
        sprintf(name, "Thread%d",i);
        thPool->addThread(new RepRestoreThread(name,name));
    }
    thPool->startThreads();
    int isStop = 0;
    while(1)
    {

        for(int i=0; i<5; i++)
        {
            RepRestoreThread * repthr = dynamic_cast<RepRestoreThread*>((thPool->getThreadList())[i]);
            if(repthr != NULL)
            {
                if(!repthr->hasExited())
                {
                    break;
                }
                else
                {
                    isStop = 1;
                }
            }
        }

        if(isStop)
            break;
    }

    RepRestoreThread* th1 = new RepRestoreThread("Thread1");
    th1->start();
    long long count = 0;
    while(1)
    {
        if(th1->hasExited())
        {th1->stop();
            sleep(5);
        break;}
    }
    
    std::cout<<"hello word in rep"<<std::endl;
    return 0;
}*/
