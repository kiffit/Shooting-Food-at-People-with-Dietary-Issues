# Eh Studios
# 04/21/2025


from Entity import Entity


class Projectile(Entity):
    # Attributes
    __parent = None

    # Constructor
    def __init__(self, name, description, aabb, position, health, damage, damage_type, action_interval, collision_action_interval, parent):
        super().__init__(name, description, aabb, position, health, damage, damage_type, action_interval, collision_action_interval)
        self.set_parent(parent)

    # Method

    # Getters
    def get_parent(self):
        return self.__parent

    # Setters
    def set_parent(self, parent):
        self.__parent = parent

    # Tostring
    def __str__(self):
        return (
            f"Projectile:"
            f"\n\t{super().__str__()}"
            f"\n\tparent: {self.get_parent()}"
        )
