#include "engine/window_manager/hdr/side_bar.h"

namespace window_manager
{

CircleTexture::CircleTexture(const sf::Vector2f& position, const float radius, const char* id): 
    ISimpleTexture(std::make_shared<sf::CircleShape>(radius)),
    collision_area_{physics::CircleDescription{position, radius}}
{
    auto cm = physics::getCollisionManager();
    cm.addStaticCollision(id, collision_area_);
    // Has to be moved by radius because position is set as left upper corner of a rectangle circumscribed around the circle 
    shape_->setPosition(position - sf::Vector2f{radius, radius});
}

RectangleTexture::RectangleTexture(const sf::Vector2f& position, const sf::Vector2f& size, const char* id):
    ISimpleTexture(std::make_shared<sf::RectangleShape>(size)),
    collision_area_{physics::RectangleDescription{position, size}}
{
    auto cm = physics::getCollisionManager();
    cm.addStaticCollision(id, collision_area_);
    shape_->setPosition(position);
}


}  // window_manager
