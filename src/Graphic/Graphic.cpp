#include <Graphic/Graphic.hpp>
#include <Event/UserInput.hpp>
#include <Components/Head.hpp>
#include <Components/Body.hpp>
#include <Components/Food.hpp>
#include <Components/Position.hpp>

#include <Event/Close.hpp>

Graphic::Graphic(entt::registry &registry, entt::dispatcher &dispatcher)
    : registry_(registry), dispatcher_(dispatcher),
      window_(sf::VideoMode(800, 800), "Snake"), is_gameover_(false)
{
    dispatcher_.sink<GameOver>().connect<&Graphic::on_gameover>(this);
}

void Graphic::step()
{
    sf::Event event;
    while (window_.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            dispatcher_.trigger<Close>();

        if (event.KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::K:
                dispatcher_.trigger<USERINPUT>(UP);
                break;
            case sf::Keyboard::J:
                dispatcher_.trigger<USERINPUT>(DOWN);
                break;
            case sf::Keyboard::L:
                dispatcher_.trigger<USERINPUT>(RIGHT);
                break;
            case sf::Keyboard::H:
                dispatcher_.trigger<USERINPUT>(LEFT);
                break;
            default:
                break;
            }
        }
    }

    window_.clear(sf::Color::White);
    if (is_gameover_)
    {
        draw_gameover();
    }
    else
    {
        draw_schene();
    }
    window_.display();
}

void Graphic::draw_schene()
{
    auto head_view = registry_.view<Head, Position>();

    for (auto entity : head_view)
    {
        auto head_pos = registry_.get<Position>(entity);
        sf::RectangleShape head(sf::Vector2f(20.0, 20.0));
        head.setPosition(head_pos.x * 2, head_pos.y * 2);
        head.setFillColor(sf::Color::Yellow);
        window_.draw(head);
    }

    auto body_view = registry_.view<Body, Position>();

    for (auto entity : body_view)
    {
        auto body_pos = registry_.get<Position>(entity);
        sf::RectangleShape body;
        body.setPosition(body_pos.x * 2, body_pos.y * 2);
        body.setFillColor(sf::Color::Green);
        window_.draw(body);
    }

    auto food_view = registry_.view<Food, Position>();

    for (auto entity : food_view)
    {
        auto food_pos = registry_.get<Position>(entity);
        sf::RectangleShape food;
        food.setPosition(food_pos.x * 2, food_pos.y * 2);
        food.setFillColor(sf::Color::Red);
        window_.draw(food);
    }
}

void Graphic::draw_gameover()
{
}

void Graphic::on_gameover(const GameOver& gameover)
{
    is_gameover_ = true;
}