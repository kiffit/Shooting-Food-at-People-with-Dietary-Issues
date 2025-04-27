#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H


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
    void updateList(std::vector<std::shared_ptr<Entity> > &list, sf::Time &elapsed);

    void processCollisions() const;

    void update(sf::Time &elapsed);

    void swapBuffers();

    void cleanup();
};

#endif //GAMECONTROLLER_H
