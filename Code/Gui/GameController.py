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

    # Tostring
    def __str__(self):
        pass
