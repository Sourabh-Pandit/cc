#include <cc/debug>
#include <cc/ui/Application>
#include <cc/ui/SlideView>
#include <cc/ui/Transition>
#include <cc/ui/ColumnLayout>
#include <cc/ui/Label>

using namespace cc;
using namespace cc::ui;

class Slide1: public View
{
    friend class Object;

    Slide1(View *parent):
        View(parent)
    {
        color = Color{"#FFFFFF"};

        Label::create(this, "Press (->)")->centerInParent();
    }
};

class Slide2: public View
{
    friend class Object;

    Slide2(View *parent):
        View(parent)
    {
        color = Color{"#FFFFFF"};

        View *box = View::create(this);
        box->color = Color{"#D0D0FF"};
        box->centerInParent();

        ColumnLayout::setup(box);

        Label::create(box, "• Item 1");
        Label::create(box, "• Item 2");
        Label::create(box, "• Item 3");
    }
};

class MainView: public SlideView
{
    friend class Object;

    MainView()
    {
        size = Size{640, 480};

        Object::create<Slide1>(this);
        Object::create<Slide2>(this);

        easeOn(slideCarrier()->pos, 0.5, easing::Bezier(0.5, -0.4, 0.5, 1.4));
    }

    bool onKeyPressed(const KeyEvent *event) override
    {
        if (event->scanCode() == ScanCode::Key_Left)
        {
            currentIndex -= 1;
        }
        else if (event->scanCode() == ScanCode::Key_Right)
        {
            currentIndex += 1;
        }
        else if ('0' <= +event->keyCode() && +event->keyCode() <= '9')
        {
            currentIndex = +event->keyCode() - '1' + 10 * (+event->keyCode() == '0');
        }

        return true;
    }
};

int main(int argc, char **argv)
{
    Application *app = Application::open(argc, argv);
    Window::open(Object::create<MainView>(), "Hello, world!", WindowMode::Default|WindowMode::Accelerated);
    return app->run();
}
