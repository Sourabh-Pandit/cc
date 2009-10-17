/*
 * SignalManager.hpp -- signal handling
 *
 * Copyright (c) 2007-2009, Frank Mertens
 *
 * See ../LICENSE for the license.
 */
#ifndef PONA_SIGNALMANAGER_HPP
#define PONA_SIGNALMANAGER_HPP

#include <signal.h>
#include "atoms"
#include "Mutex.hpp"
#include "Thread.hpp"
#include "Process.hpp"
#include "Map.hpp"
#include "Event.hpp"

namespace pona
{

class SignalInitializer {
public:
	SignalInitializer();
private:
	static int count_;
};

namespace { SignalInitializer signalInitializer_; }

class SignalListener: public Thread {
public:
	SignalListener();
	void run();
	Mutex done_;
};

class SignalManager: public Instance
{
	PONA_SHARED
	
public:
	static Ref<SignalManager> instance();
	
	Ref<Event> signalEvent(int signal);
	
	static void defaultAction(int signal);
	
private:
	friend class SignalInitializer;
	friend class SignalListener;
	
	SignalManager();
	~SignalManager();
	
	void startListener();
	void relay(int signal);
	
	Ref<SignalListener, Owner> signalListener_;
	int pid_;
	
	typedef Map<int, Ref<Event, Owner> > SignalEvents;
	Ref<SignalEvents, Owner> signalEvents_;
};

Ref<Event> signalEvent(int signal);

} // namespace pona

#endif // PONA_SIGNALMANAGER_HPP
