# Eh Studios
# 04/21/2025


from Code.Entities.Entity import Entity
from Code.Entities.Projectiles.SugarCube import SugarCube


class SugarCubeLauncher(Entity):
    # Attributes

    # Constructor
    def __init__(self, position):
        # Set data
        name = "Sugar Cube Launcher"
        desc = "Violently launches a large white granulated sugar cube."
        team = "PLANTS"
        bbox = self.make_standard_bbox(position)
        health = 10
        damage = 0
        damage_types = []
        action_interval = 3
        collision_action_interval = 0

        # Initialize
        super().__init__(name, desc, team, bbox, health, damage, damage_types, action_interval, collision_action_interval)

    # Methods
    def scheduled_action(self, game_controller):
        game_controller.projectiles.append(SugarCube([self.bbox.position[0], self.bbox.position[1]]))

    def collision_action(self):
        pass

    def move(self, dtime):
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
