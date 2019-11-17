sprite_image_filename = 'car.png'

import pygame
from pygame.locals import *
from sys import exit
from gameobjects.vector2 import Vector2
from math import *
from numpy import clip

pygame.init()
screen = pygame.display.set_mode((640, 480), 0, 32)

sprite = pygame.image.load (sprite_image_filename).convert_alpha()

clock = pygame.time.Clock()

#pygame.mouse.set_visible (False)
#pygame.event.set_grab (True)

sprite_pos = Vector2 (200, 150)	# the center of the sprite, transform to spriet_draw_pos when drawing
sprite_speed = 300.
sprite_rotation = 0.
sprite_rotation_speed = 90.

def plane_transform (vec, rotation):
	sin_rotation = sin(rotation * pi /180.0)
	cos_rotation = cos(rotation *pi /180.0)
	heading_x = vec.x * cos_rotation + vec.y * sin_rotation 
	heading_y = -vec.x * sin_rotation + vec.y * cos_rotation
	return Vector2(heading_x, heading_y)

screen = pygame.display.get_surface()
screen_area = screen.get_rect()
while True:
	for event in pygame.event.get():
		if event.type == QUIT:
			exit()
		if event.type == KEYDOWN:
			if event.key == K_ESCAPE:
				exit()

	pressed_keys = pygame.key.get_pressed()
	pressed_mouse = pygame.mouse.get_pressed()

	rotation_direction = 0.
	movement_direction = 0.

	rel = pygame.mouse.get_rel()
	rotation_direction = - rel[0] / 5.

	movement_direction = Vector2 (0, 0)
	if pressed_keys [K_a]:
		rotation_direction += 1.
	if pressed_keys [K_d]:
		rotation_direction -= 1.
	if pressed_keys[K_w] or pressed_mouse[0]:
		movement_direction.y -= 1.
	if pressed_keys[K_s] or pressed_mouse[2]:
		movement_direction.y = 1.

	screen.fill ((0, 0, 0))

	rotated_sprite = pygame.transform.rotate (sprite, sprite_rotation)
	w, h = rotated_sprite.get_size()
	sprite_draw_pos = Vector2 (sprite_pos.x - w/2, sprite_pos.y-h/2)	# the position to draw (top, left)
	screen.blit (rotated_sprite, sprite_draw_pos)

	time_passed = clock.tick(60)
	time_passed_seconds = time_passed / 1000.0

	sprite_rotation += rotation_direction * sprite_rotation_speed * time_passed_seconds

	sprite_rotation += rotation_direction * sprite_rotation_speed * time_passed_seconds
	heading = plane_transform (movement_direction, sprite_rotation)

	sprite_pos += heading * sprite_speed * time_passed_seconds
	sprite_pos.x = float (clip (sprite_pos.x, screen_area.left + w/2, screen_area.right - w/2))
	sprite_pos.y = float (clip (sprite_pos.y, screen_area.top + h/2, screen_area.bottom - h/2))
	pygame.display.update()
