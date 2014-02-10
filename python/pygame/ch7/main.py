from config import *
from entity import *
from state import *
import pygame
from pygame.locals import *
from random import randint, choice
from gameobjects.vector2 import Vector2

def run():
	pygame.init()
	screen= pygame.display.set_mode (SCREEN_SIZE, 0, 32)

	world = World()

	w, h = SCREEN_SIZE

	clock = pygame.time.Clock()
	ant_image = pygame.image.load ('ant.png').convert_alpha()
	leaf_image = pygame.image.load ('leaf.png').convert_alpha()
	spider_image = pygame.image.load ('spider.png').convert_alpha()

	for ant_no in xrange (ANT_COUNT):
		ant = Ant (world, ant_image)
		ant.location = Vector2 (randint(0, w), randint (0, h))
		ant.brain.set_state ('exploring')
		world.add_entity (ant)

	while True:
		for event in pygame.event.get():
			if event.type == QUIT:
				return

		time_passed = clock.tick (30)

		if randint (1, 10) == 1:
			leaf = Leaf (world, leaf_image)
			leaf.location = Vector2 (randint (0, w), randint (0, h))
			world.add_entity (leaf)
	
		if randint (1, 100) == 1:
			spider = Spider (world, spider_image)
			spider.location = Vector2 (-50, randint (0, h))
			spider.destination = Vector2 (w+50, randint (0,h))
			world.add_entity (spider)
	
		world.process (time_passed)
		world.render (screen)
	
		pygame.display.update()

if __name__ == '__main__':
	run()
