background_image_filename = '../ch3/sushiplate.jpg'
sprite_image_filename = '../ch3/fugu.png'

import pygame
from pygame.locals import *
from sys import exit

pygame.init()
screen = pygame.display.set_mode((640, 480), 0, 32)

background = pygame.image.load(background_image_filename).convert()
sprite = pygame.image.load(sprite_image_filename)

clock = pygame.time.Clock()

x, y = 100., 100.
speed_x, speed_y = 133., 170.

while True:
	for event in pygame.event.get():
		if event.type == QUIT:
			exit()

	screen.blit(background, (0, 0))
	screen.blit(sprite, (x, y))

	time_passed = clock.tick (30)
	time_passed_seconds = time_passed / 1000.0

	x += speed_x * time_passed_seconds
	y += speed_y * time_passed_seconds

	if x > 640 - sprite.get_width():
		speed_x = - speed_x
		x = 640 - sprite.get_width()
	elif x < 0.:
	 	speed_x = - speed_x
	 	x = 0.

	if y > 480 - sprite.get_height():
		speed_y = -speed_y
		y = 480 - sprite.get_height()
	elif y < 0:
		speed_y = -speed_y
		y = 0.

	pygame.display.update()
	
