// Copyright (C) 2006, All Rights Reserved, by
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
// EMC assumes no responsibility for the use or  reliability  of its
// software on equipment which is not supplied by EMC.
//
//
// FACILITY:
//
// Celerra Command Service Thread Pool
//
// ABSTRACT:
//
// ***abstract text***
//
// AUTHORS:
//
//  Norm Speciner
//  Karthik Srinivasan
//
// CREATION DATE:
//
//  15-July-2006
//
// MODIFICATION HISTORY:
//
// Log information available via 'cvs log'
//
// VERSION:
//
// $Id: cl_thread_pool.hxx,v 1.5 2010/02/20 01:55:51 williw Exp $
// $Source: /usr/local/cvs/archive/System_Common/sc_smf/src/utils/cl_thread_pool.hxx,v $
//

#ifndef _CL_THREAD_POOL_HXX_
#define _CL_THREAD_POOL_HXX_

#include <vector>

// class includes
class CLBasicThread;
typedef std::vector<CLBasicThread*> ThreadArray;

class CLThreadPool
{
    public:
        CLThreadPool();
        virtual ~CLThreadPool();

        // add thread to the pool.
        void addThread( CLBasicThread *);

        // Thread access routines
        const ThreadArray& getThreadList() const;

        void startThreads();
        void stopThreads();
        void deleteThreads();

        // find current thread in thread pool
        CLBasicThread* findThread(void);

    private:
        ThreadArray threads;
};

#endif //_THREAD_POOL_HXX_

