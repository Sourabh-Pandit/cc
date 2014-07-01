/*
 * Copyright (C) 2014 Frank Mertens.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#include "CxxSyntax.h"
#include "CxxLanguage.h"

namespace flux {
namespace toki {

CxxLanguage::CxxLanguage():
	Language(
		"C++",
		Pattern("*.((h|c){0..1:(pp|xx|++|h|c)}|(m|mm))"),
		cxxSyntax()
	)
{}

}} // namespace flux::toki