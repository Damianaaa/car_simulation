#ifndef CAR_MODEL_H
#define CAR_MODEL_H

#include <SFML/Graphics.hpp>

#include "engine/physical_objects/physical_model/hdr/physical_model.h"

class IModel
{
protected:
    sf::Texture texture_;
    sf::Sprite sprite_;
    PhysicalModel p_model_;
    // CollisionModel c_model_;
public:
    void setPose(const sf::Vector2f& pose);
    const sf::Sprite& getSprite() const noexcept { return sprite_; }
    virtual void initializePhysicalModel() = 0;
    virtual ~IModel() = default;
};

// Builder? 
class CarModel: public IModel
{
private:
    // std::unique_ptr<ControlModel> 
    // std::vector<std::unique_ptr<Sensor>> This or any other way
public:
    CarModel();
    ~CarModel();
};

#endif
