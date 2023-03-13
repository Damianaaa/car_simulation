#include "engine/physics/movement_handler/hdr/movement_handler.h"
#include "engine/physics/collision_model/hdr/collision_model.h"
#include "engine/math/hdr/geometric_transformations.h"
#include "engine/physics/collision_model/hdr/area_description.h"
namespace physics
{
namespace mh
{

sf::Vector2<float> CarMovementHandler::calculateDisplacement(const MovementDirection dir) const // Naming
{
    float sign;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        sign = -1.0f;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        sign = 1.0f;
    else
        return {0.0f, 0.0f};
    const float angle = ((-sprite_.getRotation()) / 180) * M_PI;
    const float vel_x = sign * linear_increment_ * sin(angle);
    const float vel_y = sign * linear_increment_ * cos(angle);
    return {vel_x, vel_y};
}

float CarMovementHandler::calculateRotation(const TurnDirection dir) const 
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        return angular_increment_;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        return -angular_increment_;
    else
        return 0.0f;
}

bool CarMovementHandler::checkCollision(const sf::Vector2f displacement, const float rotation) const
{
    const auto& cm = physics::getCollisionManager();
    const auto texture_properties = sprite_.getTextureRect();
    const auto new_center_point = sprite_.getPosition() + displacement;
    const float new_rotation = ((-sprite_.getRotation()) / 180) * M_PI + rotation;

    const auto new_borders = math::getBordersFromCenterPoint(
        new_center_point, sf::Vector2f{texture_properties.width, texture_properties.height}, -new_rotation
    );

    RectangleDescription future_collision_rect{{
        LineDescription{new_borders[0], new_borders[1]},
        LineDescription{new_borders[1], new_borders[2]},
        LineDescription{new_borders[2], new_borders[3]},
        LineDescription{new_borders[3], new_borders[0]}
    }};
    
    return cm.getCollisions(future_collision_rect).size() > 0;
}

void CarMovementHandler::update() {
    const auto displacement{calculateDisplacement(MovementDirection::forward)};
    const auto rotation{calculateRotation(TurnDirection::left)};
    // Move, if collision revert movement

    if (checkCollision(displacement, rotation))
        std::cout << "Collided\n";
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
