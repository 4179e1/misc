SCREEN_SIZE = (800, 600)

from math import radians

from OpenGL.GL import * 
from OpenGL.GLU import *

import pygame
from pygame.locals import *

from gameobjects.matrix44 import *
from gameobjects.vector3 import *

def resize (width, height):
	glViewport (0, 0, width, height)
	glMatrixMode (GL_PROJECTION)
	glLoadIdentity()
	gluPerspective (60.0, float (width)/height, .1, 1000.)
	glMatrixMode (GL_MODELVIEW)
	glLoadIdentity()

def init ():
	glEnable (GL_DEPTH_TEST)
	glClearColor (1.0, 1.0, 1.0, 1.0)
	glShadeModel (GL_FLAT)
	glEnable (GL_COLOR_MATERIAL)

	glEnable (GL_LIGHTING)
	glEnable (GL_LIGHT0)
	glLight (GL_LIGHT0, GL_POSITION, (0, 1, 1, 0))

class Cube (object):
	def __init__ (self, position, color):
		self.position = position
		self.color = color

	num_faces = 6
	vertices = [(0.0, 0.0, 1.0),
				(1.0, 0.0, 1.0),
				(1.0, 1.0, 1.0),
				(0.0, 1.0, 1.0),
				(0.0, 0.0, 0.0),
				(1.0, 0.0, 0.0),
				(1.0, 1.0, 0.0),
				(0.0, 1.0, 0.0)]

	normals = [ (0.0, 0.0, +1.0),	# front
				(0.0, 0.0, -1.0),	# back
				(+1.0, 0.0, 0.0),	# right
				(-1.0, 0.0, 0.0),	# left
				(0.0, +1.0, 0.0),	# top
				(0.0, -1.0, 0.0)]	# bottom

	vertex_indices = [  (0, 1, 2, 3),	# front
						(4, 5, 6, 7),	# back
						(1, 5, 6, 2), 	# right
						(0, 4, 7, 3),	# left
						(3, 2, 6, 7),	# top
						(0, 1, 5, 4)]	# bottom

	def render (self):
		glColor (self.color)
		vertices = []
		for v in self.vertices:
			vertices.append (tuple (Vector3(v) + self.position))

		glBegin (GL_QUADS)
		for face_no in xrange (self.num_faces):
			glNormal3dv (self.normals[face_no])

			v1, v2, v3, v4 = self.vertex_indices [face_no]
			glVertex (vertices[v1])
			glVertex (vertices[v2])
			glVertex (vertices[v3])
			glVertex (vertices[v4])

		glEnd ()

class Map (object):
	def __init__ (self):
		map_surface = pygame.image.load ('map.png')
		map_surface.lock()

		w,h = map_surface.get_size ()

		self.cubes = []

		for y in range (h):
			for x in range (w):
				r, g, b, a = map_surface.get_at ((x, y))
				if (r, g, b) != (255, 255, 255):
					gl_col = (r/255.0, g/255.0, b/255.0)
					position = (float(x), 0.0, float (y))
					cube = Cube (position, gl_col)
					self.cubes.append (cube)
		map_surface.unlock()

		self.display_list = None

	def render (self):
		if self.display_list is None:
			self.display_list = glGenLists(1)
			glNewList (self.display_list, GL_COMPILE)
			
			for cube in self.cubes:
				cube.render()

			glEndlist()
		else:
			glCallList (self.display_list)

def run():
	pygame.init()
	screen = pygame.display.set_mode (SCREEN_SIZE, HWSURFACE|OPENGL|DOUBLEBUF)

	resize (*SCREEN_SIZE)
	init ()
	
	clock = pygame.time.Clock()
	map = Map()

	camera_matrix = Matrix44()
	camera_matrix.translate = (10.0, .6, 10.0)

	rotation_direction = Vector3 ()
	rotation_speed = radians(90.0)
	movement_direction = Vector3 ()
	movement_speed = 5.0

	while True:
		for event in pygame.event.get():
			if event.type == QUIT:
				return
			if event.type == KEYUP and event.key == K_ESCAPE:
				return

		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

		time_passed = clock.tick(30)
		time_passed_seconds = time_passed / 1000.

		pressed = pygame.key.get_pressed()

		if pressed [K_LEFT]:
			rotation_direction.y += 1.0
		if pressed [K_RIGHT]:
			rotation_direction.y -= 1.0
		if pressed [K_UP]:
			rotation_direction.x -= 1.0
		if pressed [K_DOWN]:
			rotation_direction.x += 1.0
		if pressed [K_a]:
			rotation_direction.z -= 1.0
		if pressed [K_d]:
			rotation_direction.z += 1.0
		if pressed [K_w]:
			movement_direction.z -= 1.0
		if pressed [K_q]:
			movement_direction.z += 1.0

		rotation = rotation_direction * rotation_speed * time_passed_seconds
		rotation_matrix = Matrix44.xyz_rotation (*rotation)
		camera_matrix *= rotation_matrix

		heading = Vector3 (camera_matrix.forward)
		movement = heading * movement_direction.z * movement_speed
		camera_matrix.translate += movement * time_passed_seconds

		glLoadMatrixd (camera_matrix.get_inverse().to_opengl())
		
		glLight (GL_LIGHT0, GL_POSITION, (0, 1.5, 1, 0))

		map.render ()

		pygame.display.flip()


if __name__ == '__main__':
	run()
