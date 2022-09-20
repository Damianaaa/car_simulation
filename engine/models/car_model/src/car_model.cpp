#include "engine/models/car_model/hdr/car_model.h"

CarModel::CarModel(const std::string& texture_path)
{
    if(!texture_.loadFromFile(texture_path))
        throw;
    sprite_->setTexture(texture_);
    setPose({18, 38}); // Default values for now
    movement_handler_ = std::make_unique<physics::mh::CarMovementHandler>(
        *sprite_.get(), physics::constants::base_vel, physics::constants::base_rot);
}

void CarModel::update() // Probably in the future it will get bigger
{
    movement_handler_->update();
}