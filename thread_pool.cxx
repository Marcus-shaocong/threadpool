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
//  Celerra Command Service Daemon Thread Pool
//
// ABSTRACT:
//
//  <abstract>
//
// AUTHORS:
//
//  Karthik Srinivasan
//
// CREATION DATE:
//
//
//
// MODIFICATION HISTORY:
//
//  Log information available via 'cvs log'
//
// VERSION:
//
//  $Id: cl_thread_pool.cxx,v 1.5 2010/02/20 01:55:51 williw Exp $
//  $Source: /usr/local/cvs/archive/System_Common/sc_smf/src/utils/cl_thread_pool.cxx,v $
//


#include "thread_pool.hxx"

#include "basic_thread.hxx"

#include <assert.h>
#include <stdio.h>
#include <unistd.h> // Sleep is defined here.

CLThreadPool::CLThreadPool()
{
}

CLThreadPool::~CLThreadPool()
{
}

void CLThreadPool::startThreads()
{
    ThreadArray::const_iterator iter = threads.begin();

    for( ; iter != threads.end(); ++iter )
    {
        CLBasicThread * thr = *iter;
        if( thr != NULL )
        {
            thr->start();
        }
        else
        {
        }
    }
}

void CLThreadPool::stopThreads()
{
    ThreadArray::const_iterator iter = threads.begin();
    for( ; iter != threads.end(); ++iter )
    {
        CLBasicThread * thr = *iter;
        if( thr != NULL )
        {
            thr->stop();
        }
    }
}

void CLThreadPool::addThread( CLBasicThread* clb )
{

    assert( clb != NULL);
    threads.push_back(clb);
}

void CLThreadPool::deleteThreads()
{
    ThreadArray::iterator iter;
    int iSleep = 0;
    bool stopped = false;

    while(!stopped && iSleep < 10)
    {
        stopped = true;
        iSleep++;
        sleep(1);
        for( iter = threads.begin(); iter != threads.end(); ++iter )
        {
            CLBasicThread *thr = *iter;
            if (!thr->hasExited())
            {
                stopped = false;
                break;
            }
        }
    }

    for( iter = threads.begin(); iter != threads.end(); ++iter )
    {
        CLBasicThread *thr = *iter;
        if( thr != NULL )
        {
            if (thr->hasExited())
                delete thr;
        }
    }
}

const ThreadArray& CLThreadPool::getThreadList()
    const
{
    return threads;
}

CLBasicThread* CLThreadPool::findThread(void)
{
    ThreadArray::const_iterator iter = threads.begin();

    for( ; iter != threads.end(); ++iter )
    {
        CLBasicThread * thr = *iter;
        if( thr != NULL )
        {
            if
                (thr->isCurThread())
                {
                    return  thr;
                }
        }
    }

    return NULL;
}

