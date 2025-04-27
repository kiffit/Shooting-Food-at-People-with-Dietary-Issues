#ifndef PEASHOOTER_H
#define PEASHOOTER_H
#include "../Entity.h"


#define PEASHOOTER_HITBOX_W 100
#define PEASHOOTER_HITBOX_H 100


class Peashooter final : public Entity {
public:
    // Constructor
    explicit Peashooter(const sf::Vector2f &pos);

    // Methods
    void update(sf::Time &elapsed, GameController &gc) override;
    void onCollision(Entity &other) override;
    void onDie() override;
};


#endif //PEASHOOTER_H

