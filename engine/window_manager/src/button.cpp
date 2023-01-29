#include "engine/window_manager/hdr/button.h"
#include <iostream>

namespace window_manager
{

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, std::function<void()> on_click,
    const std::string& text, const TextAlignment text_alignment, const sf::Color color)
    : position_{position}, size_{size}, texture_{std::make_shared<sf::RectangleShape>(size)},
        on_click_{on_click}, text_{std::make_shared<sf::Text>()}, base_color_{color}
{
    texture_->setPosition(position_);
    texture_->setFillColor(base_color_);
    prepareTextBox(text, text_alignment);
}

bool Button::isClicked(const sf::Vector2f& click_location)
{
    const bool x_check{(click_location.x >= position_.x && click_location.x <= position_.x + size_.x)};
    const bool y_check{(click_location.y >= position_.y && click_location.y <= position_.y + size_.y)};
    return x_check && y_check;
}

sf::Color Button::getOnClickColor(const float factor) const
{
    return sf::Color{base_color_.r * factor, base_color_.g * factor, base_color_.b * factor};
}

void Button::prepareTextBox(const std::string& text, const TextAlignment text_alignment)
{
    if (!font_.loadFromFile("/home/damian/cpp_projects/SFML_engine/engine/fonts/Arialn.ttf"))
    {
        std::cerr << "Font not found\n"; 
    }
    text_->setFont(font_);
    text_->setString(text);
    text_->setCharacterSize(16);
    text_->setFillColor(sf::Color::Black);
    text_->setStyle(sf::Text::Bold);
    const auto position = calculateTextPosition(text_alignment);
    text_->setPosition(position); 
}

sf::Vector2f Button::calculateTextPosition(const TextAlignment text_alignment) const
{
    sf::Vector2f text_pos;
    text_pos.y = position_.y + (size_.y / 2) - (text_->getGlobalBounds().height / 2) - 3; // For some reason it looks best with (-3) adjustment
    const float distance_to_boundary{5.f};
    const float text_width = text_->getGlobalBounds().width;
    switch (text_alignment)
    {
    case TextAlignment::Left:
        text_pos.x = position_.x + distance_to_boundary;
        break;
    case TextAlignment::Centered:
        text_pos.x = position_.x + (size_.x / 2) - (text_width / 2);
        break;
    case TextAlignment::Right:
        text_pos.x = (position_.x + size_.x) - text_width - distance_to_boundary;
        break;
    default:
        break;
    }
    return text_pos;
}

void Button::onClick()
{
    on_click_();
    on_hold_ = true;
    texture_->setFillColor(getOnClickColor(0.9));
    texture_->setOutlineThickness(3);
    texture_->setOutlineColor(getOnClickColor(0.3));
    text_->setFillColor(getOnClickColor(0.2));
}

std::vector<std::shared_ptr<sf::Drawable>> Button::getDrawables()
{
    return {texture_, text_};
}

void Button::resetState()
{
    texture_->setFillColor(base_color_);
    texture_->setOutlineThickness(0);
    text_->setFillColor(sf::Color::Black);
    on_hold_ = false;
}

// Maybe instead of this, write method update as everywhere with local mouse click check
void Button::triggerEvent(const sf::Vector2f& click_location)
{
    if (isClicked(click_location)) {
        if (!on_hold_)
        {
            onClick();
        }
    }
    else {
        resetState();
    }
}

}  // window_manager