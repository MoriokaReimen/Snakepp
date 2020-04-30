#include <GridShape.hpp>

namespace sf
{
GridShape::GridShape(const Vector2f &cell_size, const Vector2i &dimension)
    : cell_size_(cell_size), dimension_(dimension), color_(Color::Black)
{
    update();
}

void GridShape::update()
{
    vertices_.clear();
    vertices_.setPrimitiveType(sf::Lines);
    for (int i = 0; i <= dimension_.x; i++)
    {
        vertices_.append(sf::Vertex(Vector2f(i * cell_size_.x, 0), color_));
        vertices_.append(sf::Vertex(Vector2f(i * cell_size_.x, cell_size_.y * dimension_.y), color_));
    }

    for (int j = 0; j <= dimension_.y; j++)
    {
        vertices_.append(sf::Vertex(Vector2f(0, j * cell_size_.y), color_));
        vertices_.append(sf::Vertex(Vector2f(cell_size_.x * dimension_.x, j * cell_size_.y), color_));
    }
}

void GridShape::setCellSize(const Vector2f &size)
{
    this->cell_size_ = size;
    update();
}

const Vector2f &GridShape::getCellSize() const
{
    return this->cell_size_;
}

void GridShape::setDimension(const Vector2i &dimension)
{
    this->dimension_ = dimension;
    update();
}

Vector2i GridShape::getDimension() const
{
    return this->dimension_;
}

Color GridShape::getColor() const
{
    return color_;
}

void GridShape::setColor(Color& color)
{
    this->color_ = color;
}

void GridShape::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(vertices_, states);
}

}; // namespace sf