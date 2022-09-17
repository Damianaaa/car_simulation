#ifndef CAR_MODEL_H
#define CAR_MODEL_H

#include <memory.h>
#include <SFML/Graphics.hpp>

#include "engine/physical_objects/physical_model/hdr/physical_model.h"
#include "engine/physics/movement_handler/hdr/movement_handler.h"
#include "engine/physics/constants/hdr/constants.h"

class IModel
{
protected:
    sf::Texture texture_;
    sf::Sprite sprite_;
    // PhysicalModel p_model_;
    // CollisionModel c_model_;

public:
    const sf::Sprite& getSprite() const noexcept { return sprite_; }
    void setPose(const sf::Vector2f& pose) { sprite_.setOrigin(pose); };
    // virtual void initializePhysicalModel() = 0;
    virtual ~IModel() = default;
};

class IDynamicModel: public IModel
{
  protected:
    std::unique_ptr<physics::mh::IMovementHandler> movement_handler_;
  public:
    virtual ~IDynamicModel() = default;
};

class CarModel: public IDynamicModel
{
  private:
    // std::vector<std::unique_ptr<Sensor>> This or any other way
  public:
    explicit CarModel(const std::string& texture_path);

    void update();
};

#endif
