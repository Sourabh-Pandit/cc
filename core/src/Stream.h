/*
 * Copyright (C) 2007-2016 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#pragma once

#include <cc/String>

namespace cc {

class Format;

/** \class Stream Stream.h cc/Stream
  * \brief Abstract data stream
  */
class Stream: public Object
{
public:
    /** Read N bytes
      * \param data target buffer (N = data->count())
      * \return number of bytes read (<= N)
      * \see ByteArray::select()
      */
    virtual int read(ByteArray *data);

    /** Write N bytes
      * \param data source buffer (N = data->count())
      * \see ByteArray::select()
      */
    virtual void write(const ByteArray *data);

    /** Write multiple buffers atomically ("scatter write")
      * \param parts list of source buffers
      */
    virtual void write(const StringList *parts);

    /// Convenience wrapper
    inline void write(const String &data) { write(data.get()); }

    /// Convenience wrapper
    inline void write(const char *data) { write(String(data)); }

    /// Convenience wrapper
    void write(const Format &format);

    /** Transfer a span of bytes
      * \param count number of bytes to transfer (or -1 for all)
      * \param sink target stream (or null for dump mode)
      * \param buffer auxiliary transfer buffer
      * \return number of bytes transferred
      */
    virtual off_t transferSpanTo(off_t count, Stream *sink, ByteArray *buffer = 0);

    /// Convenience wrapper for transferSpanTo(sink, -1, buffer)
    inline off_t transferTo(Stream *sink, ByteArray *buffer = 0) { return transferSpanTo(-1, sink, buffer); }

    /// Convenience wrapper for transferSpanTo(0, count)
    inline off_t skip(off_t count) { return transferSpanTo(count, 0); }

    /// Convenience wrapper for transferSpanTo(-1, 0)
    inline void drain() { transferSpanTo(-1, 0); }

    /** Read a span of bytes
      * \param count number of bytes to read (or -1 for all)
      * \param data target buffer
      * \return number of bytes read
      */
    int readSpan(int count, ByteArray *data);

    /** Read a fixed number of bytes (N)
      * \param count number of bytes to read (N)
      * \return String of exactly N bytes (padded with zeros if no more data could be read)
      */
    String readSpan(int count);

    /** Read the entire stream
      * \param buffer auxiliary transfer buffer
      * \return all byte read from the stream
      */
    String readAll(ByteArray *buffer = 0);

protected:
    virtual ~Stream() {}
};

} // namespace cc
