#include <cc/debug>
#include <cc/ui/Application>
#include <cc/ui/ScrollView>
#include <cc/ui/Column>
#include <cc/ui/Label>

using namespace cc;
using namespace cc::ui;

class Item: public Label
{
    friend class Object;

    Item(View *parent, const String &text):
        Label(parent, text)
    {
        margin = Size{20};
    }
};

class MainView: public View
{
    friend class Object;

    MainView()
    {
        size = Size{640, 480};
        inheritPaper();

        auto scroll = add<ScrollView>();

        scroll->carrier()->organize<Column>();

        for (int i = 0; i < 50; ++i)
            scroll->carrier()->add<Item>("Item " + str(i + 1));
    }
};

int main(int argc, char **argv)
{
    auto app = Application::open(argc, argv);
    Window::open<MainView>("Hello, world!", WindowMode::Accelerated|WindowMode::VSync);
    return app->run();
}
