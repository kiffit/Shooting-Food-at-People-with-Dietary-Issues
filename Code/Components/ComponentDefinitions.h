// ReSharper disable CppDFAUnreachableCode
// ReSharper disable CppDFAConstantConditions
#ifndef PLANTS_H
#define PLANTS_H
#include <functional>
#include "SFML/Graphics/RectangleShape.hpp"
#include "../Entities/Entity.h"

#define PLANT_HITBOX_WIDTH 100
#define PLANT_HITBOX_HEIGHT 100

#define ZOMBIE_HITBOX_WIDTH 100
#define ZOMBIE_HITBOX_HEIGHT 100

#define PROJECTILE_HITBOX_WIDTH 50
#define PROJECTILE_HITBOX_HEIGHT 50

/* ------------------------------------------------------------------------------------------------ */
/* REGULAR PLANT COMPONENTS */
/* ------------------------------------------------------------------------------------------------ */
class PlantMovementComponent final : public MovementComponent {
public:
    void update(Entity &entity, World &world, float elapsed) override {
    }
};

class PlantAttackComponent final : public AttackComponent {
public:
    PlantAttackComponent(const std::function<Entity *(sf::Vector2f)> &projectile_spawner, const float interval)
    : interval_(interval), projectile_spawner_(projectile_spawner) {
    }

    void update(Entity &entity, World &world, const float elapsed) override {
        // Increment time
        time_ += elapsed;

        // Action upon time interval
        if (time_ >= interval_) {
            world.addProjectile(projectile_spawner_(entity.hitbox.position));
            time_ = 0;
        }
    }

    void onCollision(Entity &entity, Entity &other) override {
    }

private:
    float time_ = 0;
    float interval_ = 0;
    std::function<Entity *(sf::Vector2f)> projectile_spawner_;
};

class PlantGraphicsComponent final : public GraphicsComponent {
public:
    PlantGraphicsComponent() {
        shape_.setSize({PLANT_HITBOX_WIDTH, PLANT_HITBOX_HEIGHT});
        shape_.setFillColor(sf::Color::Green);
    }

    void update(Entity &entity, float) override {
        shape_.setPosition(entity.hitbox.position);
    }

    const sf::Drawable &drawable(Entity &entity) override {
        shape_.setPosition(entity.hitbox.position);
        return shape_;
    }

private:
    sf::RectangleShape shape_;
};

/* ------------------------------------------------------------------------------------------------ */
/* REGULAR ZOMBIE COMPONENTS */
/* ------------------------------------------------------------------------------------------------ */
class ZombieMovementComponent final : public MovementComponent {
public:
    void update(Entity &entity, World &world, const float elapsed) override {
        entity.hitbox.position += entity.velocity * elapsed;
        entity.velocity = {-100, 0};
    }
};

class ZombieAttackComponent final : public AttackComponent {
public:
    explicit ZombieAttackComponent(const float damage, const float interval) : damage_(damage), interval_(interval) {}

    void update(Entity &entity, World &world, const float elapsed) override {
        time_ += elapsed;
    }

    void onCollision(Entity &entity, Entity &other) override {
        entity.velocity = {0, 0};

        if (time_ >= 1) {
            other.health -= damage_;
            time_ = 0;
        }
    }

private:
    float time_ = 0;
    float damage_;
    float interval_;
};

class ZombieGraphicsComponent final : public GraphicsComponent {
public:
    ZombieGraphicsComponent() {
        shape_.setSize({ZOMBIE_HITBOX_WIDTH, ZOMBIE_HITBOX_HEIGHT});
        shape_.setFillColor(sf::Color::Red);
    }

    void update(Entity &entity, float) override {
        shape_.setPosition(entity.hitbox.position);
    }

    const sf::Drawable &drawable(Entity &entity) override {
        shape_.setPosition(entity.hitbox.position);
        return shape_;
    }

private:
    sf::RectangleShape shape_;
};

/* ------------------------------------------------------------------------------------------------ */
/* REGULAR PROJECTILE COMPONENTS */
/* ------------------------------------------------------------------------------------------------ */
class ProjectileMovementComponent final : public MovementComponent {
public:
    explicit ProjectileMovementComponent(const sf::Vector2f &velocity) : velocity_(velocity) {
    }

    void update(Entity &entity, World &world, const float elapsed) override {
        entity.hitbox.position += velocity_ * elapsed;
    }

private:
    sf::Vector2f velocity_;
};

class ProjectileAttackComponent final : public AttackComponent {
public:
    explicit ProjectileAttackComponent(const float damage) : damage_(damage) {}

    void update(Entity &entity, World &world, float elapsed) override {}

    void onCollision(Entity &entity, Entity &other) override {
        float damage = damage_;

        if (entity.damage_type == other.damage_type)
            damage *= 3;

        other.health -= damage;
        entity.health = -1;
    }

private:
    float damage_;
};

class ProjectileGraphicsComponent final : public GraphicsComponent {
public:
    ProjectileGraphicsComponent() {
        shape_.setSize({PROJECTILE_HITBOX_WIDTH, PROJECTILE_HITBOX_HEIGHT});
        shape_.setFillColor(sf::Color::Blue);
    }

    void update(Entity &entity, float) override {
        shape_.setPosition(entity.hitbox.position);
    }

    const sf::Drawable &drawable(Entity &entity) override {
        shape_.setPosition(entity.hitbox.position);
        return shape_;
    }

private:
    sf::RectangleShape shape_;
};

/* ------------------------------------------------------------------------------------------------ */
/* DRAG COMPONENTS */
/* ------------------------------------------------------------------------------------------------ */
class DraggableMovementComponent final : public MovementComponent {
public:
    void update(Entity &entity, World &world, float elapsed) override {
        const auto mousePos = world.getMousePosition();
        const auto hitbox = sf::FloatRect(entity.hitbox.position, entity.hitbox.size);
        const bool isPressed = world.getMousePressed();

        if (isPressed) {
            if (!dragging_last_ && !dragging_ && hitbox.contains(mousePos)) {
                dragging_ = true;
                offset_ = mousePos - entity.hitbox.position;
            }

            if (dragging_) {
                entity.hitbox.position = mousePos - offset_;
            }
        } else {
            dragging_ = false;
        }

        dragging_last_ = isPressed;
    }

private:
    bool dragging_ = false;
    bool dragging_last_ = false;
    sf::Vector2f offset_;
};

#endif //PLANTS_H
