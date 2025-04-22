# Eh Studios
# 04/21/2025


from abc import ABC, abstractmethod


class Entity(ABC):
    # Constructor
    def __init__(self, name, description, bbox, health, damage, damage_type, action_interval, collision_action_interval):
        self.name = name
        self.description = description
        self.bbox = bbox
        self.health = health
        self.damage = damage
        self.damage_type = damage_type
        self.action_interval = action_interval
        self.collision_action_interval = collision_action_interval

    # Abstract Methods
    @abstractmethod
    def scheduled_action(self):
        pass

    @abstractmethod
    def collision_action(self):
        pass

    @abstractmethod
    def move(self):
        pass

    @abstractmethod
    def attack(self):
        pass

    @abstractmethod
    def die(self):
        pass

    # Getters
    @property
    def name(self):
        return self._name

    @property
    def description(self):
        return self._description

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
    def damage_type(self):
        return self._damage_type

    @property
    def action_interval(self):
        return self._action_interval

    @property
    def collision_action_interval(self):
        return self._collision_action_interval

    # Setters
    @name.setter
    def name(self, value):
        self._name = value

    @description.setter
    def description(self, value):
        self._description = value

    @bbox.setter
    def bbox(self, value):
        self._bbox = value

    @health.setter
    def health(self, value):
        self._health = value

    @damage.setter
    def damage(self, value):
        self._damage = value

    @damage_type.setter
    def damage_type(self, value):
        self._damage_type = value

    @action_interval.setter
    def action_interval(self, value):
        self._action_interval = value

    @collision_action_interval.setter
    def collision_action_interval(self, value):
        self._collision_action_interval = value

    # Tostring
    def __str__(self):
        return (
            f"Entity:"
            f"\n\tname: {self.name}"
            f"\n\tdescription: {self.description}"
            f"\n\tbbox: {self.bbox}"
            f"\n\thealth: {self.health}"
            f"\n\tdamage: {self.damage}"
            f"\n\tdamage_type: {self.damage_type}"
            f"\n\taction_interval: {self.action_interval}"
            f"\n\tcollision_action_interval: {self.collision_action_interval}"
        )
