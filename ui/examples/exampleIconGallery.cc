#include <cc/debug>
#include <cc/ui/Application>
#include <cc/ui/ItemView>
#include <cc/ui/Column>
#include <cc/ui/SingleLineItemDelegate>

using namespace cc;
using namespace cc::ui;

class IconItem: public Item
{
    friend class Object;

public:
    Icon icon() const { return icon_; }

private:
    IconItem(Icon icon): icon_{icon} {}

    Icon icon_;
};

class IconModel: public Item
{
    friend class Object;

    IconModel()
    {
        for (int i = +Icon::FirstIcon; i <= +Icon::LastIcon; ++i)
            add<IconItem>(static_cast<Icon>(i));
    }
};

class IconView: public ItemView
{
    friend class Object;

    IconView(View *parent, IconModel *model):
        ItemView{parent, model}
    {}

    View *addDelegate(View *parent, Item *item) override
    {
        IconItem *iconItem = Object::cast<IconItem *>(item);
        return parent->add<SingleLineItemDelegate>(str(iconItem->icon()), style()->getIconVisual(iconItem->icon()));
    }
};

class MainView: public View
{
    friend class Object;

    MainView()
    {
        size = Size{1280, 1080};
        inheritPaper();

        /*auto scroll = add<ScrollView>();

        int j = 0;
        for (int i = +Icon::FirstIcon; i <= +Icon::LastIcon && j < 50; ++i, ++j) {
            Icon icon = static_cast<Icon>(i);
            scroll->carrier()->add<SingleLineItemDelegate>(str(icon), style()->getIconVisual(icon));
        }

        scroll->carrier()->organize<Column>();*/

        auto scroll = add<IconView>(
            Object::create<IconModel>()
        );

        scroll->clicked->connect([=]{
            CC_INSPECT(scroll->currentRow());
        });

        CC_INSPECT(scroll->carrier()->size());
        CC_INSPECT(scroll->rowCount());
    }
};

int main(int argc, char **argv)
{
    auto app = Application::open(argc, argv);
    if (argc == 2 && String(argv[1])->contains("fullscreen")) {
        // app->cursorVisible = false;
        Window::open<MainView>(/*WindowMode::Accelerated|*/WindowMode::Fullscreen|WindowMode::VSync);
    }
    else
        Window::open<MainView>(/*WindowMode::Accelerated|*/WindowMode::VSync);
    return app->run();
}
