#include <Engine/Engine.hpp>
#include <Components/Head.hpp>
#include <Components/Body.hpp>
#include <Components/Food.hpp>
#include <Components/Position.hpp>

#include <Event/GameOver.hpp>

Engine::Engine(entt::registry &registry, entt::dispatcher& dispatcher)
    : registry_(registry),
      dispatcher_(dispatcher)
{
    // add head to snake
    auto head_entity = registry_.create();
    registry_.assign<Position>(head_entity, 0, 0);
    registry_.assign<Head>(head_entity, Head());
    dispatcher_.sink<USERINPUT>().connect<&Engine::on_input>(this);
}

void Engine::step()
{
    auto view = registry_.view<Head>();
    for (auto head_entity : view)
    {
        auto &head_position = registry_.get<Position>(head_entity);

        const Head &head = registry_.get<Head>(head_entity);
        if (!head.bodies.empty())
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
        if (is_collide_food())
        {
            if (!head.bodies.empty())
            {
                auto last_entity = head.bodies[head.bodies.size() - 1];
                Position tail_pos = registry_.get<Position>(last_entity);

            } else {
                Position tail_pos = head_position;
            }
        }

        if (is_out_of_field())
        {
            dispatcher_.trigger<GameOver>();
        }
    }
}

bool Engine::is_out_of_field()
{
    auto head_view = registry_.view<Head>();
    for (auto head_entity : head_view)
    {
        auto &head_position = registry_.get<Position>(head_entity);
        if (0 <= head_position.x && head_position.x <= FIELD_WIDTH &&
            0 <= head_position.y && head_position.y <= FIELD_HEIGHT)
            return true;
    }

    return false;
}

bool Engine::is_collide_food()
{
    auto head_view = registry_.view<Head>();
    for (auto head_entity : head_view)
    {
        auto &head_position = registry_.get<Position>(head_entity);
        for (auto food_entity : registry_.view<Position, Food>())
        {
            auto food_position = registry_.get<Position>(food_entity);
            if (head_position == food_position)
            {
                return true;
            }
        }
    }

    return false;
}

void Engine::on_input(USERINPUT input)
{
    this->input_ = input;
}