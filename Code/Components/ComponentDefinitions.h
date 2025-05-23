// ReSharper disable CppDFAUnreachableCode
// ReSharper disable CppDFAConstantConditions
#ifndef PLANTS_H
#define PLANTS_H
#include <functional>
#include <cmath>
#include "SFML/Graphics/RectangleShape.hpp"
#include "../Entities/Entity.h"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

#define PLANT_HITBOX_WIDTH 100
#define PLANT_HITBOX_HEIGHT 100

#define ZOMBIE_HITBOX_WIDTH 100
#define ZOMBIE_HITBOX_HEIGHT 100

#define PROJECTILE_HITBOX_WIDTH 50
#define PROJECTILE_HITBOX_HEIGHT 50

#define COMMON_TEXTURE_SIZE 100
#define PLANT_ANIMATION_TIME .25
#define ZOMBIE_ANIMATION_TIME .25

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
    PlantAttackComponent(const std::function<Entity *(sf::Vector2f)> &projectile_spawner, const std::string &sound_file_path, const float volume, const float interval)
        : interval_(interval), buffer_(sf::SoundBuffer(sound_file_path)), projectile_spawner_(projectile_spawner) {
        sound_.setVolume(volume);
    }

    void update(Entity &entity, World &world, const float elapsed) override {
        // Increment time
        time_ += elapsed;

        // Action upon time interval
        if (time_ >= interval_ && (!entity.row_based || world.canSeeZombie(entity))) {
            entity.attacking = true;
            world.addProjectile(projectile_spawner_({entity.hitbox.position.x, entity.hitbox.position.y + PLANT_HITBOX_HEIGHT / 2.f - PROJECTILE_HITBOX_HEIGHT / 4.f}));
            time_ = 0;
            sound_.play();
        } else
            entity.attacking = false;
    }

    void onCollision(Entity &entity, Entity &other) override {
    }

private:
    float time_ = 0;
    float interval_ = 0;
    sf::SoundBuffer buffer_;
    sf::Sound sound_ = sf::Sound(buffer_);
    std::function<Entity *(sf::Vector2f)> projectile_spawner_;
};

class PlantGraphicsComponent final : public GraphicsComponent {
public:
    PlantGraphicsComponent(const std::string &texture_idle_path, const std::string &texture_move_path,
                           const float anim_interval = PLANT_ANIMATION_TIME)
        : texture_idle_(new sf::Texture(texture_idle_path)), texture_move_(new sf::Texture(texture_move_path)),
          anim_interval_(anim_interval) {
        shape_.setSize({COMMON_TEXTURE_SIZE, COMMON_TEXTURE_SIZE});
        shape_.setTexture(texture_idle_);
    }

    void update(Entity &entity, const float elapsed) override {
        anim_time_ += elapsed;

        // Animation while attacking
        if (entity.attacking) {
            anim_time_ = 0;
            shape_.setTexture(texture_move_);
        } else if (anim_time_ > anim_interval_)
            shape_.setTexture(texture_idle_);
    }

    const sf::Drawable &drawable(Entity &entity) override {
        shape_.setPosition(entity.hitbox.position);
        return shape_;
    }

private:
    sf::RectangleShape shape_;
    sf::Texture *texture_idle_;
    sf::Texture *texture_move_;
    float anim_time_ = 0;
    float anim_interval_;
};

/* ------------------------------------------------------------------------------------------------ */
/* REGULAR ZOMBIE COMPONENTS */
/* ------------------------------------------------------------------------------------------------ */
class ZombieMovementComponent final : public MovementComponent {
public:
    explicit ZombieMovementComponent(const sf::Vector2f &velocity) : velocity_(velocity) {
    }

    void update(Entity &entity, World &world, const float elapsed) override {
        entity.hitbox.position += entity.velocity * elapsed;
        entity.velocity = velocity_;
    }

private:
    sf::Vector2f velocity_;
};

class ZombieAttackComponent final : public AttackComponent {
public:
    explicit ZombieAttackComponent(const float damage, const float interval) : damage_(damage), interval_(interval) {
    }

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
    ZombieGraphicsComponent(const std::string &texture_idle_path, const std::string &texture_move_path,
                            const float anim_interval = ZOMBIE_ANIMATION_TIME)
        : texture_idle_(new sf::Texture(texture_idle_path)), texture_move_(new sf::Texture(texture_move_path)),
          anim_interval_(anim_interval) {
        shape_.setSize({COMMON_TEXTURE_SIZE, COMMON_TEXTURE_SIZE});
        shape_.setTexture(texture_idle_);
    }

    void update(Entity &entity, const float elapsed) override {
        anim_time_ += elapsed;

        // Animation
        if (anim_time_ > anim_interval_) {
            anim_time_ = 0;

            if (shape_.getTexture() == texture_idle_)
                shape_.setTexture(texture_move_);
            else
                shape_.setTexture(texture_idle_);
        }
    }

