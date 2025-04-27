#include "Entity.h"

Entity::Entity(const sf::Vector2f &pos, const sf::Vector2f &size) {
    set_hitbox({pos, size});
    set_lifetime(sf::Time::Zero);
    set_alive(true);
}

void Entity::move(const sf::Vector2f &dir) {
    auto hb = get_hitbox();
    set_hitbox({hb.position + dir, hb.size});
}

void Entity::set_hitbox(const sf::Rect<float> &hitbox) {
    this->hitbox = hitbox;
}

void Entity::set_lifetime(const sf::Time &lifetime) {
    this->lifetime = lifetime;
}

void Entity::set_alive(const bool alive) {
    this->alive = alive;
}

void Entity::set_name(const std::string &name) {
    this->name = name;
}

void Entity::set_description(const std::string &description) {
    this->description = description;
}

void Entity::set_damage_type(const std::string &damage_type) {
    this->damage_type = damage_type;
}

void Entity::set_team(const std::string &team) {
    this->team = team;
}

void Entity::set_interval(const sf::Time &interval) {
    this->interval = interval;
}

void Entity::set_health(const float health) {
    this->health = health;
}

std::string Entity::to_string() const {
    std::stringstream ss;
    ss << "Entity:"
            << "\n\tName: " << get_name()
            << "\n\tDescription: " << get_description()
            << "\n\tDamage type: " << get_damage_type()
            << "\n\tHealth: " << get_health()
            << "\n\tLifetime: " << get_lifetime().asMilliseconds() << "ms";
    return ss.str();
}

std::string Entity::debug_string() const {
    std::stringstream ss;
    ss
            << "Name: " << get_name()
            << "\nPosition: " << get_hitbox().position.x << ", " << get_hitbox().position.y
            << "\nHealth: " << get_health()
            << "\nLifetime: " << get_lifetime().asMilliseconds();
    return ss.str();
}
