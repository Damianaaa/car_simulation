#ifndef ENGINE_WINDOW_MANAGER_HDR_SIDE_BAR_H
#define ENGINE_WINDOW_MANAGER_HDR_SIDE_BAR_H

#include "engine/physics/collision_model/hdr/area_description.h"
#include "engine/physics/collision_model/hdr/collision_model.h"
#include <vector>
#include <memory>
#include <functional>
#include <type_traits>
#include <SFML/Graphics.hpp>

namespace window_manager
{
    
enum class ShapeTypes {
    Circle, Rectangle, Line
};

class ISimpleTexture {
  protected:
    std::shared_ptr<sf::Shape> shape_;
  public:
    std::shared_ptr<sf::Shape>& getDrawable() { return shape_; }
    ISimpleTexture(std::shared_ptr<sf::Shape>&& shape): shape_{shape} {};
    virtual ~ISimpleTexture() = default;
};

// Factory to provide safe and convenient creation model.
class CircleTexture: public ISimpleTexture {
    physics::CircleDescription collision_area_;
  public:
    CircleTexture(const sf::Vector2f& position, const float radius, const char* id);
    ~CircleTexture() = default;
};

class RectangleTexture: public ISimpleTexture {
    physics::RectangleDescription collision_area_;
  public:
    RectangleTexture(const sf::Vector2f& position, const sf::Vector2f& size, const char* id);
    ~RectangleTexture() = default;
};
// class LineTexture: public ISimpleTexture {}; // Umm maybe not necessary




// Maybe button builder?
// template<class F, class... Args >
// class Button {
//     enum class TextAlignment {
//         Left, Centered, Right, None 
//     };
    
//     sf::Vector2f position_;
//     std::unique_ptr<sf::Shape> shape_; // How to approach shape size
//     std::string text_{};
//     sf::Color background_color_;
//     // std::function<F(Args...);
//     bool isClicked(const sf::Vector2f& click_location) { return true; }
    
//     public:
//     void triggerEvent()
//     {
//         if (isClicked({0.f, 0.f})) {
//             // callfoo();
//             int a = 0;
//         }
//     }

//     Button(const sf::Vector2f& position, const ShapeTypes shape) {

//     }
//     ~Button() = default;
// };
// class ScrollButton {}; // basically arrows to switch between targets > <. Maybe could be treated as normal button.
// class LookupBox {}; // Box capable of monitoring a value of given variable e.g. position.

}  // window_manager
#endif  // ENGINE_WINDOW_MANAGER_HDR_SIDE_BAR_H