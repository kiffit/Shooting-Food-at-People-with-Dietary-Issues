# Eh Studios
# 04/21/2025


from Entity import Entity


class Plant(Entity):
    # Attributes

    # Constructor
    def __init__(self, name, description, aabb, position, health, damage, damage_type, action_interval, collision_action_interval):
        super().__init__(name, description, aabb, position, health, damage, damage_type, action_interval, collision_action_interval)

    # Method

    # Getter

    # Setter

    # Tostring
    def __str__(self):
        return (
            f"Plant:"
            f"\n\t{super().__str__()}"
        )
