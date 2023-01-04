#include "engine/physics/collision_model/hdr/collision_model.h"

namespace physics
{

bool CollisionManager::checkIfKeyExist(const char* key, const CollisionType type) 
{
    const auto& collisions = (type == CollisionType::Dynamic) ? dynamic_collisions_ : static_collisions_;
    return std::any_of(collisions.cbegin(), collisions.cend(), 
        [key](const std::pair<const char* const, Area>& collision){ 
          return key == collision.first; }); 
}

std::unordered_map<const char*, Area> CollisionManager::static_collisions_{};
std::unordered_map<const char*, Area> CollisionManager::dynamic_collisions_{};

CollisionManager& getCollisionManager()
{
  static CollisionManager* cm = new CollisionManager();
  return *cm;
}

}