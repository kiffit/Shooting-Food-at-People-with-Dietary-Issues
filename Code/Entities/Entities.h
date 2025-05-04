#ifndef ENTITYHELPERS_H
#define ENTITYHELPERS_H
#include "../Components/ComponentDefinitions.h"

/* ------------------------------------------------------------------------------------------------ */
/* PROJECTILES */
/* ------------------------------------------------------------------------------------------------ */
inline Entity *epipenProjectile(const sf::Vector2f &position) {
    constexpr sf::Vector2f hitbox_size = {PLANT_HITBOX_WIDTH, PLANT_HITBOX_HEIGHT};
    constexpr sf::Vector2f velocity = {20, -50};

    const auto entity = new Entity(new ClickableMovementComponent(), new ProjectileAttackComponent(0, 6),
                                   new ProjectileGraphicsComponent("../Design/Sprites/epipen.png"));
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->velocity = velocity;
    return entity;
};

inline Entity *soybeanMinigunProjectile(const sf::Vector2f &position) {
    constexpr sf::Vector2f velocity = {2000, 0};
    constexpr sf::Vector2f hitbox_size = {PROJECTILE_HITBOX_WIDTH, PROJECTILE_HITBOX_HEIGHT};
    constexpr float damage = 0.2;

    const auto entity = new Entity(new ProjectileMovementComponent(velocity), new ProjectileAttackComponent(damage),
                                   new ProjectileGraphicsComponent("../Design/Sprites/soybean.png"));
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->damage_type = "soy";
    return entity;
};

inline Entity *baguetteProjectile(const sf::Vector2f &position) {
    constexpr sf::Vector2f velocity = {800, 0};
    constexpr sf::Vector2f hitbox_size = {PROJECTILE_HITBOX_WIDTH, PROJECTILE_HITBOX_HEIGHT};
    constexpr float damage = 0.6;

    const auto entity = new Entity(new ProjectileMovementComponent(velocity), new ProjectileAttackComponent(damage),
                                   new ProjectileGraphicsComponent("../Design/Sprites/baguette.png"));
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->damage_type = "gluten";
    return entity;
};

inline Entity *milkProjectile(const sf::Vector2f &position) {
    constexpr sf::Vector2f velocity = {1000, 0};
    constexpr sf::Vector2f hitbox_size = {PROJECTILE_HITBOX_WIDTH, PROJECTILE_HITBOX_HEIGHT};
    constexpr float damage = 0.8;

    const auto entity = new Entity(new ProjectileMovementComponent(velocity), new ProjectileAttackComponent(damage),
                                   new ProjectileGraphicsComponent("../Design/Sprites/milk.png"));
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->damage_type = "milk";
    return entity;
};

inline Entity *peanutProjectile(const sf::Vector2f &position) {
    constexpr sf::Vector2f velocity = {900, 0};
    constexpr sf::Vector2f hitbox_size = {PROJECTILE_HITBOX_WIDTH, PROJECTILE_HITBOX_HEIGHT};
    constexpr float damage = 1.2;

    const auto entity = new Entity(new ProjectileMovementComponent(velocity), new ProjectileAttackComponent(damage),
                                   new ProjectileGraphicsComponent("../Design/Sprites/peanut.png"));
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->damage_type = "peanut";
    return entity;
};

/* ------------------------------------------------------------------------------------------------ */
/* PLANTS */
/* ------------------------------------------------------------------------------------------------ */
inline Entity *epipenPlant(const sf::Vector2f &position) {
    constexpr float interval = 2;
    constexpr sf::Vector2f hitbox_size = {PLANT_HITBOX_WIDTH, PLANT_HITBOX_HEIGHT};
    constexpr float health = 20;

    const auto entity = new Entity(new PlantMovementComponent(),
                                   new PlantAttackComponent(epipenProjectile, "../Design/Sounds/epipen.mp3", 40, interval),
                                   new PlantGraphicsComponent("../Design/Sprites/sharps_0.png",
                                                              "../Design/Sprites/sharps_1.png"));
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->health = health;
    entity->row_based = false;
    return entity;
};

