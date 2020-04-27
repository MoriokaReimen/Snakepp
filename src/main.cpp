#include <Engine/Engine.hpp>
#include <Graphic/Graphic.hpp>
#include <cstdlib>
#include <entt/entt.hpp>

#include <Event/Close.hpp>

bool is_closed(false);
void on_close(const Close& close);

class MainApp
{
    entt::registry registry_;
    entt::dispatcher dispatcher_;
    Engine engine_;
    Graphic graphic_;
    bool is_closed_;
    void on_close(const Close& close)
    {
        is_closed_ = true;
    }
public:
    MainApp()
        : registry_(), dispatcher_(),
          engine_(registry_, dispatcher_), graphic_(registry_, dispatcher_), is_closed_(false)
    {
        dispatcher_.sink<Close>().connect<&MainApp::on_close>(this);
    }

    bool step()
    {
        engine_.step();
        graphic_.step();

        return is_closed_;
    }

    bool is_closed()
    {
        return is_closed_;
    }
};

int main()
{
    MainApp app;

    while(!app.is_closed())
    {
        app.step();
    }

    return EXIT_SUCCESS;
}
