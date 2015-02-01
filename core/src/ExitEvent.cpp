/*
 * Copyright (C) 2007-2015 Frank Mertens.
 *
 * Use of this source is governed by a BSD-style license that can be
 * found in the LICENSE file.
 *
 */

#include <flux/Singleton>
#include <flux/ExitEvent>

namespace flux {

ExitEvent::ExitEvent()
    : pid_(Process::currentId())
{}

ExitEvent::~ExitEvent()
{
    if (Process::currentId() == pid_) run();
}

ExitEvent *exitEvent() { return Singleton<ExitEvent>::instance(); }

} // namespace flux
