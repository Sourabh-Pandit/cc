/*
 * Copyright (C) 2007-2016 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#include <cc/SubProcess>
#include "JobServer.h"

namespace ccbuild {

JobServer::JobServer(JobChannel *requestChannel, JobChannel *replyChannel):
    requestChannel_(requestChannel),
    replyChannel_(replyChannel)
{
    Thread::start();
}

JobServer::~JobServer()
{
    requestChannel_->pushFront(0);
    Thread::wait();
}

void JobServer::run()
{
    while (true) {
        Ref<Job> job = requestChannel_->popFront();
        if (!job) break;
        Ref<SubProcess> sub = SubProcess::open(job->command_);
        job->outputText_ = sub->readAll();
        job->status_ = sub->wait();
        replyChannel_->pushBack(job);
    }
}

} // namespace ccbuild
