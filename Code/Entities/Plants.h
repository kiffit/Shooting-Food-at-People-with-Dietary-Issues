#ifndef PLANTS_H
#define PLANTS_H
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Window/Mouse.hpp"
#include "Entity.h"
#include "../World.h"

#define REGULAR_HITBOX_WIDTH 100
#define REGULAR_HITBOX_HEIGHT 100

/* ------------------------------------------------------------------------------------------------ */
/* REGULAR COMPONENTS */
/* ------------------------------------------------------------------------------------------------ */
class RegularInputComponent final : public InputComponent {
public:
    void update(Entity &entity, World &world) override {
    }
};

class RegularPhysicsComponent final : public PhysicsComponent {
public:
    void update(Entity &entity, World &world, const float elapsed) override {
        entity.position += entity.velocity * elapsed;
    }

    sf::FloatRect getHitbox(Entity &entity) const override {
        return {entity.position, {REGULAR_HITBOX_WIDTH, REGULAR_HITBOX_HEIGHT}};
    }
};

class RegularGraphicsComponent final : public GraphicsComponent {
public:
    void update(Entity &entity, float elapsed) override {
    }

    std::shared_ptr<sf::Drawable> drawable(Entity &entity) override {
        auto rect = std::make_shared<sf::RectangleShape>(sf::Vector2f(REGULAR_HITBOX_WIDTH, REGULAR_HITBOX_HEIGHT));
        rect->setPosition(entity.position);
        rect->setFillColor(sf::Color::Green);
        return rect;
    }
};

inline Entity *createRegularGuy() {
    return new Entity(new RegularInputComponent(), new RegularPhysicsComponent(), new RegularGraphicsComponent());
}

/* ------------------------------------------------------------------------------------------------ */
/* DRAG COMPONENTS */
/* ------------------------------------------------------------------------------------------------ */
class DraggableInputComponent final : public InputComponent {
public:
    void update(Entity &entity, World &world) override {
        const auto mousePos = sf::Vector2f(sf::Mouse::getPosition(*world.getWindow()));
        const auto hitbox = entity.getPhysicsComponent()->getHitbox(entity);
        const bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

        if (isPressed) {
            // If initial click inside entity, yoink
            if (!dragging_last && !dragging && hitbox.contains(mousePos)) {
                dragging = true;
            }

            // Then we be offsetting it
            if (dragging) {
                entity.velocity = mousePos - hitbox.size / 2.0f;
            }
        } else {
            dragging = false;
        }

        dragging_last = isPressed;
    }

private:
    bool dragging = false;
    bool dragging_last = false;
};

class DraggablePhysicsComponent final : public PhysicsComponent {
public:
    void update(Entity &entity, World &world, const float elapsed) override {
        entity.position = entity.velocity;
    }

    sf::FloatRect getHitbox(Entity &entity) const override {
        return {entity.position, {REGULAR_HITBOX_WIDTH, REGULAR_HITBOX_HEIGHT}};
    }
};

inline Entity *createDraggableGuy() {
    return new Entity(new DraggableInputComponent(), new DraggablePhysicsComponent(), new RegularGraphicsComponent());
}

#endif //PLANTS_H
