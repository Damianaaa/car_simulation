#include "engine/window_manager/hdr/textures.h"

namespace window_manager
{

unsigned int ISimpleTexture::id_ = 0;

CircleTexture::CircleTexture(const sf::Vector2f& position, const float radius): 
    ISimpleTexture(std::make_shared<sf::CircleShape>(radius)),
    collision_area_{physics::CircleDescription{position, radius}}
{
    auto cm = physics::getCollisionManager();
    cm.addStaticCollision("Circle_" + std::to_string(id_++), collision_area_);
    // Has to be moved by radius because position is set as left upper corner of a rectangle circumscribed around the circle 
    shape_->setPosition(position - sf::Vector2f{radius, radius});
}

RectangleTexture::RectangleTexture(const sf::Vector2f& position, const sf::Vector2f& size):
    ISimpleTexture(std::make_shared<sf::RectangleShape>(size)),
    collision_area_{physics::RectangleDescription{position, size}}
{
    auto cm = physics::getCollisionManager();
    cm.addStaticCollision("Rectangle_" + std::to_string(id_++), collision_area_);
    shape_->setPosition(position);
}

}  // window_manager
