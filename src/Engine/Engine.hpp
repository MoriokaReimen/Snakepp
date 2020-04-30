#pragma once
#include <entt/entt.hpp>
#include <Event/UserInput.hpp>
#include <chrono>

class Engine
{
    inline static const int FIELD_WIDTH = 40;
    inline static const int FIELD_HEIGHT = 40;
    entt::registry &registry_;
    entt::dispatcher &dispatcher_;
    bool is_out_of_field();
    bool is_collide_food();
    bool is_overwrap();
    USERINPUT input_;
    void on_input(USERINPUT input);
    void update_position(const entt::entity &head_entity);
    void consume_food(const entt::entity &head_entity);
    std::chrono::system_clock::time_point last_update_;

public:
    Engine(entt::registry &registry, entt::dispatcher &dispatcher);
    void step();
};