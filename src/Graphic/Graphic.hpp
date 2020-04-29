#pragma once
#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Event/GameOver.hpp>
#include <ResourceManager/ResourceManger.hpp>

class Graphic
{
    entt::registry& registry_;
    entt::dispatcher& dispatcher_;
    sf::RenderWindow window_;
    bool is_gameover_;
    void draw_schene();
    void draw_gameover();
    void on_gameover(const GameOver& gameover);
    ResMng::ResMng resource_;

public:
    Graphic(entt::registry& registry, entt::dispatcher& dispatcher);
    void step();
};