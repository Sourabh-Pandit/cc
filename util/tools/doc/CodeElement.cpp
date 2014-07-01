/*
 * Copyright (C) 2014 Frank Mertens.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#include <flux/stdio.h>
#include <flux/toki/Registry.h>
#include "CodeElement.h"

namespace flux {
namespace doc {

CodeElement::CodeElement(String className)
	: PathElement(className)
{}

void CodeElement::define()
{
	PathElement::define();
	insert("language", "");
}

void CodeElement::realize(const ByteArray *text, Token *objectToken)
{
	PathElement::realize(text, objectToken);
	String name = value("language");
	if (name != "") {
		toki::Language *language = 0;
		if (toki::registry()->lookupLanguageByName(name, &language)) {
			language_ = language;
		}
		else {
			int n = toki::registry()->languageCount();
			for (int i = 0; i < n; ++i) {
				toki::Language *candidate = toki::registry()->languageAt(i);
				if (candidate->displayName()->downcase() == name) {
					language_ = candidate;
					break;
				}
			}
			if (!language_) {
				int offset = valueToken(text, objectToken, "language")->i1();
				ferr() << SemanticError(Format("Unknown language \"%%\"") << name, text, offset) << nl;
			}
		}
	}
}

Ref<MetaObject> CodeElement::produce()
{
	return CodeElement::create();
}

}} // namespace flux::doc
