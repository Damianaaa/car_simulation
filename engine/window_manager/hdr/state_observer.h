#ifndef ENGINE_WINDOW_MANAGER_HDR_STATE_OBSERVER_H
#define ENGINE_WINDOW_MANAGER_HDR_STATE_OBSERVER_H

#include <memory>
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>

namespace window_manager
{

class IStateObserver
{
  public:
    virtual void update() = 0;
    virtual std::vector<std::shared_ptr<sf::Drawable>> getDrawables() = 0;
};

template<typename T>
class StateObserver: public IStateObserver
{
    // Extract a text block from it
    std::shared_ptr<sf::RectangleShape> texture_;
    std::shared_ptr<sf::Text> text_;
    sf::Font font_;
    std::function<std::string(const T&)> to_string_;
    const T& reference_value_;
    const std::string observer_description_;

    void prepareTextBox()
    {
        if (!font_.loadFromFile("/home/damian/cpp_projects/SFML_engine/engine/fonts/Arialn.ttf"))
        {
            std::cerr << "Font not found\n"; 
        }
        text_->setFont(font_);
        text_->setCharacterSize(16);
        text_->setFillColor(sf::Color::Black);
        text_->setStyle(sf::Text::Bold);
    }

  public:
    StateObserver(const sf::Vector2f& position, const sf::Vector2f& size, std::function<std::string(const T&)> to_string,
      const std::string& description, const T& reference_value) : texture_{std::make_shared<sf::RectangleShape>(size)},
        text_{std::make_shared<sf::Text>()}, to_string_{to_string}, reference_value_{reference_value}, observer_description_{description}
    {
        texture_->setPosition(position);
        texture_->setFillColor(sf::Color::White);
        text_->setPosition(position + sf::Vector2f{3.f, 0}); // small offset
        prepareTextBox();
    }

    void update()
    {
        text_->setString(observer_description_ + ": " + to_string_(reference_value_));
    }

    std::vector<std::shared_ptr<sf::Drawable>> getDrawables()
    {
        return {texture_, text_};
    }
};

}  // window_manager
#endif  // ENGINE_WINDOW_MANAGER_HDR_STATE_OBSERVER_H