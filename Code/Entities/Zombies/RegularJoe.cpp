#include "RegularJoe.h"

RegularJoe::RegularJoe(const sf::Vector2f &pos) : Entity(pos, {REGULARJOE_HITBOX_W, REGULARJOE_HITBOX_H}) {
    set_name("Regular Joe");
    set_description("Just an ordinary joe.");
    set_damage_type("none");
    set_team("zombies");
    set_interval(sf::seconds(1));
    set_health(10);
}

void RegularJoe::update(sf::Time &elapsed, GameController &gc) {
    set_lifetime(get_lifetime() + elapsed);

    if (!colliding) {
        move({-REGULARJOE_SPEED * elapsed.asSeconds(), 0});
    }

    colliding = false; // Reset for next frame
}

void RegularJoe::onCollision(Entity &other) {
    colliding = true;

    if (get_lifetime().asSeconds() >= get_interval().asSeconds()) {
        other.set_health(other.get_health() - REGULARJOE_DAMAGE);
        set_lifetime(sf::Time::Zero);
    }
}


void RegularJoe::onDie() {
}
