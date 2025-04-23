# Eh Studios
# 04/21/2025


from Code.Entities.Entity import Entity


class Plant(Entity):
    # Attributes

    # Constructor
    def __init__(self, name, description, aabb, position, health, damage, damage_type, action_interval):
        super().__init__(name, description, aabb, position, health, damage, damage_type, action_interval)

    # Methods
    def scheduled_action(self):
        pass

    def collision_action(self):
        pass

    def move(self):
        pass

    def attack(self):
        pass

    def die(self):
        pass

    # Getter

    # Setter

    # Tostring
    def __str__(self):
        return (
            f"Plant:"
            f"\n\t{super().__str__()}"
        )
