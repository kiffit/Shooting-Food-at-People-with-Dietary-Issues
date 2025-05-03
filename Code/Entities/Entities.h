#ifndef ENTITYHELPERS_H
#define ENTITYHELPERS_H
#include "../Components/ComponentDefinitions.h"

/* ------------------------------------------------------------------------------------------------ */
/* PROJECTILES */
/* ------------------------------------------------------------------------------------------------ */
inline Entity *sugarCubeProjectile(const sf::Vector2f &position) {
    constexpr sf::Vector2f velocity = {300, 0};
    constexpr sf::Vector2f hitbox_size = {PROJECTILE_HITBOX_WIDTH, PROJECTILE_HITBOX_HEIGHT};
    constexpr float damage = 1;

    const auto entity = new Entity(new ProjectileMovementComponent(velocity), new ProjectileAttackComponent(damage), new ProjectileGraphicsComponent());
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->damage_type = "sugar";

    return entity;
};

/* ------------------------------------------------------------------------------------------------ */
/* PLANTS */
/* ------------------------------------------------------------------------------------------------ */
inline Entity *sugarCubePlant(const sf::Vector2f &position) {
    constexpr float interval = 2;
    constexpr sf::Vector2f hitbox_size = {PLANT_HITBOX_WIDTH, PLANT_HITBOX_HEIGHT};
    constexpr float health = 10;

    const auto entity = new Entity(new DraggableMovementComponent(), new PlantAttackComponent(sugarCubeProjectile, interval), new PlantGraphicsComponent());
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->health = health;

    return entity;
};

/* ------------------------------------------------------------------------------------------------ */
/* ZOMBIES */
/* ------------------------------------------------------------------------------------------------ */
inline Entity *diabeticZombie(const sf::Vector2f &position) {
    constexpr float interval = 2;
    constexpr float damage = 3;
    constexpr sf::Vector2f hitbox_size = {PLANT_HITBOX_WIDTH, PLANT_HITBOX_HEIGHT};
    constexpr float health = 10;

    const auto entity = new Entity(new ZombieMovementComponent(), new ZombieAttackComponent(damage, interval), new ZombieGraphicsComponent());
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->health = health;
    entity->damage_type = "sugar";

    return entity;
};

#endif //ENTITYHELPERS_H
