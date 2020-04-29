#include <Engine/Engine.hpp>

#include <random>

#include <Components/Head.hpp>
#include <Components/Body.hpp>
#include <Components/Food.hpp>
#include <Components/Position.hpp>

#include <Event/GameOver.hpp>

static int get_random(const int start, const int end);

Engine::Engine(entt::registry &registry, entt::dispatcher &dispatcher)
    : registry_(registry),
      dispatcher_(dispatcher),
      input_(DOWN)
{
    // add head to snake
    auto head_entity = registry_.create();
    registry_.assign<Position>(head_entity, 0, 0);
    registry_.assign<Head>(head_entity, Head());

    auto food_entity = registry_.create();
    registry_.assign<Position>(food_entity, get_random(0, FIELD_WIDTH), get_random(0, FIELD_HEIGHT));
    registry_.assign<Food>(food_entity, Food());

    dispatcher_.sink<USERINPUT>().connect<&Engine::on_input>(this);
}

void Engine::step()
{
    auto view = registry_.view<Head>();
    for (auto head_entity : view)
    {
        update_position(head_entity);
        Head &head = registry_.get<Head>(head_entity);
        auto &head_position = registry_.get<Position>(head_entity);
        if (is_collide_food())
        {
            if (!head.bodies.empty())
            {
                auto last_entity = head.bodies[head.bodies.size() - 1];
                Position tail_pos = registry_.get<Position>(last_entity);
                auto entity = registry_.create();
                registry_.assign<Position>(entity, tail_pos);
                registry_.assign<Body>(entity, Body());
                head.bodies.push_back(entity);
            }
            else
            {
                Position tail_pos = head_position;
                auto entity = registry_.create();
                registry_.assign<Position>(entity, tail_pos);
                registry_.assign<Body>(entity, Body());
                head.bodies.push_back(entity);
            }

            auto food_view = registry_.view<Position, Food>();
            for (auto food_entity : food_view)
            {
                auto &food_pos = registry_.get<Position>(food_entity);
                food_pos.x = get_random(0, FIELD_WIDTH);
                food_pos.y = get_random(0, FIELD_HEIGHT);
            }
        }

        if (is_out_of_field() || is_overwrap())
        {
            dispatcher_.trigger<GameOver>();
        }
    }
}

void Engine::update_position(const entt::entity &head_entity)
{
    auto &head_position = registry_.get<Position>(head_entity);

    Head &head = registry_.get<Head>(head_entity);

    /* update body postions */
    for (int i = head.bodies.size() - 1; i > 0; i--)
    {
        auto body_entity = head.bodies[i];
        auto last_body_entity = head.bodies[i - 1];
        const auto &last_position = registry_.get<Position>(last_body_entity);
        auto &position = registry_.get<Position>(body_entity);
        position = last_position;
    }
    if (!head.bodies.empty())
    {
        auto body_entity = head.bodies[0];
        auto &body_position = registry_.get<Position>(body_entity);
        body_position = head_position;
    }

    /* update head position */
    switch (input_)
    {
    case UP:
        head_position.y -= 1;
        break;
    case DOWN:
        head_position.y += 1;
        break;
    case LEFT:
        head_position.x -= 1;
        break;
    case RIGHT:
        head_position.x += 1;
        break;
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
            return false;
    }

    return true;
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

bool Engine::is_overwrap()
{
    auto head_view = registry_.view<Head>();
    for (auto head_entity : head_view)
    {
        auto &head_position = registry_.get<Position>(head_entity);
        auto &head = registry_.get<Head>(head_entity);
        for (int i = 1; i < head.bodies.size(); i++)
        {
            auto body_position = registry_.get<Position>(head.bodies[i]);
            if (body_position == head_position)
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

static int get_random(const int start, const int end)
{
    static std::random_device rd;
    static std::mt19937 eng(rd());
    std::uniform_int_distribution<> dist(start, end);

    return dist(eng);
}
