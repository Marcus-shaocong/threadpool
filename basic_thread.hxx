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
// An abstract C++ object to encapsulate linux thread. pthread data structure is
// enacpsulated within this object. Function start() will init the data structure
// and create the thread. Threads are created as DETACHED with SYSTEM wide scope.
// Application threads should implement the run() function to perform its duties.
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
// $Id: cl_basic_thread.hxx,v 1.8 2009/06/04 02:36:32 williw Exp $
// $Source: /usr/local/cvs/archive/sys_mgmt/src/kernel/Attic/cl_basic_thread.hxx,v $ 
//
#ifndef _CL_BASIC_THREAD_HXX_
#define _CL_BASIC_THREAD_HXX_

#include <pthread.h>
#include <string>

class CLBasicThread
{
    public:
        enum threadState
        {
            NOT_RUNNING,
            RUNNING
        };

        enum threadFrequency
        {
            ONCE,
            PERIODIC
        };

        CLBasicThread(const char* name, threadFrequency tfreq, int interval = 0);
        virtual ~CLBasicThread();

        // Start
        void start();
        // Stop
        void stop();
        // Wakeup
        void wakeup();
        // Terminate
        void terminate();
        // identity of thread
        const char* getName() const { return m_sName.c_str(); }
        bool isCurThread(void) { return pthread_equal(pthread_self(),m_thr); }
        bool hasExited() { return m_bExit; }
    protected:

        // The entry point of this thread should be implemented by every derived thread.
        virtual void run() = 0;

    private:
        // The main entry point for each thread
        void base_run(void);

        // watchdog or other similar service will use this to toggle the state
        // and then restart it if necessary
        void setState(threadState ts){ m_thrState = ts ;}

        // Interface to send a signal to this thread.
        void sendSignal( int signal );

        // interface to start this thread.
        static void* thread_start( void* arg );

        // data members.
    private:
        pthread_t       m_thr;
        pthread_attr_t  m_thr_attr;
        std::string     m_sName;
        threadState     m_thrState;
        threadState     m_thrSubState;
        int                  m_iRunInterval;
        bool               m_bStop;
        threadFrequency    m_threadFrequency;
        bool               m_bExit;
};

#endif // _CL_BASIC_THREAD_HXX_



