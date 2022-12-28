#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "engine/window_manager/hdr/window_manager.h"
#include "engine/models/car_model/hdr/car_model.h"
#include "engine/physics/collision_model/hdr/area_description.h"
#include "engine/physics/collision_model/hdr/collision_model.h"
#include "engine/sensors/lidar/hdr/lidar.h"

// Add boost cli handling for adding stuff like: lidar beams visibility
int main()
{
    using namespace physics;
    auto cm = getCollisionManager();
    // Relative path
    CarModel car{"/home/damian/cpp_projects/SFML_engine/engine/images/car.png"};
    std::shared_ptr<sf::CircleShape> circle{std::make_shared<sf::CircleShape>(30)};
    
    circle->setPosition(70.f, 70.f); // Has to be moved by radius because position is set as left upper corner of a rectangle circumscribed around a circle 
    CircleDescription circle_collision{sf::Vector2f{100.f, 100.f}, 30.0f};
    RectangleDescription map_borders{
        {LineDescription{{0, 0}, {0, constants::window_heigth}},
        LineDescription{{0, 0}, {constants::window_width, 0}},
        LineDescription{{0, constants::window_heigth}, {constants::window_width, constants::window_heigth}},
        LineDescription{{constants::window_width, 0}, {constants::window_width, constants::window_heigth}}}
    };
    cm.addStaticCollision("borders", map_borders);
    cm.addStaticCollision("circle", circle_collision);

    sensor::Lidar lidar{100, car.getOrientation(), car.getOrigin()};
    // +200 for side bar for now
    WindowManager manager{constants::window_width + 200, constants::window_heigth, "Okienko"};
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