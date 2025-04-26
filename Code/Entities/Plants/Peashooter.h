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
        // Update lifetime
        set_lifetime(get_lifetime() + elapsed);

        // If it has been x time, fire a pea
        set_health(get_health() - 5 * elapsed.asSeconds());
    }

    void onCollision(Entity &other) override {
    }

    void die() override {
        std::cout << "damn ded" << std::endl;
    }
};


#endif //PEASHOOTER_H
