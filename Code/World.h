#ifndef WORLD_H
#define WORLD_H
#include <algorithm>
#include <mutex>
#include "Entities/Entity.h"

class World {
public:
    // Constructor
    explicit World(sf::RenderWindow *window) : window_(window) {
    }

    // Methods
    void update(const float elapsed) {
        // Run through entity updates, also kills dead ones
        update_list(plants_, elapsed);
        update_list(projectiles_, elapsed);
        update_list(zombies_, elapsed);
    }

    // Getting drawables for rendering
    std::vector<std::shared_ptr<sf::Drawable> > getPlantDrawables() {
        std::scoped_lock lock(drawables_mutex_);
        return collect_drawables(plants_);
    }

    std::vector<std::shared_ptr<sf::Drawable> > getZombieDrawables() {
        std::scoped_lock lock(drawables_mutex_);
        return collect_drawables(zombies_);
    }

    std::vector<std::shared_ptr<sf::Drawable> > getProjectileDrawables() {
        std::scoped_lock lock(drawables_mutex_);
        return collect_drawables(projectiles_);
    }

    [[nodiscard]] sf::RenderWindow *getWindow() const {
        return window_;
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

    //

private:
    std::vector<Entity *> plants_;
    std::vector<Entity *> zombies_;
    std::vector<Entity *> projectiles_;
    std::mutex drawables_mutex_;

    /// USE RESPONSIBLY, MOUSE CONTROLS ONLY
    sf::RenderWindow *window_;

    // Private methods
    static void remove_dead(std::vector<Entity *> &list) {
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

    void update_list(std::vector<Entity *> &list, const float elapsed) {
        for (const auto entity: list)
            entity->update(*this, elapsed);

        remove_dead(list);
    }

    static std::vector<std::shared_ptr<sf::Drawable> > collect_drawables(const std::vector<Entity *> &list) {
        std::vector<std::shared_ptr<sf::Drawable> > drawables;
        for (auto *entity: list)
            if (auto drawable = entity->getGraphicsComponent()->drawable(*entity))
                drawables.push_back(drawable);

        return drawables;
    }
};

#endif //WORLD_H
