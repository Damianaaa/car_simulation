#include "engine/sensors/lidar/hdr/lidar.h"
#include "engine/physics/collision_model/hdr/collision_model.h"
#include "engine/math/hdr/algebra.h"
#include <iostream>
#include <cmath>

namespace sensor
{
    
Lidar::Lidar(const unsigned int number_of_beams, const float& heading, const sf::Vector2f& origin):
    angle_increment_{360.0f / number_of_beams},
    heading_{heading},
    origin_{origin},
    distances_{std::vector<float>(number_of_beams, std::nanf("NaN"))}
{
    createBeams(number_of_beams);
    updateBeams();
}

void Lidar::update()
{
    updateBeams();
}

void Lidar::createBeams(const unsigned int number_of_beams)
{
    beams_.reserve(number_of_beams);
    // probably should be in initialization list
    for (unsigned int i = 0; i < number_of_beams; ++i)
        beams_.emplace_back(std::make_shared<sf::VertexArray>());
}

// We can make it exeption safe by copy and switch idiom
void Lidar::updateBeams() 
{
    sf::VertexArray new_beam(sf::Lines, 2);
    new_beam[0] = origin_;
    const auto cm = physics::getCollisionManager();

    // More like a fancy way to do that, just out of curiocity 
    auto idx_increment = [i = 0]() mutable { return i++; };
    // Make parallel if possible (it should be), easy way would be to use execution policy on the std::for_each.
    for (const auto& beam: beams_)
    {
        // -heading should be probably somehow connected to initial car orientation
        const float beam_angle = -heading_ + idx_increment() * angle_increment_;
        const float angle_rad = ((-beam_angle) / 180) * M_PI;
        physics::LineDescription ld{origin_, origin_ + sf::Vector2<float>(500 * cos(angle_rad), 500 * sin(angle_rad))};
        const auto points = cm.getCollisions(ld);
        if (points.size() == 0) // Always should find col
            new_beam[1] = sf::Vector2f{0 ,0};
        else 
            new_beam[1] = math::getClosestPoint(origin_, points);
        *beam = new_beam;
    }
}


} // namespace sensor
