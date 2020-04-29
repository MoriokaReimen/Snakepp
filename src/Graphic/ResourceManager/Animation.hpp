#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace ResMng
{
class Animation
{
    std::vector<sf::IntRect> frames_;
    sf::Texture texture_;

public:
    Animation();
    Animation(const std::string &path);
    Animation(const std::string &path, const std::vector<sf::IntRect> &frames);
    Animation(const void *addr, const size_t size);
    Animation(const void *addr, const size_t size, const std::vector<sf::IntRect> &frames);
    void addFrame(const sf::IntRect &rect);
    bool setSpriteSheet(const void *addr, const size_t size);
    bool setSpriteSheet(const void *addr, const size_t size, const std::vector<sf::IntRect> &frames);
    bool setSpriteSheet(const std::string &path);
    bool setSpriteSheet(const std::string &path, const std::vector<sf::IntRect> &frames);
    const sf::Texture &getSpriteSheet() const;
    size_t getSize() const;
    const sf::IntRect &getFrame(const int &n) const;
};
} // namespace ResMng