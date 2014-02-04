background_image_filename = 'sushiplate.jpg'

import pygame
from pygame.locals import *
from sys import exit

Resolution = (640, 480)
Fullscreen = False

pygame.init()
screen = pygame.display.set_mode(Resolution, 0, 32)
background = pygame.image.load (background_image_filename).convert()


while True:
	for event in pygame.event.get():
		if event.type == QUIT:
			exit()
		if event.type == KEYDOWN:
			if event.key == K_ESCAPE:
				exit()
			if event.key == K_f:
				Fullscreen = not Fullscreen
				if Fullscreen:
					screen = pygame.display.set_mode (Resolution, FULLSCREEN, 32)
				else:
					screen = pygame.display.set_mode (Resolution, 0, 32)

	screen.blit (background, (0, 0))
	pygame.display.update()	

