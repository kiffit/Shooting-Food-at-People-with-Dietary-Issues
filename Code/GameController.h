#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <algorithm>
#include <vector>
#include "Entities/Entity.h"

class GameController {
public:
    // Attributes
    std::vector<std::shared_ptr<Entity> > plants;
    std::vector<std::shared_ptr<Entity> > zombies;
    std::vector<std::shared_ptr<Entity> > projectiles;

    // Constructor
    GameController() {
        plants.clear();
        zombies.clear();
        projectiles.clear();
    }

    // Methods
    static void updateList(std::vector<std::shared_ptr<Entity> > &list, sf::Time &elapsed) {
        for (const auto &entity: list) {
            entity->update(elapsed);
        }

        // Remove dead ones after update pass
        list.erase(
            std::remove_if(list.begin(), list.end(),
                           [](const std::shared_ptr<Entity> &e) {
                               if (e->get_health() <= 0) {
                                   e->die();
                                   return true;
                               }
                               return false;
                           }),
            list.end());
    }


    void update(sf::Time &elapsed) {
        // Update plants, zombies, and projectiles step, will delete all dead entities
        updateList(plants, elapsed);
        updateList(zombies, elapsed);
        updateList(projectiles, elapsed);
    }
};

#endif //GAMECONTROLLER_H
