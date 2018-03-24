#include <cc/stdio>
#include <cc/ui/Application>
#include <cc/ui/Transition>

using namespace cc;
using namespace cc::ui;

class TestView: public View
{
    friend class Object;

    TestView()
    {
        size = Size{640, 480};
        color = Color{"#FFFFFF"};

        clicked->connect([=]{
            fout() << "Clicked at " << mousePos() << nl;
            angle += 45;
        });

        Transition<double>::create(angle, 0.5);
    }

    void paint() override
    {
        Painter p(this);

        p->translate(center());
        p->setSource(Color{"#0080FFFF"});
        p->rectangle(-Point{50, 50}, Size{100, 100});
        p->fill();
    }
};

int main(int argc, char **argv)
{
    Application *app = Application::open(argc, argv);
    Window::open(Object::create<TestView>(), "Click me!", WindowMode::Default|WindowMode::InputFocus);
    return app->run();
}
