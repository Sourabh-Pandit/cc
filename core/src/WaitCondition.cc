/*
 * Copyright (C) 2007-2017 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#include <pthread.h>
#include <math.h>
#ifndef NDEBUG
#include <cc/check>
#endif
#include <cc/exceptions>
#include <cc/WaitCondition>

namespace cc {

WaitCondition::WaitCondition()
{
    int ret = pthread_cond_init(&cond_, 0);
    if (ret != 0) CC_SYSTEM_DEBUG_ERROR(ret);
}

WaitCondition::~WaitCondition()
{
    #ifndef NDEBUG
    int ret =
    #endif
    pthread_cond_destroy(&cond_);
    #ifndef NDEBUG
    check(ret == 0);
    #endif
}

/** Enter wait state and atomically unlock provided mutex.
  * The thread will be woken up again and reaquire the mutex atomically
  * if the availability of the condition is signalled (to an arbritary number
  * of threads by signal() or all threads by broadcast()).
  * Note that the first thread scheduled by the OS may invalidate
  * the condition again.
  */
void WaitCondition::wait(Mutex *mutex)
{
    int ret = -1;
    while (true) {
        ret = pthread_cond_wait(&cond_, &mutex->Mutex::mutex_);
        if (ret != EINTR) break;
    }
    if (ret != 0) CC_SYSTEM_DEBUG_ERROR(ret);
}

/** Same as wait(), but also wakeup if system time reaches 'timeout'.
  * (see also: now()). Returns true if the condition was signalled
  * before 'timeout', else returns false.
  */
bool WaitCondition::waitUntil(double timeout, Mutex *mutex)
{
    bool success = true;
    struct timespec ts;
    double sec = 0;
    ts.tv_nsec = modf(timeout, &sec) * 1e9;
    ts.tv_sec = sec;
    int ret = -1;
    while (true) {
        ret = pthread_cond_timedwait(&cond_, &mutex->Mutex::mutex_, &ts);
        if (ret != EINTR) break;
    }
    if (ret != 0) {
        if (ret == ETIMEDOUT)
            success = false;
        else
            CC_SYSTEM_DEBUG_ERROR(ret);
    }
    return success;
}

/** Wakeup at least one waiting thread.
  * (A system might wakeup as many threads as CPU's are idle.)
  */
void WaitCondition::signal()
{
    int ret = pthread_cond_signal(&cond_);
    if (ret != 0) CC_SYSTEM_DEBUG_ERROR(ret);
}

/** Wakeup all waiting threads.
  */
void WaitCondition::broadcast()
{
    int ret = pthread_cond_broadcast(&cond_);
    if (ret != 0) CC_SYSTEM_DEBUG_ERROR(ret);
}

} // namespace cc
