from config import *
from state import *
import pygame
from gameobjects.vector2 import Vector2
from random import randint, choice


class GameEntity (object):
	def __init__ (self, world, name, image):
		self.world = world
		self.name = name
		self.image = image
		self.location = Vector2(0, 0)
		self.destination = Vector2(0,0)
		self.speed = 0.

		self.brain = StateMachine()

		self.id = 0

	def render (self, surface):
		x, y = self.location
		w, h = self.image.get_size()
		surface.blit (self.image, (x-w/2, y-h/2))

	def process (self, time_passed):
		self.brain.think()
		if self.speed > 0 and self.location != self.destination:
			vec_to_destination = self.destination - self.location
			distance_to_destination = vec_to_destination.get_length()
			heading = vec_to_destination.get_normalized()
			travel_distance = min (distance_to_destination, time_passed * self.speed)
			self.location += travel_distance * heading

	
class World (object):
	def __init__ (self):
		self.entities = {}
		self.entity_id = 0
		self.background = pygame.surface.Surface(SCREEN_SIZE).convert()
		self.background.fill ((255, 255, 255))
		pygame.draw.circle (self.background, (200, 255, 200), NEST_POSITION, int (NEST_SIZE))

	def add_entity (self, entity):
		self.entities[self.entity_id] = entity
		entity.id = self.entity_id
		self.entity_id += 1
	
	def remove_entity (self, entity):
		del self.entities[entity.id]

	def get (self, entity_id):
		return self.entities.get(entity_id, None)

	def process (self, time_passed):
		time_passed_seconds = time_passed / 1000.0
		for entity in self.entities.copy().itervalues():
			entity.process (time_passed_seconds)

	def render (self, surface):
		surface.blit (self.background, (0, 0))
		for entity in self.entities.values():
			entity.render(surface)

	def get_close_entity (self, name, location, range=100.):
		location = Vector2 (*location)
		for entity in self.entities.values():
			if entity.name == name:
				distance = location.get_distance_to (entity.location)
				if distance < range:
					return entity
		return None


class Ant (GameEntity):
	def __init__ (self, world, image):
		GameEntity.__init__ (self, world, 'ant', image)

		exploring_state = AntStateExploring (self)
		seeking_state = AntStateSeeking (self)
		delivering_state = AntStateDelivering (self)
		hunting_state = AntStateHunting (self)

		self.brain.add_state (exploring_state)
		self.brain.add_state (seeking_state)
		self.brain.add_state (delivering_state)
		self.brain.add_state (hunting_state)

		self.carry_image = None

	def carry (self, image):
		self.carry_image = image

	def drop (self, surface):
		if self.carry_image:
			x, y = self.location
			w, h = self.carry_image.get_size()
			surface.blit (self.carry_image, (x-w, y-h/2))
			self.carry_image = None

	def render (self, surface):
		GameEntity.render (self, surface)
		if self.carry_image:
			x, y = self.location
			w, h = self.carry_image.get_size()
			surface.blit (self.carry_image, (x-w, y-h/2))
	
class Leaf (GameEntity):
	def __init__ (self, world, image):
		GameEntity.__init__ (self, world, 'leaf', image)

class Spider (GameEntity):
	def __init__ (self, world, image):
		GameEntity.__init__ (self, world, 'spider', image)
		self.dead_image = pygame.transform.flip (image, 0, 1)

		self.health = 25
		self.speed = 50. + randint (-20, 20)

	def bitten (self):
		self.health -= 1
		if self.health <= 0:
			self.speed = 0.
			self.image = self.dead_image
		self.speed = 140.

	def render (self, surface):
		GameEntity.render (self, surface)

		x, y = self.location
		w, h = self.image.get_size()
		bar_x = x - 12
		bar_y = y + h/2
		surface.fill ((255, 0, 0), (bar_x, bar_y, 25, 4))
		surface.fill ((0, 255, 0), (bar_x, bar_y, self.health, 4))

	def process (self, time_passed):
		x, y = self.location
		if x > SCREEN_SIZE[0] + 2:
			self.world.remove_entity (self)
			return
		GameEntity.process (self, time_passed)

