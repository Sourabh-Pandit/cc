#include <cc/ui/Application>
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
        margin = dp(20);
    }
};

class MainView: public View
{
    friend class Object;

    MainView()
    {
        size = Size{640, 480};
        paper = 0xFFFFFF;

        auto box = add<View>();
        box->paper = 0xD0D0FF;
        box->centerInParent();

        box->organize<Column>();

        box->add<Item>("• Item 1");
        box->add<Item>("• Item 2");
        box->add<Item>("• Item 3");

        {
            auto subBox = box->add<View>();
            subBox->paper = 0xD0FFD0;

            subBox->organize<Column>()
                ->indent->bind([=]{
                    return style()->defaultFont()->size();
                });

            subBox->add<Item>("• Item A");
            subBox->add<Item>("• Item B");
            subBox->add<Item>("• Item C"); // ◦
        }
    }
};

int main(int argc, char **argv)
{
    auto app = Application::open(argc, argv);
    Window::open<MainView>("Hello, world!", WindowMode::Accelerated|WindowMode::VSync);
    return app->run();
}
