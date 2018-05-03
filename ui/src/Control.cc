/*
 * Copyright (C) 2018 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#include <cc/ui/Control>

namespace cc {
namespace ui {

Control::Control(View *parent):
    View(parent)
{
    hover->bind([=]{ return isParentOfOrEqual(app()->hoverControl()); });
    pressed->bind([=]{ return isParentOfOrEqual(app()->pressedControl()); });
    focus->bind([=]{ return isParentOfOrEqual(app()->focusControl()); });
}

Rect Control::textInputArea() const
{
    return Rect{ Point{}, size() };
}

void Control::onTextEdited(const String &text, int start, int length)
{}

void Control::onTextInput(const String &text)
{}

}} // namespace cc::ui
