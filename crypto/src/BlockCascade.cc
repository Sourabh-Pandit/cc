/*
 * Copyright (C) 2007-2016 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#include <cc/crypto/BlockCascade>

namespace cc {
namespace crypto {

Ref<BlockCascade> BlockCascade::create(BlockCipher *cipher, ByteArray *iv)
{
    return new BlockCascade(cipher, iv);
}

BlockCascade::BlockCascade(BlockCipher *cipher, ByteArray *iv):
    BlockCipher(cipher->blockSize()),
    cipher_(cipher),
    s_(ByteArray::allocate(cipher->blockSize()))
{
    s_->clear();
    if (iv) *s_ = *iv;
}

void BlockCascade::encode(ByteArray *p, ByteArray *c)
{
    *s_ ^= *p;
    cipher_->encode(s_, c);
    *s_ = *c;
}

void BlockCascade::decode(ByteArray *c, ByteArray *p)
{
    cipher_->decode(c, p);
    *p ^= *s_;
    *s_ = *c;
}

}} // namespace cc::crypto