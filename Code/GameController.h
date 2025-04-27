#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <algorithm>
#include <mutex>
#include <vector>
#include "Entities/Entity.h"

/*
 * Hello!
 * Big note: we can store time in entities.
 * It updates every frame. If it exceeds a certain interval, they can call an action and reset it.
 * We can probably speed this idea up a little with some thinking.
 */

class GameController {
public:
    // Attributes
    std::vector<std::shared_ptr<Entity> > plants_front, plants_back;
    std::vector<std::shared_ptr<Entity> > zombies_front, zombies_back;
    std::vector<std::shared_ptr<Entity> > projectiles_front, projectiles_back;
    std::mutex mutex_lock;

    // Constructor
    GameController() = default;

    // Methods
    void updateList(std::vector<std::shared_ptr<Entity> > &list, sf::Time &elapsed) {
        for (const auto &entity: list) {
            entity->update(elapsed, *this);
        }

        // Remove dead ones after update pass
        list.erase(
            std::remove_if(list.begin(), list.end(),
                           [](const std::shared_ptr<Entity> &e) {
                               if (e->get_health() <= 0) {
                                   e->onDie();
                                   return true;
                               }
                               return false;
                           }),
            list.end());
    }

    void update(sf::Time &elapsed) {
        // Update plants, zombies, and projectiles step, will delete all dead entities
        updateList(plants_back, elapsed);
        updateList(zombies_back, elapsed);
        updateList(projectiles_back, elapsed);

        // Swap buffers, necessary for avoiding race conditions and segfaults between the controller and window
        swapBuffers();
    }

    void swapBuffers() {
        std::scoped_lock lock(mutex_lock);
        plants_front = plants_back;
        zombies_front = zombies_back;
        projectiles_front = projectiles_back;
    }

    void cleanup() {
        std::scoped_lock lock(mutex_lock);
        plants_front.clear();
        plants_back.clear();
        zombies_front.clear();
        zombies_back.clear();
        projectiles_front.clear();
        projectiles_back.clear();
    }
};

#endif //GAMECONTROLLER_H
