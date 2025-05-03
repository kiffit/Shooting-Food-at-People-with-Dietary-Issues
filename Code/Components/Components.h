#ifndef COMPONENTS_H
#define COMPONENTS_H
#include "SFML/Graphics/Drawable.hpp"

// Forward declarations
class Entity;
class World;

/// Input abstraction, allowing player control or AI control.
class MovementComponent {
public:
    virtual ~MovementComponent() = default;
    virtual void update(Entity &entity, World &world, float elapsed) = 0;
};


/// Attack abstraction for letting custom attacks occur.
class AttackComponent {
public:
    virtual ~AttackComponent() = default;
    virtual void update(Entity &entity, World &world, float elapsed) = 0;
    virtual void onCollision(Entity &entity, Entity &other) = 0;
};

/// Graphics abstraction, responsible for providing a pointer to a renderable object through get_drawable()
class GraphicsComponent {
public:
    virtual ~GraphicsComponent() = default;
    virtual void update(Entity &entity, float elapsed) = 0;
    virtual const sf::Drawable &drawable(Entity &entity) = 0;
};

#endif //COMPONENTS_H
