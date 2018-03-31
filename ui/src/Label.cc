/*
 * Copyright (C) 2018 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#include <cc/ui/TextRun>
#include <cc/ui/StylePlugin>
#include <cc/ui/Label>

namespace cc {
namespace ui {

Ref<Label> Label::create(View *parent, String text, const TextStyle *textStyle)
{
    return Object::create<Label>(parent, text, textStyle);
}

Label::Label(View *parent, String text_, const TextStyle *textStyle_):
    View(parent),
    text(text_)
{
    if (textStyle_) textStyle = textStyle_;
    else textStyle->bind([=]{ return StylePlugin::instance()->defaultTextStyle(); });

    margin->bind([=]{ return StylePlugin::instance()->defaultTextMargin(); });

    color = transparent;

    updateLayout();

    text     ->connect([=]{ updateLayout(); });
    textStyle->connect([=]{ updateLayout(); });
    margin   ->connect([=]{ updateSize(); });
    size     ->connect([=]{ update(); });
}

void Label::updateLayout()
{
    textRun_ = TextRun::create(
        text(),
        textStyle()
    );

    updateSize();
    update();
}

void Label::updateSize()
{
    size = textRun_->size() + 2 * margin();
}

void Label::paint()
{
    Painter(this)->showTextRun(
        center() + 0.5 * Step { -textRun_->size()[0], textRun_->size()[1] },
        textRun_
    );
}

}} // namespace cc::ui