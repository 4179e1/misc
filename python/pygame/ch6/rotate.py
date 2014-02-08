background_image_filename = '../ch3/sushiplate.jpg'
sprite_image_filename = '../ch3/fugu.png'

import pygame
from pygame.locals import *
from sys import exit
from gameobjects.vector2 import Vector2
from math import *

pygame.init()

screen = pygame.display.set_mode((640, 480), 0, 32)

background = pygame.image.load(background_image_filename).convert()
sprite = pygame.image.load (sprite_image_filename).convert_alpha()

clock = pygame.time.Clock()

sprite_pos = Vector2 (200, 150)
sprite_speed = 300.
sprite_rotation = 90.
sprite_rotation_speed = 360. #  Degress per second


def plane_transform (vec, rotation):
	sin_rotation = sin(rotation * pi /180.0)
	cos_rotation = cos (rotation *pi /180.0)
	heading_x = key_direction.x * cos_rotation + key_direction.y * sin_rotation 
	heading_y = -key_direction.x * sin_rotation + key_direction.y * cos_rotation
	return Vector2(heading_x, heading_y)

while True:
	for event in pygame.event.get():
		if event.type == QUIT:
			exit()

	pressed_keys = pygame.key.get_pressed()
	
	rotation_direction = 0.
	key_direction = Vector2 (0, 0)

	if pressed_keys[K_a]:
		rotation_direction += 1.0
	if pressed_keys[K_d]:
		rotation_direction -= 1.0
	if pressed_keys[K_q]:
		key_direction.x = -1.0
	if pressed_keys[K_e]:
		key_direction.x = 1.0
	if pressed_keys[K_w]:
		key_direction.y = -1.0
	if pressed_keys[K_s]:
		key_direction.y = 1.0
	
	key_direction.normalize()

	screen.blit(background, (0, 0))
	rotated_sprite = pygame.transform.rotate (sprite, sprite_rotation)
	w, h = rotated_sprite.get_size()
	sprite_draw_pos = Vector2 (sprite_pos.x - w/2, sprite_pos.y-h/2)
	screen.blit (rotated_sprite, sprite_draw_pos)

	time_passed = clock.tick(30)
	time_passed_seconds = time_passed / 1000.0

	sprite_rotation += rotation_direction * sprite_rotation_speed * time_passed_seconds
	heading = plane_transform (key_direction, sprite_rotation)
	print heading
	

	sprite_pos += heading * sprite_speed * time_passed_seconds

	pygame.display.update()
