background_image_filename = '../ch3/sushiplate.jpg'
sprite_image_filename = '../ch3/fugu.png'

import pygame
from pygame.locals import *
from sys import exit
from gameobjects.vector2 import Vector2

pygame.init()

screen = pygame.display.set_mode((640, 480), 0, 32)

background = pygame.image.load(background_image_filename).convert()
sprite = pygame.image.load (sprite_image_filename).convert_alpha()

screen.blit(background, (0, 0))
screen.blit (sprite, (0, 0))
pygame.display.update()

while True:
	for event in pygame.event.get():
		if event.type == QUIT:
			exit()
	

