# Eh Studios
# 04/21/2025


from Code.Entities.Entity import Entity


class SugarCube(Entity):
    # Attributes
    __parent = None

    # Constructor
    def __init__(self, position):
        # Set data
        name = "Sugar Cube"
        desc = "A diabetic's worst nightmare."
        team = "PLANTS"
        bbox = self.make_standard_bbox(position, 0.6, 0.2)
        health = 100
        damage = 3
        damage_types = ["sugar"]
        action_interval = 0
        collision_action_interval = 0

        # Initialize
        super().__init__(name, desc, team, bbox, health, damage, damage_types, action_interval,
                         collision_action_interval)

    # Methods
    def scheduled_action(self, game_controller):
        pass

    def collision_action(self):
        pass

    def move(self, dtime):
        self.bbox.position[0] += 6 * dtime

    def attack(self):
        pass

    def die(self):
        pass

    # Getters

    # Tostring
    def __str__(self):
        return (
            f"Projectile:"
            f"\n\t{super().__str__()}"
            f"\n\tparent: {self.get_parent()}"
        )
