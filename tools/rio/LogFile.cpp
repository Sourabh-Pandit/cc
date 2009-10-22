/*
 * LogFile.cpp -- transfer and connection logging
 *
 * Copyright (c) 2007-2009, Frank Mertens
 *
 * See ../../LICENSE for the license.
 */

#include "Options.hpp"
#include "LogFile.hpp"

namespace rio
{

LogFile::LogFile(Ref<SocketAddress> address, int type, Time t0, Ref<LogFile> merged)
	: address_(address),
	  type_(type),
	  merged_(merged)
{
	if ((options()->loggingFlags_ & type) != 0)
	{
		String addressString = address->addressString();
		addressString->replace('.', '-');
		
		const char* names[] = {"connect", "recv", "send", "merged", "echo" };
		int typeIndex = 0; while (type > 1) { type /= 2; ++typeIndex; }
		
		String path = Format("%%/%%_%%_%%_%%.log")
			<< options()->logDir_
			<< t0.ms()
			<< addressString
			<< address->port()
			<< names[typeIndex];
		
		file_ = new File(path);
		file_->create();
		file_->open(File::Write);
		lineSink_ = new LineSink(file_);
	}
}

void LogFile::writeLine(Ref<SocketAddress> address, String data)
{
	String line = data;
	
	if (type_ == Connect) {
		line = Format("%%: %%: %%:%%")
			<< now().ms()
			<< data
			<< address->addressString()
			<< address->port();
		
		if (!bool(options()->quiet_))
			error()->writeLine(line);
	}
	
	if (lineSink_)
		lineSink_->writeLine(line);
	
	if (merged_)
	{
		if ((type_ == Recv) || (type_ == Send)) {
			bool client = options()->client_;
			client = (client && (type_ == Send)) || ((!client) && (type_ == Recv));
			if (client)
				line = String("C: ") << data;
			else
				line = String("S: ") << data;
		}
		
		if (merged_)
			merged_->writeLine(address, line);
	}
}

void LogFile::writeLine(String data)
{
	writeLine(address_, data);
}

void LogFile::write(uint8_t* buf, int bufFill)
{
	if (file_)
		file_->write(buf, bufFill);
	if (merged_)
		merged_->write(buf, bufFill);
}

} // namespace rio