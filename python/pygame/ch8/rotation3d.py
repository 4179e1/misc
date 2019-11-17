SCREEN_SIZE = (640, 640)
CUBE_SIZE = 300

import pygame
from pygame.locals import *
from gameobjects.vector3 import Vector3
from gameobjects.matrix44 import Matrix44 as Matrix

from math import *
from random import randint

def calculate_viewing_distance (fov, screen_width):
	d = (screen_width/2.0) / tan (fov/2.0)
	return d

def run ():
	pygame.init()
	screen = pygame.display.set_mode (SCREEN_SIZE, 0)
	font = pygame.font.SysFont ('courier new', 16, True)
	ball = pygame.image.load ('ball.png').convert_alpha()

	points = []

	fov = 75.
	viewing_distance = calculate_viewing_distance (radians (fov), SCREEN_SIZE[0])

	for x in xrange (0, CUBE_SIZE + 1, 10):
		edge_x = x == 0 or x == CUBE_SIZE
		for y in xrange (0, CUBE_SIZE + 1, 10):
			edge_y = y == 0 or y == CUBE_SIZE
			for z in xrange (0, CUBE_SIZE + 1, 10):
				edge_z = z == 0 or z == CUBE_SIZE

				if sum ((edge_x, edge_y, edge_z)) >= 2:
					point_x = float (x) - CUBE_SIZE / 2
					point_y = float (y) - CUBE_SIZE / 2
					point_z = float (z) - CUBE_SIZE / 2
					points.append (Vector3 (point_x, point_y, point_z))

	def point_z (point):
		return point[2]
	points.sort (key=point_z, reverse=True)

	center_x, center_y = SCREEN_SIZE
	center_x /= 2
	center_y /= 2

	ball_w, ball_h = ball.get_size()
	ball_center_x = ball_w / 2
	ball_center_y = ball_h / 2

	camera_position = Vector3 (0.0, 0.0, 600.)
	rotation = Vector3()
	rotation_speed = Vector3 (radians(20), radians(20), radians(20))
	clock = pygame.time.Clock()
	red = (255, 0, 0)
	green = (0, 255, 0)
	blue = (0, 0, 255)
	white = (255, 255, 255)

	x_surface = font.render ("X", True, white)
	y_surface = font.render ('Y', True, white)
	z_surface = font.render ('Z', True, white)

	while True:
		for event in pygame.event.get():
			if event.type == QUIT:
				return

		screen.fill ((0, 0, 0))

		time_passed = clock.tick ()
		time_passed_seconds = time_passed / 1000.

		rotation_direction = Vector3 ()
		
		pressed_keys = pygame.key.get_pressed ()
		if pressed_keys [K_a]:
			rotation_direction.y -= 1.0
		if pressed_keys [K_d]:
			rotation_direction.y += 1.0
		if pressed_keys [K_w]:
			rotation_direction.x -= 1.0
		if pressed_keys [K_s]:
			rotation_direction.x += 1.0
		if pressed_keys [K_q]:
			rotation_direction.z += 1.0
		if pressed_keys [K_e]:
			rotation_direction.z -= 1.0
			
		rotation += rotation_direction * rotation_speed * time_passed_seconds

		rotation_matrix = Matrix.x_rotation (rotation.x)
		rotation_matrix *= Matrix.y_rotation (rotation.y)
		rotation_matrix *= Matrix.z_rotation (rotation.z)
		
		transformed_points = []

		for point in points:
			p = rotation_matrix.transform_vec3(point) - camera_position
			transformed_points.append (p)
		transformed_points.sort (key=point_z)

		for x, y, z in transformed_points:
			if z < 0:
				x = center_x + x * -viewing_distance / z		# why -viewing_distance? so the z axis of camera would be negetive
				y = center_y + -y * -viewing_distance / z
				screen.blit (ball, (x-ball_center_x, y-ball_center_y))	
		
		def draw_axis (color, axis, label):
			axis = rotation_matrix.transform_vec3 (axis * 150.)		# that's where magificant by 150
			SCREEN_SIZE = (640, 640)
			center_x = SCREEN_SIZE[0] / 2.0
			center_y = SCREEN_SIZE[1] / 2.0
			x,y,z = axis - camera_position

			x = center_x + x * -viewing_distance / z
			y = center_y + -y * -viewing_distance / z

			pygame.draw.line (screen, color, (center_x, center_y), (x, y), 2)

			w,h = label.get_size ()
			screen.blit (label, (x-w/2, y-h/2))
			
		x_axis = Vector3 (1, 0, 0)
		y_axis = Vector3 (0, 1, 0)
		z_axis = Vector3 (0, 0, 1)

		draw_axis (red, x_axis, x_surface)
		draw_axis (green, y_axis, y_surface)
		draw_axis (blue, z_axis, z_surface)

		degrees_txt = tuple (degrees(r) for r in rotation)
		rotation_txt = 'Rotation: W/S %.3f, A/D %.3f, Q/E %.3f' % degrees_txt
		txt_surface = font.render (rotation_txt, True, white)
		screen.blit (txt_surface, (5, 5))

		matrix_txt = str (rotation_matrix)
		txt_y = 25
		for line in matrix_txt.split ('\n'):
			txt_surface = font.render (line, True, white)
			screen.blit (txt_surface, (5, txt_y))
			txt_y += 20

		pygame.display.update()

if __name__ == '__main__':
	run()
