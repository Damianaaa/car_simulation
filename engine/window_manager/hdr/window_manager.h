#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <vector>
#include <memory>
#include <type_traits>
#include <SFML/Graphics.hpp>

/**
 * @brief Class responsible for window management and for now most of the event handling
 * @todo On-click actions, for now texture creation (with support of the side bar manager).
 * 
 */
class WindowManager
{
private:
    std::vector<std::shared_ptr<sf::Drawable>> textures_;
    sf::RenderWindow window_;

    bool isClosed()
    {
        sf::Event event;
        bool is_closed{false};
        while (window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                is_closed = true;            
        }
        return is_closed;
    }

public:
    bool isOpen() { return window_.isOpen() && !isClosed(); }
    inline void addTexture(const std::shared_ptr<sf::Drawable> texture) { textures_.emplace_back(texture); }

    const sf::RenderWindow& getWindow() { return window_; }

    template<typename T>
    void addDrawableVector(const std::vector<std::shared_ptr<T>>& drawables) 
    {
        if (std::is_base_of_v<sf::Drawable, T>)
        std::for_each(drawables.cbegin(), drawables.cend(), [&textures = textures_](const auto drawable)
            { textures.push_back(drawable); });
        else
        {
            std::cerr << "Type is not derived from sf::Drawable\n";
        }
    }

    /**
     * @brief Updates the window and renders all the textures. In the future would be nice to
     * render only the changing area (e.g. around the model)
     */
    void updateWindow() 
    {
        window_.clear();
        std::for_each(textures_.cbegin(), textures_.cend(), 
            [&window = window_](const auto &texture) { window.draw(*texture); }); // Check if faster or at least as fast as for loop
        window_.display();
    }

    WindowManager(const uint16_t width, const uint16_t heigth, const char* title, const uint8_t FPS=30):
            window_{sf::VideoMode(width, heigth), sf::String(title)}
    {
        window_.setFramerateLimit(FPS);
    }
    WindowManager() = delete;
    ~WindowManager() {
        window_.close();
    }
};
#endif
