# Eh Studios
# 04/21/2025


from Entities import Entity
from Utilities.BoundingBox import BoundingBox
from pygame.math import Vector2


def main():
    b1 = BoundingBox(Vector2(0, 0), 1, 1)
    b2 = BoundingBox(Vector2(1, 1), 1, 1)
    print(b1)
    print(b2)
    print(b1.intersects(b2))


if __name__ == '__main__':
    main()
