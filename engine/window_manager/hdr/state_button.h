#ifndef ENGINE_WINDOW_MANAGER_HDR_STATE_BUTTON_H
#define ENGINE_WINDOW_MANAGER_HDR_STATE_BUTTON_H

#include "engine/window_manager/hdr/button.h"
#include <memory>
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>

namespace window_manager
{

class StateButton: public Button
{
    bool state{false}; // enum
    std::string current_text;

public:
    template <typename... Args>
    StateButton(Args&&... args) : Button(std::forward<Args>(args)...) {
        const float current_width = text_->getGlobalBounds().width;
        current_text = text_->getString().toAnsiString();
        text_->setString(current_text + ": OFF");
        
        const float new_width = text_->getGlobalBounds().width;
        text_->move({(new_width - current_width) / (-2.f), 0});
    }

    void onClick() override
    {
        state = !state;
        const std::string state_description = state ? ": ON" : ": OFF";
        text_->setString(current_text + state_description);
        Button::onClick();
    }

    bool getState() { return state; }
};

}  // window_manager
#endif  // ENGINE_WINDOW_MANAGER_HDR_STATE_BUTTON_H