# Eh Studios
# 04/21/2025


from abc import ABC, abstractmethod
import pygame.time

from Code.Utilities.BoundingBox import BoundingBox


class Entity(ABC):
    # Constructor
    def __init__(self, name, description, team, bbox, health, damage, damage_types, action_interval,
                 collision_action_interval):
        self.name = name
        self.description = description
        self.team = team
        self.bbox = bbox
        self.health = health
        self.damage = damage
        self.damage_types = damage_types
        self.action_interval = action_interval
        self.collision_action_interval = collision_action_interval
        self.created_time = pygame.time.get_ticks() / 1000

    # Abstract Methods
    @abstractmethod
    def scheduled_action(self, game_controller):
        pass

    @abstractmethod
    def collision_action(self):
        pass

    @abstractmethod
    def move(self, dtime):
        pass

    @abstractmethod
    def attack(self):
        pass

    @abstractmethod
    def die(self):
        pass

    # Regular Methods
    def make_standard_bbox(self, position, width=0.8, height=0.8):
        return BoundingBox(position, width, height)

    # Getters
    @property
    def name(self):
        return self._name

    @property
    def description(self):
        return self._description

    @property
    def team(self):
        return self._team

    @property
    def bbox(self):
        return self._bbox

    @property
    def health(self):
        return self._health

    @property
    def damage(self):
        return self._damage

    @property
    def damage_types(self):
        return self._damage_types

    @property
    def action_interval(self):
        return self._action_interval

    @property
    def collision_action_interval(self):
        return self._collision_action_interval

    @property
    def created_time(self):
        return self._created_time

    # Setters
    @name.setter
    def name(self, value):
        self._name = value

    @description.setter
    def description(self, value):
        self._description = value

    @team.setter
    def team(self, value):
        self._team = value

    @bbox.setter
    def bbox(self, value):
        self._bbox = value

    @health.setter
    def health(self, value):
        self._health = value

    @damage.setter
    def damage(self, value):
        self._damage = value

    @damage_types.setter
    def damage_types(self, value):
        self._damage_types = value

    @action_interval.setter
    def action_interval(self, value):
        self._action_interval = value

    @collision_action_interval.setter
    def collision_action_interval(self, value):
        self._collision_action_interval = value

    @created_time.setter
    def created_time(self, value):
        self._created_time = value

    # Tostring
    def __str__(self):
        return (
            f"Entity:"
            f"\n\tname: {self.name}"
            f"\n\tdescription: {self.description}"
            f"\n\tteam: {self.team}"
            f"\n\tbbox: {self.bbox}"
            f"\n\thealth: {self.health}"
            f"\n\tdamage: {self.damage}"
            f"\n\tdamage_types: {self.damage_types}"
            f"\n\taction_interval: {self.action_interval}"
            f"\n\tcollision_action_interval: {self.collision_action_interval}"
        )
