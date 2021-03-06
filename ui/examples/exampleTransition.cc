#include <cc/stdio>
#include <cc/ui/Application>
#include <cc/ui/Control>
#include <cc/ui/Transition>
#include <cc/ui/colors>

using namespace cc;
using namespace cc::ui;

class MainView: public Control
{
    friend class Object;

    MainView()
    {
        size = Size{640, 480};
        paper = Material::White;

        // easeOn(angle, 0.5, easing::outElastic);
        easeOn(angle, 0.5, easing::Bezier(0.5, -0.4, 0.5, 1.4));
    }

    void paint() override
    {
        Painter p(this);

        p->translate(center());
        p->setSource(Material::Blue500);
        p->rectangle(-Point{50, 50}, Size{100, 100});
        p->fill();
    }

    bool onPointerClicked(const PointerEvent *event) override
    {
        fout() << "Clicked at " << event->pos() << nl;
        angle += 45;
        return true;
    }
};

int main(int argc, char **argv)
{
    auto app = Application::open(argc, argv);
    Window::open<MainView>("Click me!", WindowMode::Accelerated|WindowMode::VSync);
    return app->run();
}
