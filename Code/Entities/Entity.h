#ifndef ENTITY_H
#define ENTITY_H

class Entity {
public:
    // Virtual methods
    virtual ~Entity() = default;

    virtual void update(float dt) = 0;

    virtual void draw(/* Some draw stuff */) = 0;

    virtual void onCollision(Entity &other) = 0;
};

#endif //ENTITY_H
