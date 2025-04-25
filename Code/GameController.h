#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <vector>
#include "Entities/Entity.h"
#include "Entities/Plants/Peashooter.h"

class GameController {
public:
    // Attributes
    std::vector<Entity *> plants;
    std::vector<Entity *> zombies;
    std::vector<Entity *> projectiles;

    // Constructor
    GameController() {
        plants.clear();
        zombies.clear();
        projectiles.clear();

        plants.push_back(new Peashooter({100, 10}));
    };
};

#endif //GAMECONTROLLER_H
