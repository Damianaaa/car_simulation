#include "engine/physics/collision_model/hdr/collision_model.h"

namespace physics
{

bool CollisionManager::checkIfKeyExist(const std::string& key) 
{
    //(type == CollisionType::Dynamic) ? dynamic_collisions_ : static_collisions_;
    const auto& collisions = static_collisions_; 
    return std::any_of(collisions.cbegin(), collisions.cend(), 
        [key](const std::pair<std::string, Area>& collision){ 
          return key == collision.first; }); 
}

std::unordered_map<std::string, Area> CollisionManager::static_collisions_{};

CollisionManager& getCollisionManager()
{
  static CollisionManager* cm = new CollisionManager();
  return *cm;
}

}