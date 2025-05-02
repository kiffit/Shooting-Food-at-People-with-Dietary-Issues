#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <memory>
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Rect.hpp"

// Forward declarations
class Entity;
class World;

/// Input abstraction, allowing player control or AI control.
class InputComponent {
public:
    virtual ~InputComponent() = default;
    virtual void update(Entity &entity, World &world) = 0;
};

/// Physics abstraction, allowing custom movement patterns and providing the hitbox.
class PhysicsComponent {
public:
    virtual ~PhysicsComponent() = default;
    virtual void update(Entity &entity, World &world, float elapsed) = 0;
    virtual sf::FloatRect getHitbox(Entity &entity) const = 0;
};

/// Graphics abstraction, responsible for providing a pointer to a renderable object through get_drawable()
class GraphicsComponent {
public:
    virtual ~GraphicsComponent() = default;
    virtual void update(Entity &entity, float elapsed) = 0;
    virtual std::shared_ptr<sf::Drawable> drawable(Entity &entity) = 0;
};

#endif //COMPONENTS_H