    const sf::Drawable &drawable(Entity &entity) override {
        shape_.setPosition(entity.hitbox.position);
        return shape_;
    }

private:
    sf::RectangleShape shape_;
    sf::Texture *texture_idle_;
    sf::Texture *texture_move_;
    float anim_time_ = 0;
    float anim_interval_;
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
    explicit ProjectileAttackComponent(const float damage, const float lifetime = 0) : lifetime_(lifetime),
        damage_(damage) {
    }

    void update(Entity &entity, World &world, const float elapsed) override {
        time_ += elapsed;

        if (lifetime_ != 0 && time_ >= lifetime_)
            entity.health = -1;
    }

    void onCollision(Entity &entity, Entity &other) override {
        float damage = damage_;

        if (entity.damage_type == other.damage_type)
            damage *= 10;

        other.health -= damage;
        entity.health = -1;
    }

private:
    float lifetime_;
    float damage_;
    float time_ = 0;
};

class ProjectileGraphicsComponent final : public GraphicsComponent {
public:
    explicit ProjectileGraphicsComponent(const std::string &texture_path) : texture_idle_(
        new sf::Texture(texture_path)) {
        shape_.setSize({PROJECTILE_HITBOX_WIDTH, PROJECTILE_HITBOX_HEIGHT});
        shape_.setTexture(texture_idle_);
    }

    void update(Entity &entity, float) override {
    }

    const sf::Drawable &drawable(Entity &entity) override {
        shape_.setPosition(entity.hitbox.position);
        shape_.setSize(entity.hitbox.size);
        return shape_;
    }

private:
    sf::RectangleShape shape_;
    sf::Texture *texture_idle_;
};

/* ------------------------------------------------------------------------------------------------ */
/* STORE COMPONENTS */
/* ------------------------------------------------------------------------------------------------ */
class StoreMovementComponent final : public MovementComponent {
public:
    explicit StoreMovementComponent(const std::function<Entity *(sf::Vector2f)> &plant_spawner)
        : plant_spawner_(plant_spawner) {
    }

    void update(Entity &entity, World &world, float elapsed) override {
        const auto mousePos = world.getMousePosition();
        const auto hitbox = sf::FloatRect(entity.hitbox.position, entity.hitbox.size);
        const bool isPressed = world.getMousePressed();
        entity.health = 1000000;

        if (isPressed) {
            if (!dragging_last_ && !dragging_ && hitbox.contains(mousePos)) {
                dragging_ = true;
                offset_ = mousePos - entity.hitbox.position;
                old_position_ = entity.hitbox.position;
            }

            if (dragging_) {
                entity.hitbox.position = mousePos - offset_;
            }
        } else {
            if (dragging_) {
                const sf::Vector2f rawPos = mousePos - offset_;
                const sf::Vector2f snapped = {
                    std::round((rawPos.x - multiples_offset_.x) / multiples_.x) * multiples_.x + multiples_offset_.x,
                    std::round((rawPos.y - multiples_offset_.y) / multiples_.y) * multiples_.y + multiples_offset_.y
                };

                entity.hitbox.position = snapped;

                if (!world.touchesPlant(entity) && world.epipens >= entity.epipen_cost) {
                    world.epipens -= entity.epipen_cost;
                    Entity *spawned = plant_spawner_(entity.hitbox.position);
                    world.addPlant(spawned);
                }

                entity.hitbox.position = old_position_;
            }

            dragging_ = false;
        }

        dragging_last_ = isPressed;
    }

private:
    std::function<Entity *(sf::Vector2f)> plant_spawner_;
    bool dragging_ = false;
    bool dragging_last_ = false;
    sf::Vector2f multiples_{110, 110};
    sf::Vector2f multiples_offset_{10, -20};
    sf::Vector2f old_position_;
    sf::Vector2f offset_;
};

class StoreAttackComponent final : public AttackComponent {
public:
    void update(Entity &entity, World &world, float elapsed) override {}
    void onCollision(Entity &entity, Entity &other) override {}
};

/* ------------------------------------------------------------------------------------------------ */
/* CLICKABLE COMPONENT */
/* ------------------------------------------------------------------------------------------------ */
class ClickableMovementComponent final : public MovementComponent {
public:
    void update(Entity &entity, World &world, float elapsed) override {
        const auto mousePos = world.getMousePosition();
        const auto hitbox = sf::FloatRect(entity.hitbox.position, entity.hitbox.size);
        const bool isPressed = world.getMousePressed();

        if (isPressed) {
            if (!clicking_last_ && !clicking_ && hitbox.contains(mousePos)) {
                clicking_ = true;
                world.epipens += 1;
                entity.health = -1;
            }
        }

        entity.hitbox.position += entity.velocity * elapsed;
        entity.velocity *= (1 - elapsed);

        clicking_last_ = isPressed;
    }

private:
    bool clicking_ = false;
    bool clicking_last_ = true;
};

#endif //PLANTS_H
