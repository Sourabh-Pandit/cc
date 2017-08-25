/*
 * Copyright (C) 2007-2017 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#pragma once

#include <cc/HashSink>

namespace cc {
namespace crypto {

/** \class Md5Sink Md5Sink.h cc/crypto/Md5Sink
  * \brief Message Digest 5: a one-way hash function
  */
class Md5Sink: public HashSink
{
public:
    enum {
        Size = 16 ///< size of the hash sum in bytes
    };

    /** Open a new MD5 sum computing hash sink
      * \return new object instance
      */
    static Ref<Md5Sink> open();

    virtual void write(const ByteArray *data) override;
    virtual Ref<ByteArray> finish() override;

private:
    Md5Sink();
    void consume();

    Ref<ByteArray> aux_;
    int auxFill_;
    uint64_t bytesFeed_;
    uint32_t a_, b_, c_, d_;
};

Ref<ByteArray> md5(const ByteArray *data);

}} // namespace cc::crypto