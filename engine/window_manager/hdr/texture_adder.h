#ifndef ENGINE_WINDOW_MANAGER_HDR_TEXTURE_ADDER_H
#define ENGINE_WINDOW_MANAGER_HDR_TEXTURE_ADDER_H

#include "engine/window_manager/hdr/button.h"
#include "engine/window_manager/hdr/state_button.h"
#include "engine/window_manager/hdr/textures.h"
#include "engine/window_manager/hdr/texture_slider.h"
#include "engine/window_manager/hdr/window_manager.h"
#include <memory>
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>

namespace window_manager
{

/**
 * @brief 
 * @todo: 
 * - Clean it up and prepare something to store those textures as I feel like it is not a place.
 * - Provide a way to cut the textures outside the window borders. Ez (not nice) solution would be to paint side_bar black and update it after the original window
 */
class TextureAdder
{
    std::unique_ptr<Button> left_switch_, right_switch_; // vector off buttons will probably make it a bit clearer
    std::unique_ptr<StateButton> state_switch_;
    std::unique_ptr<ShapeSlider> shape_slider_;
    WindowManager& window_manager_; // Singleton seems like a good idea in this case but what do I know
    bool on_hold_{false};
    std::vector<std::unique_ptr<ISimpleTexture>> created_textures;

    void addTexturesToWindow() 
    {
        window_manager_.addDrawableVector(left_switch_->getDrawables());
        window_manager_.addDrawableVector(right_switch_->getDrawables());
        window_manager_.addDrawableVector(state_switch_->getDrawables());
        window_manager_.addDrawableVector(shape_slider_->getDrawables());
    }

    void triggerSideBarEvent(const sf::Vector2i& mouse_pos) {
        if (!on_hold_)
        {
            state_switch_->triggerEvent(sf::Vector2f{mouse_pos});
            left_switch_->triggerEvent(sf::Vector2f{mouse_pos});
            right_switch_->triggerEvent(sf::Vector2f{mouse_pos});
        }
    }
    void triggerMapEvent(const sf::Vector2i& mouse_pos)
    {
        if (!on_hold_ && state_switch_->getState())
        {
            CreateShapeCopy(mouse_pos);
        }
    }

    void CreateShapeCopy(const sf::Vector2i& mouse_pos)
    {
        switch (shape_slider_->getCurrentShapeType())
        {
        case ShapeType::Rectangle:
            {
                auto curr_shape = dynamic_cast<sf::RectangleShape*>(shape_slider_->getCurrentShape().get());
                created_textures.emplace_back(std::make_unique<RectangleTexture>(
                    sf::Vector2f{mouse_pos}, curr_shape->getSize()
                ));
                window_manager_.addTexture(created_textures.back()->getDrawable());
            }
            break;
        case ShapeType::Circle:
            {
                auto curr_shape = dynamic_cast<sf::CircleShape*>(shape_slider_->getCurrentShape().get());
                created_textures.emplace_back(std::make_unique<CircleTexture>(
                    sf::Vector2f{mouse_pos}, curr_shape->getRadius()
                ));
                window_manager_.addTexture(created_textures.back()->getDrawable());
            }
            break;
        default:
            break;
        }
    }

public:

    TextureAdder(const sf::Vector2i& position, WindowManager& window_manager): window_manager_{window_manager}
    {
        shape_slider_ = std::make_unique<ShapeSlider>(sf::Vector2f{485, 25});
        state_switch_ = std::make_unique<StateButton>(sf::Vector2f{450, 75}, sf::Vector2f{100, 25}, []() {}, "State");
        left_switch_ = std::make_unique<Button>(sf::Vector2f{450, 25}, sf::Vector2f{25, 25}, [&slider = shape_slider_]() { slider->goLeft(); }, "L");
        right_switch_ = std::make_unique<Button>(sf::Vector2f{525, 25}, sf::Vector2f{25, 25}, [&slider = shape_slider_]() { slider->goRight(); }, "R");
        addTexturesToWindow();
    }

    void update()
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window_manager_.getWindow());
            if (mouse_pos.x < 400)
                triggerMapEvent(mouse_pos);
            else
                triggerSideBarEvent(mouse_pos);
        }
        else {
            state_switch_->resetState();
            left_switch_->resetState();
            right_switch_->resetState();
            on_hold_ = false;
        }
    }
};

}  // window_manager
#endif  // ENGINE_WINDOW_MANAGER_HDR_TEXTURE_ADDER_H