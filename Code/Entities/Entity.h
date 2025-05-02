#ifndef ENTITY_H
#define ENTITY_H
#include "../Components/Components.h"
#include "SFML/System/Vector2.hpp"

class Entity {
public:
    // Public attributes
    sf::Vector2f position{0, 0};
    sf::Vector2f velocity{0, 0};
    float health = 1;

    // Constructor
    Entity(InputComponent *input, PhysicsComponent *physics, GraphicsComponent *graphics)
        : input_(input), physics_(physics), graphics_(graphics) {
    }

    // Methods
    void update(World &world, const float elapsed) {
        input_->update(*this, world);
        physics_->update(*this, world, elapsed);
        graphics_->update(*this, elapsed);
    }

    // Getters
    [[nodiscard]] InputComponent *getInputComponent() const {
        return input_;
    }

    [[nodiscard]] PhysicsComponent *getPhysicsComponent() const {
        return physics_;
    }

    [[nodiscard]] GraphicsComponent *getGraphicsComponent() const {
        return graphics_;
    }

private:
    InputComponent *input_;
    PhysicsComponent *physics_;
    GraphicsComponent *graphics_;
};

#endif //ENTITY_H
