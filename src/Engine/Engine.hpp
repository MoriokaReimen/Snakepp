#pragma once
#include <entt/entt.hpp>

class Engine
{
    entt::registry& registry_;
    bool is_out_of_field();
    bool is_collide_food();
public:
    Engine(entt::registry& registry);
    void step();

};