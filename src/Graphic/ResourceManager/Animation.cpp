#include <Animation.hpp>

namespace ResMng
{
Animation::Animation()
    : frames_(),
      texture_()
{
}

Animation::Animation(const std::string &path)
{
    setSpriteSheet(path);
}

Animation::Animation(const std::string &path, const std::vector<sf::IntRect> &frames)
{
    setSpriteSheet(path, frames);
}

Animation::Animation(const void *addr, const size_t size)
{
    setSpriteSheet(addr, size);
}

Animation::Animation(const void *addr, const size_t size, const std::vector<sf::IntRect> &frames)
{
    setSpriteSheet(addr, size, frames);
}

void Animation::addFrame(const sf::IntRect &rect)
{
    frames_.push_back(rect);
}

bool Animation::setSpriteSheet(const void *addr, const size_t size)
{
    bool ret = false;
    if (texture_.loadFromMemory(addr, size))
    {
        ret = true;
    }

    return ret;
}

bool Animation::setSpriteSheet(const void *addr, const size_t size, const std::vector<sf::IntRect> &frames)
{
    bool ret;

    ret = setSpriteSheet(addr, size);
    if (ret)
    {
        this->frames_ = frames;
    }

    return ret;
}

bool Animation::setSpriteSheet(const std::string &path)
{
    bool ret(false);
    sf::Texture texture;
    if (texture_.loadFromFile(path))
    {
        ret = true;
    }

    return ret;
}

bool Animation::setSpriteSheet(const std::string &path, const std::vector<sf::IntRect> &frames)
{
    bool ret;

    ret = setSpriteSheet(path);
    if (ret)
    {
        this->frames_ = frames;
    }

    return ret;
}

const sf::Texture &Animation::getSpriteSheet() const
{
    return this->texture_;
}

size_t Animation::getSize() const
{
    return this->frames_.size();
}

const sf::IntRect &Animation::getFrame(const int &idx) const
{
    return this->frames_[idx];
}

} // namespace ResMng