#pragma once
#include <entt/entt.hpp>
#include <Event/UserInput.hpp>

class Engine
{
    inline static const int FIELD_WIDTH = 200;
    inline static const int FIELD_HEIGHT = 200;
    entt::registry& registry_;
    entt::dispatcher& dispatcher_;
    bool is_out_of_field();
    bool is_collide_food();
    USERINPUT input_;
    void on_input(USERINPUT input);
public:
    Engine(entt::registry& registry, entt::dispatcher& dispatcher);
    void step();

};