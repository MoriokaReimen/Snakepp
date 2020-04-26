#include <Engine/Engine.hpp>
#include <Components/Head.hpp>
#include <Components/Body.hpp>
#include <Components/Food.hpp>
#include <Components/Position.hpp>

Engine::Engine(entt::registry &registry)
    : registry_(registry)
{
    // add head to snake
    auto head_entity = registry_.create();
    registry_.assign<Position>(head_entity, 0, 0);
    registry_.assign<Head>(head_entity, Head());
}

void Engine::step()
{
    auto view = registry_.view<Head>();
    for (auto head_entity : view)
    {
        auto& head_position = registry_.get<Position>(head_entity);
        


        const Head &head = registry_.get<Head>(head_entity);
        if(!head.bodies.empty())
        {
            auto body_entity = head.bodies[0];
            auto &body_position = registry_.get<Position>(body_entity);
            body_position = head_position;
        }

        for (int i = 1; i < head.bodies.size(); i++)
        {
            auto body_entity = head.bodies[i];
            auto last_body_entity = head.bodies[i - 1];
            const auto &last_position = registry_.get<Position>(last_body_entity);
            auto &position = registry_.get<Position>(body_entity);
            position = last_position;
        }
    }
}

bool Engine::is_out_of_field()
{
    auto head_view = registry_.view<Head>();
    for (auto head_entity : head_view)
    {
        auto &head_position = registry_.get<Position>(head_entity);
        for(auto food_entity : registry_.view<Position, Food>())
        {
            auto food_position = registry_.get<Position>(food_entity);
            if(food_position.x == head_position.x && food_position.y == head_position.y)
            {
                return true;
            }
        }
    }

    return false;
}

bool Engine::is_collide_food()
{
    auto head_view = registry_.view<Head>();
    for (auto head_entity : head_view)
    {
        auto &head_position = registry_.get<Position>(head_entity);
        for(auto food_entity : registry_.view<Position, Food>())
        {
            auto food_position = registry_.get<Position>(food_entity);
            if(head_position == food_position)
            {
                return true;
            }
        }
    }

    return false;
}