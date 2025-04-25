#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include "Plant.h"

class Peashooter final : public Plant {
public:
    explicit Peashooter(const sf::Vector2f &pos) : Plant(pos) {
        set_name("Peashooter");
        set_description("Peas on enemies.");
        set_damage_type("organic");
        set_health(10);
    }

    // Methods
    void update(sf::Time &elapsed) override {
        set_lifetime(get_lifetime() + elapsed);
    }

    void onCollision(Entity &other) override {

    }
};



#endif //PEASHOOTER_H
