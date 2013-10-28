/*
 * Copyright (C) 2007-2013 Frank Mertens.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#ifndef FKIT_PROCESS_H
#define FKIT_PROCESS_H

#include <sys/types.h> // pid_t
#include <signal.h> // SIGTERM, etc.
#include "String.h"
#include "Map.h"
#include "SystemStream.h"
#include "LineSource.h"

namespace fkit
{

class ProcessFactory;

typedef Map<String, String> EnvMap;

FKIT_STD_EXCEPTION(ProcessException);

class Process: public Object
{
public:
	static Ref<Process> start(String command, int ioPolicy = 0);
	static Ref<Process> start(String command, ProcessFactory *factory);

	// -- child process control interface

	enum Type {
		GroupMember,
		GroupLeader,
		SessionLeader
	};

	enum IoPolicy {
		ForwardInput = 1,
		ForwardOutput = 2,
		ForwardError = 4,
		ForwardByPseudoTerminal = 8,
		CloseInput = 16,
		CloseOutput = 32,
		CloseError = 64,
		ErrorToOutput = 128,
		ForwardAll = ForwardInput|ForwardOutput|ForwardError,
		CloseAll = CloseInput|CloseOutput|CloseError
	};

	int type() const;
	int ioPolicy() const;

	SystemStream *in() const;
	SystemStream *out() const;
	SystemStream *err() const;

	LineSource *lineOut();
	LineSource *lineErr();

	pid_t id() const;

	void kill(int signal = SIGTERM, bool *permissionDenied = 0);
	bool isRunning() const;

	int wait();

	// -- query / modify the current process status

	static void cd(String path);
	static String cwd();
	static String execPath();

	static mode_t setFileCreationMask(mode_t mask);

	static uid_t realUserId();
	static gid_t realGroupId();
	static uid_t effectiveUserId();
	static gid_t effectiveGroupId();
	static bool isSuperUser();
	static void setUserId(uid_t uid);

	static String env(String key);
	static void setEnv(String key, String value);
	static void unsetEnv(String key);
	static char **&environ();

	static Ref<EnvMap> envMap();

	static pid_t currentId();
	static pid_t parentId();

	static void kill(pid_t processId, int signal, bool *permissionDenied = 0);
	static void killGroup(pid_t processGroupId, int signal, bool *permissionDenied = 0);
	static void raise(int signal);
	static int alarm(int seconds);

	static void enableInterrupt(int signal, bool on = true);

	static void sleep(double duration);
	static void exit(int exitCode);

	static void daemonize();
	static bool isDaemonized();

protected:
	friend class ProcessFactory;

	Process(
		int type,
		int ioPolicy,
		SystemStream *rawInput,
		SystemStream *rawOutput,
		SystemStream *rawError,
		pid_t processId
	);

	~Process();

private:
	static void forwardSignal(int signal);

	int type_;
	int ioPolicy_;

	Ref<SystemStream> in_;
	Ref<SystemStream> out_;
	Ref<SystemStream> err_;

	Ref<LineSource> lineOut_;
	Ref<LineSource> lineErr_;

	pid_t processId_;
};

} // namespace fkit

#endif // FKIT_PROCESS_H