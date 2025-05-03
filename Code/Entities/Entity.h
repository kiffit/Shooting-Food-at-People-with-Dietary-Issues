#ifndef ENTITY_H
#define ENTITY_H
#include "../Components/Components.h"
#include "SFML/System/Vector2.hpp"

class Entity {
public:
    // Public attributes
    sf::FloatRect hitbox;
    sf::Vector2f velocity;
    std::string damage_type;
    float health = 1;


    // Constructor
    Entity(MovementComponent *movement, AttackComponent *attack, GraphicsComponent *graphics)
        : movement_(movement), attack_(attack), graphics_(graphics) {
    }

    // Methods
    void update(World &world, const float elapsed) {
        movement_->update(*this, world, elapsed);
        attack_->update(*this, world, elapsed);
        graphics_->update(*this, elapsed);
    }

    void resolveCollision(Entity &other) {
        attack_->onCollision(*this, other);
    }

    const sf::Drawable *getDrawable() {
        return &graphics_->drawable(*this);
    }

private:
    MovementComponent *movement_;
    AttackComponent *attack_;
    GraphicsComponent *graphics_;
};

#endif //ENTITY_H
