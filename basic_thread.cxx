//Copyright (C) 2006, All Rights Reserved, by
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
// Celerra Command Service Daemon BasicThread
//
// ABSTRACT:
//
// In addition to header functions, implements extern C routine "thread_start" so as to
// invoke the virtual run routine on applications.
//
// AUTHORS:
//
// Srikanth Kaligotla
//
// CREATION DATE:
// 
// 08/01/06
//
// MODIFICATION HISTORY:
//
// Log information available via 'cvs log'
//
// VERSION:
//  
// $Id: cl_basic_thread.cxx,v 1.8 2009/06/04 02:36:32 williw Exp $
// $Source: /usr/local/cvs/archive/sys_mgmt/src/kernel/Attic/cl_basic_thread.cxx,v $ 
//
#include <unistd.h>
#include <string>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <assert.h>
#include "basic_thread.hxx"

///////////////////////////////////////////////////////////////////////////////
// Externs used in this file.
//

///////////////////////////////////////////////////////////////////////////////
// Constants, statics etc.
//
//#define CL_THREAD_STACK_SIZE 32*1024

///////////////////////////////////////////////////////////////////////////////
// Consructor
//
CLBasicThread::CLBasicThread( const char* name, threadFrequency tFreq, int interval)
    :
        m_sName( name ),
        m_thrState(CLBasicThread::NOT_RUNNING),
        m_thrSubState(CLBasicThread::NOT_RUNNING),
        m_iRunInterval(interval),
        m_bStop(false),
        m_threadFrequency(tFreq),
        m_bExit(false)
{
}

///////////////////////////////////////////////////////////////////////////////
// Destructor
//
CLBasicThread::~CLBasicThread()
{
}

///////////////////////////////////////////////////////////////////////////////
// Thread creation
//
void CLBasicThread::start()
{
    assert( m_thrState == NOT_RUNNING );
    /* Create First thread */
    pthread_attr_init(&m_thr_attr);
    pthread_attr_setscope(&m_thr_attr, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setdetachstate(&m_thr_attr, PTHREAD_CREATE_DETACHED);
    //pthread_attr_setstacksize(&m_thr_attr, CL_THREAD_STACK_SIZE);

    // GCK 10/17/08: Linux Upgrade - change to fix compile error on g++ 4.x
    if(( pthread_create(&m_thr,
                    &m_thr_attr,
                    CLBasicThread::thread_start,
                    this)) != 0 )
    {
        perror("Failed");
        return;
    }
    m_thrState = RUNNING;
}

///////////////////////////////////////////////////////////////////////////////
// Thread stop
// Set the m_bStop to indicate thred to stop execution and exit. 
// If a thread is in sleep, call wakeup so thread can stop and exit.
void CLBasicThread::stop()
{
    m_bStop = true;
    if (m_iRunInterval > 0 && m_thrSubState == NOT_RUNNING && !m_bExit)
        wakeup(); //wake up the thread

    return;
}

///////////////////////////////////////////////////////////////////////////////
// Thread wakeup.
// As a result of SIGALRM the thread will wake up if in sleep
void CLBasicThread::wakeup()
{
    if( m_thrState == RUNNING )
        sendSignal( SIGALRM );
}

///////////////////////////////////////////////////////////////////////////////
// Thread termination.
// As a result of SIGUSR2 ( Contract between signal handler and thread object ), thread gets
// interrupted so that pthread_exit() is invoked inside signal handler.
void CLBasicThread::terminate()
{
    // Make sure that thread is not running before sending the terminate signal. You don't want to
    // send multiple terminates to same thread.
    m_bStop = true;
    if( m_thrState == RUNNING && !m_bExit)
    {
        sendSignal( SIGUSR2 );
        m_thrState = NOT_RUNNING;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Private access.
// Interface to send a signal to self. 
void CLBasicThread::sendSignal( int signal )
{
    pthread_kill( m_thr, signal );
}

///////////////////////////////////////////////////////////////////////////////
// Private access.
// The base routine that controls threds execution. 
void CLBasicThread::base_run()
{
    do
    {
        if (m_iRunInterval > 0)
            sleep(m_iRunInterval);

        if (!m_bStop)
        {
            m_thrSubState = CLBasicThread::RUNNING;
            run();
            m_thrSubState = CLBasicThread::NOT_RUNNING;
        }
    } while (m_threadFrequency == PERIODIC && !m_bStop);

    m_thrState = NOT_RUNNING;
    m_bStop = true;    
    m_bExit = true;
}

///////////////////////////////////////////////////////////////////////////////
// Static functions implementation
//
// GCK 10/17/08: Linux Upgrade - change function def to fix compile error on g++ 4.x
void* CLBasicThread::thread_start( void* arg )
{
    ((CLBasicThread*)arg)->base_run() ;
    return NULL ;
} 