inline Entity *soybeanMinigunPlant(const sf::Vector2f &position) {
    constexpr float interval = 0.1;
    constexpr sf::Vector2f hitbox_size = {PLANT_HITBOX_WIDTH, PLANT_HITBOX_HEIGHT};
    constexpr float health = 10;
    constexpr float epipens = 10;

    const auto entity = new Entity(new PlantMovementComponent(),
                                   new PlantAttackComponent(soybeanMinigunProjectile, "../Design/Sounds/soybean.mp3", 10, interval),
                                   new PlantGraphicsComponent("../Design/Sprites/soy_minigun_0.png",
                                                              "../Design/Sprites/soy_minigun_1.png", interval / 2));
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->health = health;
    entity->epipen_cost = epipens;
    return entity;
};

inline Entity *baguettePlant(const sf::Vector2f &position) {
    constexpr float interval = 1;
    constexpr sf::Vector2f hitbox_size = {PLANT_HITBOX_WIDTH, PLANT_HITBOX_HEIGHT};
    constexpr float health = 8;

    const auto entity = new Entity(new PlantMovementComponent(),
                                   new PlantAttackComponent(baguetteProjectile, "../Design/Sounds/pistol.mp3", 4, interval),
                                   new PlantGraphicsComponent("../Design/Sprites/baguette_launcher_0.png",
                                                              "../Design/Sprites/baguette_launcher_1.png",
                                                              interval / 2));
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->health = health;
    return entity;
};

inline Entity *milkPlant(const sf::Vector2f &position) {
    constexpr float interval = 2;
    constexpr sf::Vector2f hitbox_size = {PLANT_HITBOX_WIDTH, PLANT_HITBOX_HEIGHT};
    constexpr float health = 8;

    const auto entity = new Entity(new PlantMovementComponent(),
                                   new PlantAttackComponent(milkProjectile, "../Design/Sounds/milk.mp3", 10, interval),
                                   new PlantGraphicsComponent("../Design/Sprites/milk_catapult_0.png",
                                                              "../Design/Sprites/milk_catapult_1.png",
                                                              interval / 2));
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->health = health;
    return entity;
};

inline Entity *peanutPlant(const sf::Vector2f &position) {
    constexpr float interval = 4;
    constexpr sf::Vector2f hitbox_size = {PLANT_HITBOX_WIDTH, PLANT_HITBOX_HEIGHT};
    constexpr float health = 8;

    const auto entity = new Entity(new PlantMovementComponent(),
                                   new PlantAttackComponent(peanutProjectile, "../Design/Sounds/pistol.mp3", 10, interval),
                                   new PlantGraphicsComponent("../Design/Sprites/peanut_turret_1.png",
                                                              "../Design/Sprites/peanut_turret_0.png",
                                                              interval / 2));
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->health = health;
    return entity;
};

/* ------------------------------------------------------------------------------------------------ */
/* STORE PLANTS */
/* ------------------------------------------------------------------------------------------------ */
inline Entity *epipenPlantStore(const sf::Vector2f &position) {
    constexpr sf::Vector2f hitbox_size = {PLANT_HITBOX_WIDTH, PLANT_HITBOX_HEIGHT};
    constexpr float health = 1000000;
    constexpr float epipens = 2;

    const auto entity = new Entity(new StoreMovementComponent(epipenPlant),
                                   new StoreAttackComponent(),
                                   new PlantGraphicsComponent("../Design/Sprites/sharps_0.png",
                                                              "../Design/Sprites/sharps_1.png"));
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->health = health;
    entity->epipen_cost = epipens;
    entity->row_based = false;
    return entity;
};

inline Entity *soybeanMinigunPlantStore(const sf::Vector2f &position) {
    constexpr sf::Vector2f hitbox_size = {PLANT_HITBOX_WIDTH, PLANT_HITBOX_HEIGHT};
    constexpr float health = 1000000;
    constexpr float epipens = 10;

    const auto entity = new Entity(new StoreMovementComponent(soybeanMinigunPlant),
                                   new StoreAttackComponent(),
                                   new PlantGraphicsComponent("../Design/Sprites/soy_minigun_0.png",
                                                              "../Design/Sprites/soy_minigun_1.png"));
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->health = health;
    entity->epipen_cost = epipens;
    return entity;
};

