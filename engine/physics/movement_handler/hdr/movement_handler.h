#ifndef MOVEMENT_HANDLER_H
#define MOVEMENT_HANDLER_H

#include <SFML/Graphics.hpp>
#include <math.h>

namespace physics
{
namespace mh
{

enum class MovementDirection { forward, backward };
enum class TurnDirection { left, right };

class IMovementHandler 
{
  protected:
    sf::Sprite& sprite_;
    virtual sf::Vector2<float> calculateDisplacement(const MovementDirection dir) const = 0;
    virtual float calculateRotation(const TurnDirection dir) const = 0;

  public:
    explicit IMovementHandler(sf::Sprite& sprite): sprite_(sprite) {}
    virtual ~IMovementHandler() = default;
    IMovementHandler(const IMovementHandler& rhs) = delete; // Read whether it deletes move constructor as well
    void operator = (const IMovementHandler& rhs) = delete;

    virtual void update() = 0;
};

class CarMovementHandler : public IMovementHandler 
{
    float linear_increment_;
    float angular_increment_;
    float calculateRotation(const TurnDirection dir) const override;
    sf::Vector2<float> calculateDisplacement(const MovementDirection dir) const override;

public:
    explicit CarMovementHandler(
        sf::Sprite& sprite, const float linear_increment, const float angular_increment):
            IMovementHandler(sprite), 
            linear_increment_{linear_increment},
            angular_increment_{angular_increment}
    {}
    void update() override;
};

}  //mh
}  //physics

#endif
