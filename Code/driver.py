# Eh Studios
# 04/21/2025


from Utilities.BoundingBox import BoundingBox
from pygame.math import Vector2
from Gui.GameWindow import GameWindow
from Gui.GameController import GameController


def main():
    gc = GameController()
    print(gc)
    gw1 = GameWindow()
    gw1.run()


if __name__ == '__main__':
    main()
