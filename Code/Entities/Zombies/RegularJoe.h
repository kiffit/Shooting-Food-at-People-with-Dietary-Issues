#ifndef REGULARJOE_H
#define REGULARJOE_H
#include "../Entity.h"


#define REGULARJOE_HITBOX_W 100
#define REGULARJOE_HITBOX_H 100
#define REGULARJOE_SPEED 40
#define REGULARJOE_DAMAGE 3


class RegularJoe final : public Entity {
    bool colliding = false;
public:
    // Constructor
    explicit RegularJoe(const sf::Vector2f &pos);

    // Methods
    void update(sf::Time &elapsed, GameController &gc) override;

    void onCollision(Entity &other) override;

    void onDie() override;
};


#endif //REGULARJOE_H
