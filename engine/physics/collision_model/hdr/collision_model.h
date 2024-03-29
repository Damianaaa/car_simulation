#ifndef ENGINE_PHYSICS_COLLISION_MODEL_HDR_COLLISION_MODEL_H
#define ENGINE_PHYSICS_COLLISION_MODEL_HDR_COLLISION_MODEL_H

#include "engine/physics/collision_model/hdr/area_description.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <optional>
#include <variant>
namespace physics
{
/*
Ok so for now:
- It will have unordered map <str/enum key, AreaDescription>
- Possibly 2 maps, one for dynamic models and one for static ones to reduce needed computations
- Implemented as a Singleton with method add collision, check collision, get interesection.
- Maybe PMR? 
- How to handle lidar, probably a separate solution as we dont want to detect collision with the beams
- How to predict collision before they occure in this setup 
- How to omit some models like e.g. when we check collisions with lidar, we wouldn't like to detect collision with the ego
*/
// enum class CollisionType{Dynamic, Static};

class CollisionManager
{
  public: // Should be private
    ~CollisionManager() = default;
    friend CollisionManager& getCollisionManager();

    template<class T>
    void addStaticCollision(const std::string& key, const T& collision)
    {
      if (!checkIfKeyExist(key))
      {
        static_collisions_.emplace(key, collision);
      }
      else
      {
        std::cerr << "Given key: '" << key << "' is already assign to one of the static collisions.\n";
      }
    }

    // std::vector<sf::Vector2f> getCollisions(const char* key)
    // {
    //   if (checkIfKeyExist(key))
    //   {
    //     return getCollisions(static_collisions_[key]);
    //   }
    //   return {};
    // }

    template<class T> // Line etc.
    std::vector<sf::Vector2f> getCollisions(const T& collision) const
    {
      std::vector<sf::Vector2f> intersection_points{};
      for (const auto& elem: static_collisions_)
      {
        std::visit([&intersection_points, &collision](const auto& area)
        {
          const auto intersection_point = area.getIntersectionPoint(collision);
          if (intersection_point)
            intersection_points.push_back(intersection_point.value());
        }, elem.second);
      }
      return intersection_points;
    }
  
  private:
    CollisionManager() = default;

    bool checkIfKeyExist(const std::string& key);

    static std::unordered_map<std::string, Area> static_collisions_;
};

CollisionManager& getCollisionManager();

}  // physics

#endif  //ENGINE_PHYSICS_COLLISION_MODEL_HDR_COLLISION_MODEL_H
