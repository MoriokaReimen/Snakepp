#pragma once
#include <SFML/Graphics.hpp>

namespace sf
{

class GridShape : public Drawable, public Transformable
{
    Vector2f cell_size_;
    Vector2i dimension_;
    VertexArray vertices_;
    Color color_;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update();
public:
    explicit GridShape(const Vector2f &cell_size, const Vector2i &dimension);
    void setCellSize(const Vector2f &size);
    const Vector2f &getCellSize() const;
    void setDimension(const Vector2i &dimension);
    Vector2i getDimension() const;
    Color getColor() const;
    void setColor(Color& color);
};
} // namespace sf
