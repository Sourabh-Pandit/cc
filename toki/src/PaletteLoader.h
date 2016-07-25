/*
 * Copyright (C) 2007-2016 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#pragma once

#include <cc/toki/Palette>

namespace cc {

template<class> class Singleton;

namespace toki {

class PaletteLoader: public Object
{
public:
    Ref<Palette> load(String path) const;

private:
    friend class Singleton<PaletteLoader>;
    PaletteLoader();

    Ref<MetaProtocol> protocol_;
};

const PaletteLoader *paletteLoader();

}} // namespace cc::toki

