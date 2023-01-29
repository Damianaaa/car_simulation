#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "engine/window_manager/hdr/window_manager.h"
#include "engine/models/car_model/hdr/car_model.h"
#include "engine/physics/collision_model/hdr/area_description.h"
#include "engine/physics/collision_model/hdr/collision_model.h"
#include "engine/window_manager/hdr/side_bar.h"
#include "engine/sensors/lidar/hdr/lidar.h"

// Add boost cli handling for adding stuff like: lidar beams visibility
int main()
{
    using namespace physics;
    auto cm = getCollisionManager();
    // Relative path
    CarModel car{"/home/damian/cpp_projects/SFML_engine/engine/images/car.png"};
    // +200 for side bar for now
    WindowManager manager{constants::window_width + 200, constants::window_heigth, "Okienko"};

    RectangleDescription map_borders{
        {LineDescription{{0, 0}, {0, constants::window_heigth}},
        LineDescription{{0, 0}, {constants::window_width, 0}},
        LineDescription{{0, constants::window_heigth}, {constants::window_width, constants::window_heigth}},
        LineDescription{{constants::window_width, 0}, {constants::window_width, constants::window_heigth}}}
    };
    cm.addStaticCollision("borders", map_borders);
    window_manager::SideBar side_bar{sf::Vector2f{}, sf::Vector2f{200.f, 400.f}, manager};
    side_bar.addStateObserver<float>(sf::Vector2f{450, 150}, sf::Vector2f{100, 25}, 
        [](const float& ref_val){ return std::to_string(ref_val); }, "x", car.getOrigin().x
    );
    side_bar.addStateObserver<float>(sf::Vector2f{450, 200}, sf::Vector2f{100, 25}, 
        [](const float& ref_val){ return std::to_string(ref_val); }, "y", car.getOrigin().y
    );
    side_bar.addShapeAdder(sf::Vector2i{100, 100}, manager);


    sensor::Lidar lidar{10, car.getOrientation(), car.getOrigin()};

    manager.addDrawableVector(lidar.getBeams());
    manager.addTexture(car.getSprite());
    while(manager.isOpen())
    {
        manager.updateWindow();
        side_bar.update();
        car.update();
        lidar.update();
    }
}