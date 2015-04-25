//Copyright (C) 2015 All Rights Reserved, by
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
// System Management Framework: replication V2
//
// ABSTRACT:
//
// This class extends the basic thread to create a thread whose job it is
// to run a replication v2 restore task
//
// AUTHORS:
//
// Shaocong Liang
//
// CREATION DATE:
//
// 04/12/2015
//
// MODIFICATION HISTORY:
//
//
// VERSION:
//
// $Id: rep_restore_thread.hxx,v 1.0 2015/003/12 Exp $
// 
//
#ifndef _REP_RESTORE_THREAD_H_
#define _REP_RESTORE_THREAD_H_

// standard includes
#include <time.h>
#include <string>
// file includes
#include "basic_thread.hxx"
#include <pthread.h>
// class includes

class RepRestoreThread : public CLBasicThread
{
    public:
        // ctor
        RepRestoreThread(const char* name, std::string str);

        // dtor
        virtual ~RepRestoreThread();

        // from base class: main entry point for thread
        virtual void run();

        // debugging aid
        std::string& dumpstats(std::string& str) const;

        std::string ssystem(const char *command);

    private:
        bool m_bFree;

        // Members for statistics gathering
        //  From man times(2)
        //        The number of clock ticks per second can be obtained using
        //      sysconf(_SC_CLK_TCK);
        clock_t m_Runstart;    // when thread started running current edge
        clock_t m_Idlestart;   // when thread last went idle
        clock_t m_Maxidle;     // maximum time span spent idle
        clock_t m_Maxproc;     // maximum time span spent processing an edge
        std::string cmdStr;
        std::string argument;
        pthread_mutex_t mutex_;
};
#endif // _REP_RESTORE_THREAD_H_

