# Eh Studios
# 04/22/2025


import pygame
from Code.Gui.GameController import GameController
from Code.Utilities.BoundingBox import BoundingBox


class GameWindow:
    def __init__(self):
        # Defining class attributes
        self.screen = None
        self.clock = None
        self.running = False
        self.dtime = 0

        # Game controller
        self.game_controller = GameController()

        # Initialization
        self.init_pygame()

    # Methods
    def init_pygame(self):
        # Initialize pygame
        pygame.init()

        # Create screen for rendering to
        self.screen = pygame.display.set_mode((1280, 720))
        pygame.display.set_caption("Shooting Food at People with Dietary Issues")

        # Create clock for time management
        self.clock = pygame.time.Clock()

    def handle_input(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.running = False

        keys = pygame.key.get_pressed()

        if keys[pygame.K_w]:
            self.game_controller.plants[0].bbox.position[1] += 3 * self.dtime

        if keys[pygame.K_a]:
            self.game_controller.plants[0].bbox.position[0] -= 3 * self.dtime

        if keys[pygame.K_s]:
            self.game_controller.plants[0].bbox.position[1] -= 3 * self.dtime

        if keys[pygame.K_d]:
            self.game_controller.plants[0].bbox.position[0] += 3 * self.dtime

    def bbox_to_screen(self, bbox):
        screen_width, screen_height = self.screen.get_size()
        scale = 200  # pixels per world unit

        # Convert to top left
        world_x, world_y = bbox.position
        world_y *= -1
        world_x -= bbox.width / 2
        world_y -= bbox.height / 2

        # Get box dimensions
        width, height = bbox.width, bbox.height

        # Translate world space to screen space
        screen_x = screen_width // 2 + int(world_x * scale)
        screen_y = screen_height // 2 + int(world_y * scale)

        return screen_x, screen_y, int(width * scale), int(height * scale)

    def draw_entity(self, entity):
        # Convert bbox to screen coordinates
        x, y, w, h = self.bbox_to_screen(entity.bbox)

        # Debug color intersecting
        color = (255, 255, 255)
        if entity.bbox.overlaps(self.game_controller.plants[1].bbox):
            color = (255, 0, 0)

        # Draw the rect
        pygame.draw.rect(self.screen, color, pygame.Rect(x, y, w, h))

        # Calculate the screen position for the text (same as the entity's center)
        text_pos_x, text_pos_y, _, _ = self.bbox_to_screen(BoundingBox(entity.bbox.position, 0, 0))

        # Draw center position text
        font = pygame.font.SysFont(None, 24)
        text_surface = font.render(f"({entity.bbox.position[0]:.2f}, {entity.bbox.position[1]:.2f})", True, (0, 0, 0))
        text_rect = text_surface.get_rect(center=(text_pos_x, text_pos_y))
        self.screen.blit(text_surface, text_rect)

    def render(self):
        # Clear buffer
        self.screen.fill("black")

        # Draw entities
        for entity in self.game_controller.plants + self.game_controller.zombies + self.game_controller.projectiles:
            self.draw_entity(entity)

        # Render to window
        pygame.display.flip()

        # FPS controlling code. Change later
        self.dtime = self.clock.tick(60) / 1000

    def run(self):
        self.running = True

        # Running loop
        while self.running:
            self.handle_input()
            self.render()

    # Properties
    @property
    def screen(self):
        return self._screen

    @property
    def clock(self):
        return self._clock

    @property
    def running(self):
        return self._running

    @property
    def dtime(self):
        return self._dtime

    # Setters
    @screen.setter
    def screen(self, value):
        self._screen = value

    @clock.setter
    def clock(self, value):
        self._clock = value

    @running.setter
    def running(self, value):
        self._running = value

    @dtime.setter
    def dtime(self, value):
        self._dtime = value

    # Tostring
    def __str__(self):
        pass
