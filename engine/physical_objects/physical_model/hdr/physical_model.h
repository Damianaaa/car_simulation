#ifndef PHYSICAL_MODEL_H
#define PHYSICAL_MODEL_H

#include <SFML/Graphics/Transform.hpp>

constexpr float g_acc = 9.81;
constexpr float ground_f = 0.3;

class PhysicalModel
{
private:
    const float mass_;
    const sf::Vector2f& pos_;
    const bool movable_;
    // std::unique_ptr<CollisionModel> collision_model{}
    // std::unique_ptr<DynamicModel> dynamic_model{}
public:
    sf::Vector2f getReplacement();
    bool checkCollision();
    PhysicalModel() = delete;
    PhysicalModel(const float mass, const sf::Vector2f& pos, const bool movable): mass_{mass}, pos_{pos}, movable_{movable} {};
};

#endif