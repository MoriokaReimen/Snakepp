#pragma once
#include <SFML/Graphics.hpp>
#include <libzippp.h>
#include <toml.hpp>
#include <string>
#include <unordered_map>
#include <Animation.hpp>

namespace ResMng
{
class ResMng
{
    std::unordered_map<std::string, sf::Texture> textures_;
    std::unordered_map<std::string, sf::Font> fonts_;
    std::unordered_map<std::string, Animation> animations_;
    std::unordered_map<std::string, std::string> texts_;

public:
    ResMng();
    ResMng(const ResMng &other) = delete;
    void load(const std::string &config_path);
    void loadZip(const std::string &resource_path);
    bool loadFont(const std::string &font_path);
    bool loadFont(const std::string &font_path, const void *addr, const std::size_t size);
    bool loadTexture(const std::string &texture_path);
    bool loadTexture(const std::string &texture_path, const void *addr, const std::size_t size);
    bool loadAnimation(const std::string &animation_path, const std::vector<sf::IntRect> &frames);
    bool loadAnimation(const std::string &animation_path, const void *addr, const std::size_t size, const std::vector<sf::IntRect> &frames);
    bool loadText(const std::string &text_path);
    bool loadText(const std::string &text_path, const void *addr, const std::size_t size);
    sf::Texture &getTexture(const std::string &path);
    sf::Font &getFont(const std::string &path);
    Animation &getAnimation(const std::string &path);
    std::string &getText(const std::string &path);
};

} // namespace ResMng