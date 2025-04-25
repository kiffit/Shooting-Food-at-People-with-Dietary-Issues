#ifndef PLANT_H
#define PLANT_H


#include "../Entity.h"
#include <SFML/Graphics.hpp>


#define PLANT_WIDTH 100
#define PLANT_HEIGHT 100


class Plant : public Entity {
public:
    // Constructor
    explicit Plant(const sf::Vector2f &pos) : Entity({pos, {PLANT_WIDTH, PLANT_HEIGHT}}) {
        set_team("plants");
    }
};

#endif //PLANT_H
