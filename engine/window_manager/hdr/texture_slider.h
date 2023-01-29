#ifndef ENGINE_WINDOW_MANAGER_HDR_SHAPE_SLIDER_H
#define ENGINE_WINDOW_MANAGER_HDR_SHAPE_SLIDER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace window_manager
{
enum class ShapeType {
    Circle, Rectangle
};

class ShapeSlider
{
    std::vector<std::shared_ptr<sf::Shape>> shapes_{
        std::make_shared<sf::RectangleShape>(sf::Vector2f{30, 30}),
        std::make_shared<sf::CircleShape>(15),
    };
    std::vector<ShapeType> shape_types_{ShapeType::Rectangle, ShapeType::Circle};
    size_t current_shape_{0};

    void pickNewShape(const size_t new_choice)
    {
        sf::Color old_color = shapes_[current_shape_]->getFillColor();
        old_color.a = 0;
        shapes_[current_shape_]->setFillColor(old_color);

        sf::Color new_color = shapes_[new_choice]->getFillColor();
        new_color.a = 255;
        shapes_[new_choice]->setFillColor(new_color);
        current_shape_ = new_choice;
    }

  public:
    explicit ShapeSlider(const sf::Vector2f& position)
    {
        bool fst_elem{true};
        for (const auto& shape: shapes_)
        {
            if (fst_elem)
            {
                shape->setFillColor(sf::Color(255, 255, 255, 255));
                fst_elem = false;
            }
            else
            {
                shape->setFillColor(sf::Color(255, 255, 255, 0));
            }
            shape->setPosition(position);
        }
    }

    void goLeft()
    {
        const size_t new_choice = current_shape_ == 0 ? shapes_.size() - 1 : current_shape_ - 1;
        pickNewShape(new_choice);
    }

    void goRight()
    {
        pickNewShape((current_shape_ + 1) % shapes_.size());
    }

    const std::vector<std::shared_ptr<sf::Shape>>& getDrawables() { return shapes_; };
    const std::shared_ptr<sf::Shape>& getCurrentShape() { return shapes_[current_shape_]; }
    ShapeType getCurrentShapeType() { return shape_types_[current_shape_]; }
};

}  // window_manager
#endif  // ENGINE_WINDOW_MANAGER_HDR_SHAPE_SLIDER_H