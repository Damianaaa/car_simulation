#include "engine/physics/movement_handler/hdr/movement_handler.h"

namespace physics
{
namespace mh
{

sf::Vector2<float> CarMovementHandler::calculateDisplacement(const MovementDirection dir) const // Naming
{
    const float sign = dir == MovementDirection::backward ? 1 : -1;
    const float angle = ((-sprite_.getRotation()) / 180) * M_PI;
    const float vel_x = sign * linear_increment_ * sin(angle);
    const float vel_y = sign * linear_increment_ * cos(angle);
    return {vel_x, vel_y};
}

float CarMovementHandler::calculateRotation(const TurnDirection dir) const 
{
    const float sign = dir == TurnDirection::right ? 1 : -1;
    // sing is a float as it would be converted anyway in the below section?
    return sign * angular_increment_; // Check if in radians, small angle wrapper?
}

void CarMovementHandler::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sprite_.rotate(calculateRotation(TurnDirection::right));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sprite_.rotate(calculateRotation(TurnDirection::left));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        sprite_.move(calculateDisplacement(MovementDirection::forward));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        sprite_.move(calculateDisplacement(MovementDirection::backward));
    }
}

}  //mh
}  //physics
