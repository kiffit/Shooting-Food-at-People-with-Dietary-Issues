#include "Peashooter.h"
#include "../../GameController.h"
#include "../Projectiles/Pea.h"

Peashooter::Peashooter(const sf::Vector2f &pos) : Entity(pos, {PEASHOOTER_HITBOX_W, PEASHOOTER_HITBOX_H}) {
    set_name("Peashooter");
    set_description("Peas on enemies.");
    set_damage_type("organic");
    set_team("plants");
    set_interval(sf::seconds(1.4));
    set_health(10);
}

void Peashooter::update(sf::Time &elapsed, GameController &gc) {
    set_lifetime(get_lifetime() + elapsed);

    if (get_lifetime().asSeconds() >= get_interval().asSeconds()) {
        gc.projectiles_back.push_back(std::make_shared<Pea>(get_hitbox().position));
        set_lifetime(sf::Time::Zero); // reset lifetime after firing
    }
}

void Peashooter::onCollision(Entity &other) {
}

void Peashooter::onDie() {
}
