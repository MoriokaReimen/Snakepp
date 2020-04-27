#pragma once
#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Event/GameOver.hpp>

class Graphic
{
    entt::registry& registry_;
    entt::dispatcher& dispatcher_;
    sf::RenderWindow window_;
    bool is_gameover_;
    void draw_schene();
    void draw_gameover();
    void on_gameover(const GameOver& gameover);

public:
    Graphic(entt::registry& registry, entt::dispatcher& dispatcher);
    void step();
};