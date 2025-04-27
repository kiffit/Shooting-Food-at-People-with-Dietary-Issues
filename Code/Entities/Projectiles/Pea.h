#ifndef PEA_H
#define PEA_H
#include "../Entity.h"


#define PEA_HITBOX_W 10
#define PEA_HITBOX_H 10
#define PEA_DAMAGE 2
#define PEA_SPEED 500


class Pea final : public Entity {
public:
    explicit Pea(const sf::Vector2f &pos) : Entity(pos, {PEA_HITBOX_W, PEA_HITBOX_W}) {
        set_name("Pea");
        set_description("Peas on enemies.");
        set_team("projectiles");
        set_damage_type("organic");
        set_interval(sf::seconds(3));
        set_health(100);
    }

    // Methods
    void update(sf::Time &elapsed, GameController &gc) override {
        // Update lifetime
        set_lifetime(get_lifetime() + elapsed);

        // Move pea
        move({PEA_SPEED * elapsed.asSeconds(), 0});

        // Kill pea if it ain't doing something
        if (get_lifetime().asSeconds() > 10)
            set_health(0);
    }

    void onCollision(Entity &other) override {
        float damage = PEA_DAMAGE;

        if (get_damage_type() == other.get_damage_type())
            damage *= 2;

        other.set_health(other.get_health() - damage);
        set_health(0);
    }

    void onDie() override {
    }
};


#endif //PEA_H
