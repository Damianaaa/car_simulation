#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "engine/window_manager/hdr/window_manager.h"
#include "engine/models/car_model/hdr/car_model.h"
#include "engine/physics/collision_model/hdr/area_description.h"
#include "engine/physics/collision_model/hdr/collision_model.h"
#include "engine/sensors/lidar/hdr/lidar.h"


int main()
{
    auto cm = physics::getCollisionManager();
    // Relative path
    CarModel car{"/home/damian/cpp_projects/SFML_engine/engine/images/car.png"};
    std::shared_ptr<sf::CircleShape> circle{std::make_shared<sf::CircleShape>(10)};
    circle->setPosition(100.f, 100.f);
    physics::CircleDescription circle_collision{sf::Vector2f{100.f, 100.f}, 10.0f};
    // physics::LineDescription map_borders[4] = {
    //     physics::LineDescription{{0, 0}, {0, 200}},
    //     physics::LineDescription{{0, 0}, {200, 0}},
    //     physics::LineDescription{{200, 200}, {0, 200}},
    //     physics::LineDescription{{200, 200}, {200, 0}}
    // };
    // cm.addStaticCollision("border_1", map_borders[0]);
    // cm.addStaticCollision("border_2", map_borders[1]);
    // cm.addStaticCollision("border_3", map_borders[2]);
    // cm.addStaticCollision("border_4", map_borders[3]);
    physics::LineDescription line{{100, 100}, {120, 120}};
    std::cout << cm.getCollisions(line).size();
    // std::cout << cm.getCollisions(line).front().x << ": " << cm.getCollisions(line).front().y << "\n";

    cm.addStaticCollision("circle", circle_collision);

    sf::Vector2<float> pivot{100.0f, 100.0f};

    sensor::Lidar lidar{10, car.getOrientation(), car.getOrigin()};

    WindowManager manager{200, 200, "Okienko"};
    manager.addTexture(circle);
    manager.addDrawableVector(lidar.getBeams());
    manager.addTexture(car.getSprite());
    while(manager.isOpen())
    {
        manager.updateWindow();
        car.update();
        lidar.update();
    }
}