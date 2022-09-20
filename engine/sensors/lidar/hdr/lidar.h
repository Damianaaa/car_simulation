#ifndef ENGINE_SENSOR_LIDAR_LIDAR_H
#define ENGINE_SENSOR_LIDAR_LIDAR_H
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <math.h>

namespace sensor
{

class Lidar//: public ISensor
{
    bool visualize_{true};
    float angle_increment_;
    const float& heading_;
    const sf::Vector2<float>& origin_;
    std::vector<std::shared_ptr<sf::VertexArray>> beams_;
    std::vector<float> distances_;

    void createBeams(const unsigned int number_of_beams);
    void updateBeams();
    void updateDistances();

  public:
    Lidar(const unsigned int number_of_beams, const float& heading, const sf::Vector2f& origin);
    ~Lidar() = default;

    inline const std::vector<std::shared_ptr<sf::VertexArray>>& getBeams() { return beams_; }
    void update();
};

} // namespace sensor

#endif