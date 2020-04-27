#pragma once
#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Graphic
{
    entt::registry& registry_;
    entt::dispatcher& dispatcher_;
    sf::RenderWindow window_;

public:
    Graphic(entt::registry& registry, entt::dispatcher& dispatcher);
    void step();
};