inline Entity *baguetteStore(const sf::Vector2f &position) {
    constexpr sf::Vector2f hitbox_size = {PLANT_HITBOX_WIDTH, PLANT_HITBOX_HEIGHT};
    constexpr float health = 1000000;
    constexpr float epipens = 4;

    const auto entity = new Entity(new StoreMovementComponent(baguettePlant),
                                   new StoreAttackComponent(),
                                   new PlantGraphicsComponent("../Design/Sprites/baguette_launcher_0.png",
                                                              "../Design/Sprites/baguette_launcher_1.png"));
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->health = health;
    entity->epipen_cost = epipens;
    return entity;
};

inline Entity *milkStore(const sf::Vector2f &position) {
    constexpr sf::Vector2f hitbox_size = {PLANT_HITBOX_WIDTH, PLANT_HITBOX_HEIGHT};
    constexpr float health = 1000000;
    constexpr float epipens = 6;

    const auto entity = new Entity(new StoreMovementComponent(milkPlant),
                                   new StoreAttackComponent(),
                                   new PlantGraphicsComponent("../Design/Sprites/milk_catapult_0.png",
                                                              "../Design/Sprites/milk_catapult_1.png"));
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->health = health;
    entity->epipen_cost = epipens;
    return entity;
};

inline Entity *peanutStore(const sf::Vector2f &position) {
    constexpr sf::Vector2f hitbox_size = {PLANT_HITBOX_WIDTH, PLANT_HITBOX_HEIGHT};
    constexpr float health = 1000000;
    constexpr float epipens = 6;

    const auto entity = new Entity(new StoreMovementComponent(peanutPlant),
                                   new StoreAttackComponent(),
                                   new PlantGraphicsComponent("../Design/Sprites/peanut_turret_0.png",
                                                              "../Design/Sprites/peanut_turret_1.png"));
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
    constexpr float interval = 1;
    constexpr float damage = 1;
    constexpr sf::Vector2f hitbox_size = {ZOMBIE_HITBOX_WIDTH, ZOMBIE_HITBOX_HEIGHT};
    constexpr float health = 20;

    const auto entity = new Entity(new ZombieMovementComponent({-100, 0}), new ZombieAttackComponent(damage, interval),
                                   new ZombieGraphicsComponent("../Design/Sprites/soyboy_0.png",
                                                               "../Design/Sprites/soyboy_1.png"));
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
    constexpr float health = 20;

    const auto entity = new Entity(new ZombieMovementComponent({-50, 0}), new ZombieAttackComponent(damage, interval),
                                   new ZombieGraphicsComponent("../Design/Sprites/gluten_grandma_0.png",
                                                               "../Design/Sprites/gluten_grandma_1.png"));
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->health = health;
    entity->damage_type = "gluten";
    return entity;
};

inline Entity *milkZombie(const sf::Vector2f &position) {
    constexpr float interval = 1;
    constexpr float damage = 1;
    constexpr sf::Vector2f hitbox_size = {ZOMBIE_HITBOX_WIDTH, ZOMBIE_HITBOX_HEIGHT};
    constexpr float health = 30;

    const auto entity = new Entity(new ZombieMovementComponent({-25, 0}), new ZombieAttackComponent(damage, interval),
                                   new ZombieGraphicsComponent("../Design/Sprites/diabetic_dave_0.png",
                                                               "../Design/Sprites/diabetic_dave_1.png"));
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->health = health;
    entity->damage_type = "milk";
    return entity;
};

inline Entity *peanutZombie(const sf::Vector2f &position) {
    constexpr float interval = 1;
    constexpr float damage = 1;
    constexpr sf::Vector2f hitbox_size = {ZOMBIE_HITBOX_WIDTH, ZOMBIE_HITBOX_HEIGHT};
    constexpr float health = 10;

    const auto entity = new Entity(new ZombieMovementComponent({-200, 0}), new ZombieAttackComponent(damage, interval),
                                   new ZombieGraphicsComponent("../Design/Sprites/peanut_patty_0.png",
                                                               "../Design/Sprites/peanut_patty_1.png"));
    entity->hitbox.position = position;
    entity->hitbox.size = hitbox_size;
    entity->health = health;
    entity->damage_type = "peanut";
    return entity;
};

#endif //ENTITYHELPERS_H
