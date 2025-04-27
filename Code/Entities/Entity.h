#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>


// Forward declaration
class GameController;


/// An abstract class for representing an interactive object in the world.
/// It provides methods that inherited members can override to define custom behavior.
class Entity {
    /* ---------- COMMON ENTITY ATTRIBUTES ---------- */
    /// Defines a position (top left of the box) and size (length and width) for the entity hitbox.
    sf::Rect<float> hitbox;

    /// Tracks the time the entity has been alive for. Necessary for scheduled actions.
    sf::Time lifetime;

    /// Whether the entity is alive or not. Entities not alive will be deleted.
    bool alive = false;

    /* ---------- INHERITED ENTITY ATTRIBUTES ---------- */
    /// A nice name for the entity. For example, "Peashooter"
    std::string name;

    /// A description for the entity explaining what it does or what it is.
    std::string description;

    /// A certain weakness an entity targets. For example, a "diabetic" damage type against a diabetic will deal bonus damage.
    std::string damage_type;

    /// A string specifying the team. Only three options should be used: "plants", "zombies", "projectiles"
    std::string team;

    /// The entity's primary action interval. When this interval is reached, the entity may choose to perform an action.
    sf::Time interval;

    /// The health for an entity. If health is <= 0, the entity will die.
    float health = 0;

public:
    // Constructor
    /// Initializes a basic entity with properties that base classes do not need to define specially.
    /// @param pos Top-left position of the entity on screen.
    /// @param size Width and height of the entity.
    explicit Entity(const sf::Vector2f &pos, const sf::Vector2f &size);

    // Virtual methods
    virtual ~Entity() = default;

    /// Gives entities a chance to update their state and run custom logic every game loop.
    /// @param elapsed Running time of last frame.
    /// @param gc Game controller, if entities wish to modify state of the game. (like adding an entity)
    virtual void update(sf::Time &elapsed, GameController &gc) = 0;

    /// Custom logic callback whenever an entity is touched or touches another entity.
    /// @param other Entity colliding with self.
    virtual void onCollision(Entity &other) = 0;

    /// Custom death callback whenever an entity is killed.
    virtual void onDie() = 0;

    // Methods
    /// Moves an entity by an offset.
    /// @param dir Direction vector the entity will be moved toward.
    void move(const sf::Vector2f &dir);

    // Getters
    [[nodiscard]] sf::Rect<float> get_hitbox() const { return hitbox; }
    [[nodiscard]] sf::Time get_lifetime() const { return lifetime; }
    [[nodiscard]] bool is_alive() const { return alive; }
    [[nodiscard]] std::string get_name() const { return name; }
    [[nodiscard]] std::string get_description() const { return description; }
    [[nodiscard]] std::string get_damage_type() const { return damage_type; }
    [[nodiscard]] std::string get_team() const { return team; }
    [[nodiscard]] sf::Time get_interval() const { return interval; }
    [[nodiscard]] float get_health() const { return health; }

    // Setters
    void set_hitbox(const sf::Rect<float> &hitbox);
    void set_lifetime(const sf::Time &lifetime);
    void set_alive(bool alive);
    void set_name(const std::string &name);
    void set_description(const std::string &description);
    void set_damage_type(const std::string &damage_type);
    void set_team(const std::string &team);
    void set_interval(const sf::Time &interval);
    void set_health(float health);

    // To string
    [[nodiscard]] std::string to_string() const;
    [[nodiscard]] std::string debug_string() const;
};

#endif //ENTITY_H
