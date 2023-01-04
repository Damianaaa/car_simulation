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

    RectangleDescription map_borders{
        {LineDescription{{0, 0}, {0, constants::window_heigth}},
        LineDescription{{0, 0}, {constants::window_width, 0}},
        LineDescription{{0, constants::window_heigth}, {constants::window_width, constants::window_heigth}},
        LineDescription{{constants::window_width, 0}, {constants::window_width, constants::window_heigth}}}
    };
    cm.addStaticCollision("borders", map_borders);
    window_manager::CircleTexture circle_1(sf::Vector2f{100.f, 100.f}, 30.0f, "c1");
    window_manager::CircleTexture circle_2(sf::Vector2f{200.f, 200.f}, 30.0f, "c2");
    window_manager::CircleTexture circle_3(sf::Vector2f{300.f, 300.f}, 30.0f, "c3");

    window_manager::RectangleTexture rect_1(sf::Vector2f{50.f, 200.f}, sf::Vector2f{50.f, 50.f}, "r1");

    sensor::Lidar lidar{10, car.getOrientation(), car.getOrigin()};
    // +200 for side bar for now
    WindowManager manager{constants::window_width + 200, constants::window_heigth, "Okienko"};
    manager.addTexture(circle_1.getDrawable());
    manager.addTexture(circle_2.getDrawable());
    manager.addTexture(rect_1.getDrawable());
    manager.addTexture(circle_3.getDrawable());

    manager.addDrawableVector(lidar.getBeams());
    manager.addTexture(car.getSprite());
    while(manager.isOpen())
    {
        manager.updateWindow();
        car.update();
        lidar.update();
    }
}