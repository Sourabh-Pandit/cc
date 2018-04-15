/*
 * Copyright (C) 2018 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#include <cc/debug>
#include <cc/System>
#include <cc/ui/easing>
#include <cc/ui/Timer>
#include <cc/ui/ScrollView>

namespace cc {
namespace ui {

Ref<ScrollView> ScrollView::create(View *parent)
{
    return Object::create<ScrollView>(parent);
}

ScrollView::ScrollView(View *parent):
    View(parent),
    carrier_(0),
    isDragged_(false),
    timer_(Timer::create(1./60))
{
    carrier_ = View::create(this);

    if (parent) size->bind([=]{ return parent->size(); });

    size->connect([=]{
        carrier_->pos = carrierStep(carrier_->pos());
    });

    timer_->triggered->connect([=]{
        if (timerMode_ == TimerMode::Flying) carrierFly();
        else if (timerMode_ == TimerMode::Bouncing) carrierBounce();
    });
}

void ScrollView::insertChild(View *child)
{
    if (carrier_)
        adoptChild(carrier_, child);
    else
        View::insertChild(child);
}

bool ScrollView::onPointerPressed(const PointerEvent *event)
{
    dragStart_ = event->pos();
    isDragged_ = false;
    speed_ = Point{};
    if (timer_->isActive()) carrierStop();
    return false;
}

bool ScrollView::onPointerReleased(const PointerEvent *event)
{
    if (isDragged_) {
        if (System::now() - lastDragTime_ > minHoldTime()) speed_ = Point{};
        isDragged_ = false;
    }
    if (carrierInsideBoundary()) {
        carrierBounceStart();
    }
    else if (speed_ != Step{}) {
        timerMode_ = TimerMode::Flying;
        timer_->start();
        lastTime_ = timer_->startTime();
        double v = abs(speed_);
        if (v > maxSpeed()) speed_ *= maxSpeed() / v;
        releaseSpeedMagnitude_ = abs(speed_);
    }
    return false;
}

bool ScrollView::onPointerMoved(const PointerEvent *event)
{
    if (
        !isDragged_ &&
        absPow2(event->pos() - dragStart_) >= minDragDistance() * minDragDistance()
    ) {
        isDragged_ = true;
        carrierOrigin_ = carrier_->pos();
        lastDragTime_ = 0;
    }

    if (isDragged_) {
        double t = System::now();
        if (lastDragTime_ > 0)
            speed_ = (lastDragPos_ - event->pos()) / (t - lastDragTime_);
        lastDragTime_ = t;
        lastDragPos_ = event->pos();

        Step d = event->pos() - dragStart_;
        Point p = carrierOrigin_ + d;

        carrier_->pos = carrierStep(p, boundary());
    }

    return true;
}

bool ScrollView::carrierInsideBoundary() const
{
    double x = carrier_->pos()[0];
    double y = carrier_->pos()[1];
    double w = carrier_->size()[0];
    double h = carrier_->size()[1];

    return
        (w > size()[0] && (x > 0 || x + w < size()[0])) ||
        (h > size()[0] && (y > 0 || y + h < size()[1]));
}

Point ScrollView::carrierStep(Point p, double b)
{
    double x = p[0];
    double y = p[1];
    double w = carrier_->size()[0];
    double h = carrier_->size()[1];

    if (w > size()[0]) {
        if (x > b) x = b;
        else if (x + w < size()[0] - b) x = size()[0] - b - w;
    }
    else x = 0;

    if (h > size()[1]) {
        if (y > b) y = b;
        else if (y + h < size()[1] - b) y = size()[1] - b - h;
    }
    else y = 0;

    return Point{ x, y };
}

void ScrollView::carrierFly()
{
    double t = System::now();
    double T = t - lastTime_;
    lastTime_ = t;
    Step d = -speed_ * T;
    double va = 0; {
        if (speed_[0] == 0) va = std::abs(speed_[1]);
        else if (speed_[1] == 0) va = std::abs(speed_[0]);
        else va = cc::abs(speed_);
    }
    double vb = va - (T / maxFlyTime()) * releaseSpeedMagnitude_;
    if (vb <= 0) vb = 0;
    speed_ *= vb / va;

    Point pa = carrier_->pos();
    Point pb = carrierStep(carrier_->pos() + d, boundary());
    if (pa == pb || speed_ == Step{}) {
        carrierStop();
        if (carrierInsideBoundary())
            carrierBounceStart();
    }
    else
        carrier_->pos = pb;
}

void ScrollView::carrierBounce()
{
    const double t0 = timer_->startTime();
    const double t1 = t0 + maxBounceTime();
    const double t = System::now();

    if (t >= t1) {
        carrier_->pos = bounceFinalPos_;
        carrierStop();
        return;
    }

    double s = easing::outBounce((t - t0) / (t1 - t0));
    carrier_->pos = (1 - s) * bounceStartPos_ + s * bounceFinalPos_;
}

void ScrollView::carrierBounceStart()
{
    timerMode_ = TimerMode::Bouncing;
    timer_->start();
    bounceStartPos_ = carrier_->pos();
    bounceFinalPos_ = carrierStep(carrier_->pos());
}

void ScrollView::carrierStop()
{
    timer_->stop();
    timerMode_ = TimerMode::Stopped;
}

}} // namespace cc::ui