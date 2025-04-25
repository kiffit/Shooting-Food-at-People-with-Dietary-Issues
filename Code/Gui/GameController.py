# Eh Studios
# 04/22/2025


from Code.Entities.Plants.SugarCubeLauncher import SugarCubeLauncher
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
        self.plants.append(SugarCubeLauncher([0, 0]))
        self.plants.append(SugarCubeLauncher([1, 1]))

    # Getters
    def get_plants(self):
        return self.plants

    def get_zombies(self):
        return self.zombies

    def get_projectiles(self):
        return self.projectiles

    # Setters
    def set_plants(self, lists):
        self.plants = lists

    def set_zombies(self, lists):
        self.zombies = lists

    def set_projectiles(self, lists):
        self.projectiles = lists

    # Tostring
    def __str__(self):
        return "\nPLANTS: " + str(self.get_plants()) + "\nZOMBIES: " + str(self.get_zombies()) + "\nPROJECTILES: " + str(self.get_projectiles())
