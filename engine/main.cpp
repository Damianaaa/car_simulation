#include <iostream>

#include <SFML/Graphics.hpp>

#include "engine/window_manager/hdr/window_manager.h"

int main()
{
    std::shared_ptr<sf::CircleShape> circle{std::make_shared<sf::CircleShape>(10)};
    circle->setPosition(100.f, 100.f);

    WindowManager manager{200, 200, "Okienko"};
    manager.addTexture(circle);
    while(manager.isOpen())
    {
        manager.updateWindow();
    }
}