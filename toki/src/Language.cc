/*
 * Copyright (C) 2007-2016 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#include <cc/toki/Registry>
#include <cc/toki/Language>

namespace cc {
namespace toki {

Language::Language(
    String displayName,
    RegExp pathPattern,
    const SyntaxDefinition *highlightingSyntax,
    const SyntaxDefinition *discoverySyntax,
    const SyntaxDefinition *foldingSyntax
)
    : displayName_(displayName),
      name_(highlightingSyntax->name()),
      pathPattern_(pathPattern),
      highlightingSyntax_(highlightingSyntax),
      discoverySyntax_(discoverySyntax),
      foldingSyntax_(foldingSyntax)
{
    registry()->registerLanguage(this);
}

}} // namespace cc::toki