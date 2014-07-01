/*
 * Copyright (C) 2014 Frank Mertens.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#include <flux/Singleton.h>
#include "elements.h"
#include "MarkupProtocol.h"

namespace flux {
namespace doc {

MarkupProtocol::MarkupProtocol()
{
	define<TitleElement>();
	define<AuthorElement>();
	define<ParagraphElement>();
	define<ListElement>();

	define<PartElement>();
	define<ImageElement>();
	define<CodeElement>();
}

const MarkupProtocol *markupProtocol() { return Singleton<MarkupProtocol>::instance(); }

}} // namespace flux::doc