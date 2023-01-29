#ifndef ENGINE_WINDOW_MANAGER_HDR_TEXTURE_H
#define ENGINE_WINDOW_MANAGER_HDR_TEXTURE_H

#include "engine/physics/collision_model/hdr/area_description.h"
#include "engine/physics/collision_model/hdr/collision_model.h"
#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>

namespace window_manager
{

enum class ShapeTypes {
    Circle, Rectangle, Line
};

// Factory to provide safe and convenient creation model.
class ISimpleTexture {
  protected:
    std::shared_ptr<sf::Shape> shape_;
    static unsigned int id_; 
  public:
    std::shared_ptr<sf::Shape>& getDrawable() { return shape_; }
    ISimpleTexture(std::shared_ptr<sf::Shape>&& shape): shape_{shape} {};
    virtual ~ISimpleTexture() = default;
};

class CircleTexture: public ISimpleTexture {
    physics::CircleDescription collision_area_;
  public:
    CircleTexture(const sf::Vector2f& position, const float radius);
    ~CircleTexture() = default;
};

class RectangleTexture: public ISimpleTexture {
    physics::RectangleDescription collision_area_;
  public:
    RectangleTexture(const sf::Vector2f& position, const sf::Vector2f& size);
    ~RectangleTexture() = default;
};

}  // window_manager
#endif  // ENGINE_WINDOW_MANAGER_HDR_TEXTURE_H