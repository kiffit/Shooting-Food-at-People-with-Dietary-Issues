#ifndef ENTITYHELPERS_H
#define ENTITYHELPERS_H
#include "../Components/ComponentDefinitions.h"

/* ------------------------------------------------------------------------------------------------ */
/* PROJECTILES */
/* ------------------------------------------------------------------------------------------------ */
inline Entity *epipenProjectile(const sf::Vector2f &position) {
    constexpr sf::Vector2f hitbox_size = {PROJECTILE_HITBOX_WIDTH, PROJECTILE_HITBOX_HEIGHT};
    constexpr sf::Vector2f velocity = {0, 50};

    const auto entity = new Entity(new ClickableMovementComponent(), new ProjectileAttackComponent(0, 6), new ProjectileGraphicsComponent());
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->velocity = velocity;
    return entity;
};

inline Entity *soybeanMinigunProjectile(const sf::Vector2f &position) {
    constexpr sf::Vector2f velocity = {1000, 0};
    constexpr sf::Vector2f hitbox_size = {PROJECTILE_HITBOX_WIDTH, PROJECTILE_HITBOX_HEIGHT};
    constexpr float damage = 0.2;

    const auto entity = new Entity(new ProjectileMovementComponent(velocity), new ProjectileAttackComponent(damage), new ProjectileGraphicsComponent());
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->damage_type = "soy";
    return entity;
};

inline Entity *baguetteProjectile(const sf::Vector2f &position) {
    constexpr sf::Vector2f velocity = {400, 0};
    constexpr sf::Vector2f hitbox_size = {PROJECTILE_HITBOX_WIDTH, PROJECTILE_HITBOX_HEIGHT};
    constexpr float damage = 4;

    const auto entity = new Entity(new ProjectileMovementComponent(velocity), new ProjectileAttackComponent(damage), new ProjectileGraphicsComponent());
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->damage_type = "gluten";
    return entity;
};

/* ------------------------------------------------------------------------------------------------ */
/* PLANTS */
/* ------------------------------------------------------------------------------------------------ */
inline Entity *epipenPlant(const sf::Vector2f &position) {
    constexpr float interval = 18;
    constexpr sf::Vector2f hitbox_size = {PLANT_HITBOX_WIDTH, PLANT_HITBOX_HEIGHT};
    constexpr float health = 20;
    constexpr float epipens = 2;

    const auto entity = new Entity(new DraggableMovementComponent(), new PlantAttackComponent(epipenProjectile, interval), new PlantGraphicsComponent("../Code/Entities/Sprites/sharps_0.png", "../Code/Entities/Sprites/sharps_1.png"));
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->health = health;
    entity->epipen_cost = epipens;
    entity->row_based = false;
    return entity;
};

inline Entity *soybeanMinigunPlant(const sf::Vector2f &position) {
    constexpr float interval = 0.1;
    constexpr sf::Vector2f hitbox_size = {PLANT_HITBOX_WIDTH, PLANT_HITBOX_HEIGHT};
    constexpr float health = 10;
    constexpr float epipens = 10;

    const auto entity = new Entity(new DraggableMovementComponent(), new PlantAttackComponent(soybeanMinigunProjectile, interval), new PlantGraphicsComponent("../Code/Entities/Sprites/soy_minigun_0.png", "../Code/Entities/Sprites/soy_minigun_1.png", interval / 2));
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->health = health;
    entity->epipen_cost = epipens;
    return entity;
};

inline Entity *baguettePlant(const sf::Vector2f &position) {
    constexpr float interval = 2;
    constexpr sf::Vector2f hitbox_size = {PLANT_HITBOX_WIDTH, PLANT_HITBOX_HEIGHT};
    constexpr float health = 8;
    constexpr float epipens = 4;

    const auto entity = new Entity(new DraggableMovementComponent(), new PlantAttackComponent(baguetteProjectile, interval), new PlantGraphicsComponent("../Code/Entities/Sprites/baguette_0.png", "../Code/Entities/Sprites/baguette_1.png"));
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->health = health;
    entity->epipen_cost = epipens;
    return entity;
};

/* ------------------------------------------------------------------------------------------------ */
/* ZOMBIES */
/* ------------------------------------------------------------------------------------------------ */
inline Entity *soyZombie(const sf::Vector2f &position) {
    constexpr float interval = 2;
    constexpr float damage = 3;
    constexpr sf::Vector2f hitbox_size = {ZOMBIE_HITBOX_WIDTH, ZOMBIE_HITBOX_HEIGHT};
    constexpr float health = 10;

    const auto entity = new Entity(new ZombieMovementComponent({-100, 0}), new ZombieAttackComponent(damage, interval), new ZombieGraphicsComponent("../Code/Entities/Sprites/soyboy_0.png", "../Code/Entities/Sprites/soyboy_1.png"));
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->health = health;
    entity->damage_type = "soy";
    return entity;
};

inline Entity *glutenZombie(const sf::Vector2f &position) {
    constexpr float interval = 1;
    constexpr float damage = 1;
    constexpr sf::Vector2f hitbox_size = {ZOMBIE_HITBOX_WIDTH, ZOMBIE_HITBOX_HEIGHT};
    constexpr float health = 10;

    const auto entity = new Entity(new ZombieMovementComponent({-50, 0}), new ZombieAttackComponent(damage, interval), new ZombieGraphicsComponent("../Code/Entities/Sprites/gluten_0.png", "../Code/Entities/Sprites/gluten_1.png"));
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->health = health;
    entity->damage_type = "gluten";
    return entity;
};

#endif //ENTITYHELPERS_H
