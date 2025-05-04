#ifndef WORLD_H
#define WORLD_H
#include <algorithm>
#include <mutex>
#include "Entities/Entity.h"

class World {
public:
    // Attributes
    float time = 0;
    float epipens = 4;

    // Methods
    void update(const float elapsed, const sf::Vector2f &mouse_position, const bool mouse_pressed) {
        // Time
        time += elapsed;

        // Update mouse_position, mouse_pressed
        mouse_position_ = mouse_position;
        mouse_pressed_ = mouse_pressed;

        // Run through entity updates
        update_list(plants_, elapsed);
        update_list(projectiles_, elapsed);
        update_list(zombies_, elapsed);

        // Process collisions
        processCollisions();

        // Kill dead entities
        remove_dead(plants_);
        remove_dead(zombies_);
        remove_dead(projectiles_);
    }

    // Getting drawables for rendering
    std::vector<const sf::Drawable *> getPlantDrawables() {
        return collect_drawables(plants_);
    }

    std::vector<const sf::Drawable *> getZombieDrawables() {
        return collect_drawables(zombies_);
    }

    std::vector<const sf::Drawable *> getProjectileDrawables() {
        return collect_drawables(projectiles_);
    }

    // Getting mouse information for dragging
    [[nodiscard]] sf::Vector2f getMousePosition() const {
        return mouse_position_;
    }

    [[nodiscard]] bool getMousePressed() const {
        return mouse_pressed_;
    }

    // List access
    void addPlant(Entity *entity) {
        plants_.push_back(entity);
    }

    void addZombie(Entity *entity) {
        zombies_.push_back(entity);
    }

    void addProjectile(Entity *entity) {
        projectiles_.push_back(entity);
    }

    // Resolving collisions
    void processCollisions() const {
        for (const auto &zombie : zombies_) {
            // Projectiles hit zombies
            for (const auto &projectile : projectiles_) {
                if (zombie->hitbox.findIntersection(projectile->hitbox)) {
                    projectile->resolveCollision(*zombie);
                }
            }

            // Plant and zombie warfare
            for (const auto &plant : plants_) {
                if (zombie->hitbox.findIntersection(plant->hitbox)) {
                    plant->resolveCollision(*zombie);
                    zombie->resolveCollision(*plant);
                }
            }
        }

        // Kill OOB projectiles
        for (const auto &projectile : projectiles_) {
            if (!screen_hitbox_.findIntersection(projectile->hitbox))
                projectile->health = -1;
        }
    }

    [[nodiscard]] bool canSeeZombie(const Entity &entity) const {
        auto row_hitbox = entity.hitbox;
        row_hitbox.size.x = shoot_range_.size.x;
        row_hitbox.size.y = 1;
        row_hitbox.position.y += entity.hitbox.size.y / 2;

        for (const auto &zombie : zombies_)
            if (row_hitbox.findIntersection(zombie->hitbox))
                return true;

        return false;
    }

    [[nodiscard]] bool touchesPlant(const Entity &entity) const {
        for (const auto &plant : plants_)
            if (&entity != plant && entity.hitbox.findIntersection(plant->hitbox) || !entity.hitbox.findIntersection(world_hitbox_))
                return true;

        return false;
    }

private:
    std::vector<Entity *> plants_;
    std::vector<Entity *> zombies_;
    std::vector<Entity *> projectiles_;
    sf::FloatRect screen_hitbox_ = {{0, 0}, {1920, 1080}};
    sf::FloatRect shoot_range_ = {{0, 0}, {1500, 1080}};
    sf::FloatRect world_hitbox_ = {{0, 0}, {1900, 900}};
    std::mutex drawables_mutex_;

    // Mouse attributes
    sf::Vector2f mouse_position_;
    bool mouse_pressed_ = false;

    // Private methods
    static void remove_dead(std::vector<Entity *> &list) {
        // Remove all entities that have hp <= 0
        list.erase(
            std::remove_if(list.begin(), list.end(),
                           [](const Entity *e) {
                               if (e->health <= 0) {
                                   // e->onDie();
                                   return true;
                               }
                               return false;
                           }),
            list.end());
    }

    void update_list(const std::vector<Entity *> &list, const float elapsed) {
        // Update all entities in a list
        for (const auto entity: list)
            entity->update(*this, elapsed);
    }

    std::vector<const sf::Drawable *> collect_drawables(const std::vector<Entity *> &list) {
        // Lock operation, ensures thread safety for rendering engine
        std::scoped_lock lock(drawables_mutex_);

        // Add all entity drawables to the list
        std::vector<const sf::Drawable *> drawables;
        for (auto *entity: list)
            drawables.push_back(entity->getDrawable());

        // Return list
        return drawables;
    }
};

#endif //WORLD_H
