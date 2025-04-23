# Eh Studios
# 04/21/2025


class BoundingBox:
    # Constructors
    def __init__(self, position, width, height):
        self.position = position
        self.width = width
        self.height = height

    # Methods
    def overlaps(self, other):
        self_left = self.position[0] - (self.width / 2)
        self_right = self.position[0] + (self.width / 2)
        self_top = self.position[1] - (self.height / 2)
        self_bottom = self.position[1] + (self.height / 2)

        other_left = other.position[0] - (other.width / 2)
        other_right = other.position[0] + (other.width / 2)
        other_top = other.position[1] - (other.height / 2)
        other_bottom = other.position[1] + (other.height / 2)

        return (
                self_left <= other_right and
                self_right >= other_left and
                self_top <= other_bottom and
                self_bottom >= other_top
        )

    # Getters
    @property
    def position(self):
        return self._position

    @property
    def width(self):
        return self._width

    @property
    def height(self):
        return self._height

    # Setters
    @position.setter
    def position(self, value):
        self._position = value

    @width.setter
    def width(self, value):
        self._width = value

    @height.setter
    def height(self, value):
        self._height = value

    # Tostring
    def __str__(self):
        return (
            f"BoundingBox:"
            f"\n\tposition: [{self.position[0]}, {self.position[1]}]"
            f"\n\twidth: {self.width}"
            f"\n\theight: {self.height}"
        )
