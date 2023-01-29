#ifndef ENGINE_WINDOW_MANAGER_HDR_SIDE_BAR_H
#define ENGINE_WINDOW_MANAGER_HDR_SIDE_BAR_H

#include "engine/window_manager/hdr/button.h"
#include "engine/window_manager/hdr/texture_adder.h"
#include "engine/window_manager/hdr/texture_slider.h"
#include "engine/window_manager/hdr/state_button.h"
#include "engine/window_manager/hdr/state_observer.h"
#include "engine/window_manager/hdr/window_manager.h"
#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>

namespace window_manager
{

class SideBar
{
    // Make class Updatable/Drawable etc. maybe mixin classes
    std::vector<std::unique_ptr<IStateObserver>> state_observers_{};
    std::vector<std::unique_ptr<Button>> buttons_;
    std::vector<std::unique_ptr<TextureAdder>> texture_adders_;
    std::vector<std::unique_ptr<ShapeSlider>> shape_sliders_;
    WindowManager& window_manager_;

    const sf::Vector2f position_, size_;

  public:
    SideBar(const sf::Vector2f& position, const sf::Vector2f& size, WindowManager& window_manager)
    : window_manager_{window_manager}
    {}

    template<typename T, class... Args>
    void addStateObserver(Args&&... args)
    {
        state_observers_.emplace_back(std::make_unique<StateObserver<T>>(std::forward<Args>(args)...));
        window_manager_.addDrawableVector(state_observers_.back()->getDrawables());
    }

    template<class... Args>
    void addShapeAdder(Args&&... args)
    {
        texture_adders_.emplace_back(std::make_unique<TextureAdder>(std::forward<Args>(args)...));
    }

    template<class... Args>
    void addShapeSlider(Args&&... args)
    {
        shape_sliders_.emplace_back(std::make_unique<ShapeSlider>(std::forward<Args>(args)...));
        window_manager_.addDrawableVector(shape_sliders_.back()->getDrawables());
    }

    template<class... Args>
    void addStateButton(Args&&... args)
    {
        buttons_.emplace_back(std::make_unique<StateButton>(std::forward<Args>(args)...));
        window_manager_.addDrawableVector(buttons_.back()->getDrawables());
    }

    template<class... Args>
    void addButton(Args&&... args)
    {
        buttons_.emplace_back(std::make_unique<Button>(std::forward<Args>(args)...));
        window_manager_.addDrawableVector(buttons_.back()->getDrawables());
    }
    
    void update()
    {
        // std::for_each(buttons_.begin(), buttons_.end(), [](const auto& button) { button->update(); });
        std::for_each(texture_adders_.begin(), texture_adders_.end(), [](const auto& adder) { adder->update(); });
        // std::for_each(shape_sliders_.begin(), shape_sliders_.end(), [](const auto& slider) { slider->update(); });
        std::for_each(state_observers_.begin(), state_observers_.end(), [](const auto& observer) { observer->update(); });
        // Run updates of all objects in side_bar
    }
};

}  // window_manager
#endif  // ENGINE_WINDOW_MANAGER_HDR_SIDE_BAR_H