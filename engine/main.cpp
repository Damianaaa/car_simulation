#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "engine/window_manager/hdr/window_manager.h"
#include "engine/models/car_model/hdr/car_model.h"
#include "engine/sensors/lidar/hdr/lidar.h"

int main()
{
    CarModel car{"/home/damian/CLionProjects/sql/car.png"};
    std::shared_ptr<sf::CircleShape> circle{std::make_shared<sf::CircleShape>(10)};
    circle->setPosition(100.f, 100.f);
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