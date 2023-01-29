#ifndef ENGINE_WINDOW_MANAGER_HDR_BUTTON_H
#define ENGINE_WINDOW_MANAGER_HDR_BUTTON_H

#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>

namespace window_manager
{
    
class Button {
  public: enum class TextAlignment {
          Left, Centered, Right, None 
      };
  protected:
    const sf::Vector2f position_, size_;
    std::shared_ptr<sf::RectangleShape> texture_;
    std::function<void()> on_click_;
    std::shared_ptr<sf::Text> text_;
    sf::Font font_;
    bool on_hold_{false};
    sf::Color base_color_;
  
    bool isClicked(const sf::Vector2f& click_location);
    sf::Color getOnClickColor(const float factor) const;
    void prepareTextBox(const std::string& text, const TextAlignment text_alignment);
    sf::Vector2f calculateTextPosition(const TextAlignment text_alignment) const;
    virtual void onClick();
  public:
    
    std::vector<std::shared_ptr<sf::Drawable>> getDrawables();
    void resetState();
    
    void triggerEvent(const sf::Vector2f& click_location);

    Button(const sf::Vector2f& position, const sf::Vector2f& size, std::function<void()> on_click,
      const std::string& text=std::string{"Button"}, const TextAlignment text_alignment=TextAlignment::Centered,
      const sf::Color color=sf::Color::White);

    ~Button() = default;
};

}  // window_manager
#endif  // ENGINE_WINDOW_MANAGER_HDR_BUTTON_H