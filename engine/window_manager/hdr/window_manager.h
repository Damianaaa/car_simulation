#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

class WindowManager
{
private:
    std::vector<std::shared_ptr<sf::Drawable>> textures_; // Who releases the memory?
    sf::RenderWindow window_;

    bool isClosed()
    {
        sf::Event event;
        while (window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                return true;            
        }
        return false;
    }

public:
    inline bool isOpen() const { return window_.isOpen(); }
    inline void addTexture(const std::shared_ptr<sf::Drawable>& texture) { textures_.emplace_back(texture); }

    void updateWindow() 
    {   
        window_.clear();
        for (const auto& texture: textures_)
        {
            window_.draw(*texture);
        }
        window_.display();
    }

    WindowManager(const uint16_t width, const uint16_t heigth, const char* title, const uint8_t FPS=30)
        : window_{sf::VideoMode(width, heigth), sf::String(title)}
    {
        window_.setFramerateLimit(FPS);
    }
    WindowManager() = delete;
};
#endif
