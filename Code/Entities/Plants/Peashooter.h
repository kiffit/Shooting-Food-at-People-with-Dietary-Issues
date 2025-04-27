#ifndef PEASHOOTER_H
#define PEASHOOTER_H
#include "../Entity.h"
#include "../Projectiles/Pea.h"


#define PEASHOOTER_HITBOX_W 100
#define PEASHOOTER_HITBOX_H 100


class Peashooter final : public Entity {
public:
    explicit Peashooter(const sf::Vector2f &pos) : Entity(pos, {PEASHOOTER_HITBOX_W, PEASHOOTER_HITBOX_W}) {
        set_name("Peashooter");
        set_description("Peas on enemies.");
        set_team("plants");
        set_damage_type("organic");
        set_interval(sf::seconds(3));
        set_health(10);
    }

    // Methods
    void update(sf::Time &elapsed, GameController &gc) override {
        set_lifetime(get_lifetime() + elapsed);


        if (get_lifetime().asSeconds() >= fireInterval) {
            gc.projectiles_back.push_back(std::make_shared<Pea>(get_hitbox().position));
            set_lifetime(sf::Time::Zero); // reset lifetime after firing
        }
    }


    void onCollision(Entity &other) override {
    }

    void onDie() override {
        std::cout << "damn ded" << std::endl;
    }
};


#endif //PEASHOOTER_H
