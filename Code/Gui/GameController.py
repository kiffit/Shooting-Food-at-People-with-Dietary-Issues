# Eh Studios
# 04/22/2025


from Code.Entities.Plant import Plant
from Code.Utilities.BoundingBox import BoundingBox


class GameController:
    def __init__(self):
        # Base/background elements
        self.background_elements = []

        # Characters
        self.plants = []
        self.zombies = []
        self.projectiles = []

        # Foreground/ui elements
        self.ui_elements = []

        # Add objects
        self.add_objects()

    # Methods
    def add_objects(self):
        self.plants.append(Plant(
            "Peashooter",
            "Shoots peas",
            BoundingBox([0, 0], 1, 1),
            10,
            10,
            "organic",
            5,
            0
        ))

        self.plants.append(Plant(
            "Peashooter",
            "Shoots peas",
            BoundingBox([2, 0], 0.5, 0.5),
            10,
            10,
            "organic",
            5,
            0
        ))

    #Getters
    def get_plants(self):
        return self.plants

    def get_zombies(self):
        return self.zombies

    def get_projectiles(self):
        return self.projectiles

    #Setters
    def set_plants(self, lists):
        self.plants = lists

    def set_zombies(self, lists):
        self.zombies = lists

    def set_projectiles(self, lists):
        self.projectiles = lists

    # Tostring
    def __str__(self):
        return "\nPLANTS: " + str(self.get_plants()) + "\nZOMBIES: " + str(self.get_zombies()) + "\nPROJECTILES: " + str(self.get_projectiles())
