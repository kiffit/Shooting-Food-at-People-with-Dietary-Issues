#ifndef ENTITY_H
#define ENTITY_H


#include <SFML/Graphics.hpp>


class Entity {
    // Common entity attributes
    sf::Rect<float> hitbox;
    sf::Time lifetime;
    bool alive = false;

    // Common entity class attributes (for things like Plants, Zombies, Projectiles inherited from Entity)
    std::string team;

    // Common inherited entity team attributes (ex. Peashooter inheriting Plant)
    std::string name;
    std::string description;
    std::string damage_type;
    float health = 0;

public:
    // Constructor
    explicit Entity(const sf::Rect<float> &hitbox) {
        set_hitbox(hitbox);
        set_lifetime(sf::Time::Zero);
        set_alive(true);
    }

    // Virtual methods
    virtual ~Entity() = default;

    virtual void update(sf::Time &elapsed) = 0;

    virtual void onCollision(Entity &other) = 0;

    virtual void die() = 0;

    // Getters
    [[nodiscard]] sf::Rect<float> get_hitbox() const {
        return hitbox;
    }

    [[nodiscard]] sf::Time get_lifetime() const {
        return lifetime;
    }

    [[nodiscard]] float get_health() const {
        return health;
    }

    [[nodiscard]] bool is_alive() const {
        return alive;
    }

    [[nodiscard]] std::string get_name() const {
        return name;
    }

    [[nodiscard]] std::string get_description() const {
        return description;
    }

    [[nodiscard]] std::string get_team() const {
        return team;
    }

    [[nodiscard]] std::string get_damage_type() const {
        return damage_type;
    }

    // Setters
    void set_hitbox(const sf::Rect<float> &hitbox) {
        this->hitbox = hitbox;
    }

    void set_lifetime(const sf::Time &lifetime) {
        this->lifetime = lifetime;
    }

    void set_health(const float health) {
        this->health = health;
    }

    void set_alive(const bool alive) {
        this->alive = alive;
    }

    void set_name(const std::string &name) {
        this->name = name;
    }

    void set_description(const std::string &description) {
        this->description = description;
    }

    void set_team(const std::string &team) {
        this->team = team;
    }

    void set_damage_type(const std::string &damage_type) {
        this->damage_type = damage_type;
    }

    // To string
    [[nodiscard]] std::string to_string() const {
        std::stringstream ss;
        ss << "Entity:"
                << "\n\tName: " << get_name()
                << "\n\tDescription: " << get_description()
                << "\n\tDamage type: " << get_damage_type()
                << "\n\tHealth: " << get_health()
                << "\n\tLifetime: " << get_lifetime().asMilliseconds() << "ms";
        return ss.str();
    }

    [[nodiscard]] std::string debug_string() const {
        std::stringstream ss;
        ss
                << "Name: " << get_name()
                << "\nPosition: " << get_hitbox().position.x << ", " << get_hitbox().position.y
                << "\nHealth: " << get_health()
                << "\nLifetime: " << get_lifetime().asMilliseconds();
        return ss.str();
    }
};

#endif //ENTITY_H
