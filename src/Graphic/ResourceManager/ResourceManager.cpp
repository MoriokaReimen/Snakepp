#include "ResourceManger.hpp"
#include <toml.hpp>
#include <spdlog/spdlog.h>
#include <sstream>
#include <vector>

namespace ResMng
{

ResMng::ResMng()
    : textures_(),
      fonts_(),
      animations_(),
      texts_()
{
}

void ResMng::load(const std::string &config_path)
{
    spdlog::info("Loading Resource : {}", config_path);
    std::istringstream ss(config_path);
    const auto data = toml::parse(ss);
    {
        const auto fonts = toml::find<std::vector<toml::table>>(data, "fonts");
        for (const auto &font : fonts)
        {
            std::string path = font.at("path").as_string();
            path = config_path + "/" + path;
            if (!this->loadFont(path))
            {
                spdlog::warn("font not found: {}", path);
            }
        }
    }
    {
        const auto textures = toml::find<std::vector<toml::table>>(data, "textures");
        for (const auto &texture : textures)
        {
            std::string path = texture.at("path").as_string();
            path = config_path + "/" + path;
            if (!this->loadTexture(path))
            {
                spdlog::warn("Texture not found: {}", path);
            }
        }
    }

    {
        const auto animations = toml::find<std::vector<toml::table>>(data, "animations");
        for (const auto &animation : animations)
        {
            std::vector<sf::IntRect> frames;
            auto geoms = animation.at("frames").as_array();
            for (auto &geom : geoms)
            {
                frames.push_back(sf::IntRect(geom[0].as_integer(), geom[1].as_integer(),
                                             geom[2].as_integer(), geom[3].as_integer()));
            }

            std::string path = animation.at("path").as_string();
            path = config_path + "/" + path;
            if (!this->loadAnimation(path, frames))
            {
                spdlog::warn("Animation not found: {}", path);
            }
        }
    }

    {
        const auto texts = toml::find<std::vector<toml::table>>(data, "texts");
        for (const auto &text : texts)
        {
            std::string path = text.at("path").as_string();
            path = config_path + "/" + path;
            if (!this->loadText(path))
            {
                spdlog::warn("Tex not found: {}", path);
            }
        }
    }
}

void ResMng::loadZip(const std::string &resource_path)
{
    libzippp::ZipArchive zf(resource_path);
    zf.open(libzippp::ZipArchive::OpenMode::READ_ONLY, false);
    spdlog::info("Loading Resource : {}", resource_path);
    auto config_entry = zf.getEntry("resource/config.toml");
    std::string config = config_entry.readAsText();
    std::istringstream ss(config);
    const auto data = toml::parse(ss);
    {
        const auto fonts = toml::find<std::vector<toml::table>>(data, "fonts");
        for (const auto &font : fonts)
        {
            auto path = font.at("path").as_string();
            libzippp::ZipEntry entry = zf.getEntry(path);
            if (entry.isFile())
            {
                auto addr = entry.readAsBinary();
                auto size = entry.getSize();
                this->loadFont(path, addr, size);
            }
            else
            {
                spdlog::warn("font not found: {}", path);
            }
        }
    }
    {
        try
        {
            const auto textures = toml::find<std::vector<toml::table>>(data, "textures");
            for (const auto &texture : textures)
            {
                auto path = texture.at("path").as_string();
                libzippp::ZipEntry entry = zf.getEntry(path);
                if (entry.isFile())
                {
                    auto addr = entry.readAsBinary();
                    auto size = entry.getSize();
                    this->loadTexture(path, addr, size);
                }
                else
                {
                    spdlog::warn("Texture not found: {}", path);
                }
            }
        }
        catch (const std::out_of_range &er)
        {
            spdlog::info("No textures found in {}", resource_path);
        }
    }

    {
        try
        {
            const auto animations = toml::find<std::vector<toml::table>>(data, "animations");
            for (const auto &animation : animations)
            {
                std::vector<sf::IntRect> frames;
                auto geoms = animation.at("frames").as_array();
                for (auto &geom : geoms)
                {
                    frames.push_back(sf::IntRect(geom[0].as_integer(), geom[1].as_integer(),
                                                 geom[2].as_integer(), geom[3].as_integer()));
                }

                auto path = animation.at("path").as_string();
                libzippp::ZipEntry entry = zf.getEntry(path);
                if (entry.isFile())
                {
                    auto addr = entry.readAsBinary();
                    auto size = entry.getSize();
                    this->loadAnimation(path, addr, size, frames);
                }
                else
                {
                    spdlog::warn("Animation not found: {}", path);
                }
            }
        }
        catch (const std::out_of_range &er)
        {
            spdlog::info("No animations found in {}", resource_path);
        }
    }

    {
        try
        {
            const auto texts = toml::find<std::vector<toml::table>>(data, "texts");
            for (const auto &text : texts)
            {
                auto path = text.at("path").as_string();
                libzippp::ZipEntry entry = zf.getEntry(path);
                if (entry.isFile())
                {
                    auto addr = entry.readAsBinary();
                    auto size = entry.getSize();
                    this->loadText(path, addr, size);
                }
                else
                {
                    spdlog::warn("Tex not found: {}", path);
                }
            }
        }
        catch (const std::out_of_range &err)
        {
            spdlog::info("No texts found in {}", resource_path);
        }
    }
}

bool ResMng::loadFont(const std::string &font_path)
{
    bool ret(false);
    sf::Font font;
    if (font.loadFromFile(font_path))
    {
        fonts_[font_path] = font;
        ret = true;
        spdlog::info("Successfully loaded font: {}", font_path);
    }
    else
    {
        spdlog::warn("Failed to load font: {}", font_path);
    }

    return ret;
}

bool ResMng::loadFont(const std::string &font_path, const void *addr, const std::size_t size)
{
    bool ret(false);
    sf::Font font;
    if (font.loadFromMemory(addr, size))
    {
        fonts_[font_path] = font;
        ret = true;
        spdlog::info("Successfully loaded font: {}", font_path);
    }
    else
    {
        spdlog::warn("Failed to load font: {}", font_path);
    }

    return ret;
}

bool ResMng::loadTexture(const std::string &texture_path)
{
    bool ret(false);
    sf::Texture texture;
    if (texture.loadFromFile(texture_path))
    {
        textures_[texture_path] = texture;
        ret = true;
        spdlog::info("Successfully loaded texture: {}", texture_path);
    }
    else
    {
        spdlog::warn("Failed to load texture: {}", texture_path);
    }
    return ret;
}

bool ResMng::loadTexture(const std::string &texture_path, const void *addr, const std::size_t size)
{
    bool ret(false);
    sf::Texture texture;
    if (texture.loadFromMemory(addr, size))
    {
        textures_[texture_path] = texture;
        ret = true;
        spdlog::info("Successfully loaded texture: {}", texture_path);
    }
    else
    {
        spdlog::warn("Failed to load texture: {}", texture_path);
    }

    return ret;
}

bool ResMng::loadAnimation(const std::string &animation_path, const std::vector<sf::IntRect> &frames)
{
    bool ret(false);
    Animation anim;
    if (anim.setSpriteSheet(animation_path, frames))
    {
        animations_[animation_path] = anim;
        ret = true;
        spdlog::info("Successfully loaded animation: {}", animation_path);
    }
    else
    {
        spdlog::warn("Failed to load animation: {}", animation_path);
    }
    return ret;
}

bool ResMng::loadAnimation(const std::string &animation_path, const void *addr, const std::size_t size, const std::vector<sf::IntRect> &frames)
{
    bool ret(false);
    Animation animation;
    if (animation.setSpriteSheet(addr, size, frames))
    {
        animations_[animation_path] = animation;
        ret = true;
        spdlog::info("Successfully loaded animation: {}", animation_path);
    }
    else
    {
        spdlog::warn("Failed to load animation: {}", animation_path);
    }

    return ret;
}

bool ResMng::loadText(const std::string &text_path)
{
    bool ret(false);
    std::ifstream file(text_path);

    if (file.is_open())
    {
        std::stringstream ss;
        ss << file.rdbuf();
        texts_[text_path] = ss.str();
        ret = true;
        spdlog::info("Successfully loaded text: {}", text_path);
    }
    else
    {
        spdlog::warn("Failed to load Text: {}", text_path);
    }

    return ret;
}

bool ResMng::loadText(const std::string &text_path, const void *addr, const std::size_t size)
{
    bool ret(false);
    std::string text((const char *)addr);

    if (!text.empty())
    {
        texts_[text_path] = text;
        ret = true;
        spdlog::info("Successfully loaded Text: {}", text_path);
    }
    else
    {
        spdlog::warn("Failed to load Text: {}", text_path);
    }

    return ret;
}

sf::Texture &ResMng::getTexture(const std::string &path)
{
    if (textures_.find(path) == textures_.end())
    {
        spdlog::error("texture: {} is not registered in resource manager", path);
    }

    return textures_[path];
}

sf::Font &ResMng::getFont(const std::string &path)
{
    if (fonts_.find(path) == fonts_.end())
    {
        spdlog::error("fonts: {} is not registered in resource manager", path);
    }

    return fonts_[path];
}

Animation &ResMng::getAnimation(const std::string &path)
{
    if (animations_.find(path) == animations_.end())
    {
        spdlog::error("animation: {} is not registered in resource manager", path);
    }

    return animations_[path];
}

std::string &ResMng::getText(const std::string &path)
{
    if (texts_.find(path) == texts_.end())
    {
        spdlog::error("text: {} is not registered in resource manager", path);
    }

    return texts_[path];
}

}; // namespace ResMng