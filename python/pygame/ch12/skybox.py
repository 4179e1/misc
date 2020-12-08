SCREEN_SIZE = (800, 600)

from OpenGL.GL import *
from OpenGL.GLU import *

import pygame
from pygame.locals import *

import sys
sys.path.append ('../ch11')
import model3d 

def resize (width, height):
	glViewport (0, 0, width, height)
	glMatrixMode (GL_PROJECTION)
	glLoadIdentity ()
	gluPerspective (60.0, float(width)/height, .1, 1000.)
	glMatrixMode (GL_MODELVIEW)
	glLoadIdentity ()

def init():
	glEnable (GL_LIGHTING)
	glEnable (GL_DEPTH_TEST)
	glEnable (GL_TEXTURE_2D)
	glShadeModel (GL_SMOOTH)

	glEnable (GL_LIGHT0)
	glLight (GL_LIGHT0, GL_POSITION, (0, .5, 1, 0))

def run():
	pygame.init ()
#	screen = pygame.display.set_mode (SCREEN_SIZE, FULLSCREEN | HWSURFACE | OPENGL | DOUBLEBUF)
	screen = pygame.display.set_mode (SCREEN_SIZE, HWSURFACE | OPENGL | DOUBLEBUF)
	resize (*SCREEN_SIZE)
	init ()

	sky_box = model3d.Model3D()
	sky_box.read_obj ('tanksky/skybox.obj')

	for material in sky_box.materials.itervalues():
		glBindTexture (GL_TEXTURE_2D, material.texture_id)
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)

	mouse_x = 0.0
	mouse_y = 0.0

	pygame.mouse.set_visible (False)

	while True:
		for event in pygame.event.get():
			if event.type == QUIT:
				return
			if event.type == KEYDOWN:
				return

		glClear (GL_DEPTH_BUFFER_BIT)

		glLoadIdentity ()
		mouse_rel_x, mouse_rel_y = pygame.mouse.get_rel ()
		mouse_x += float (mouse_rel_x) / 5.0
		mouse_y += float (mouse_rel_y) / 5.0

		glRotatef (mouse_y, 1, 0, 0)
		glRotatef (mouse_x , 0, 1, 0)

		glDisable (GL_LIGHTING)
		glDepthMask (False)

		sky_box.draw_quick ()

		glEnable (GL_LIGHTING)
		glDepthMask (True)

		pygame.display.flip ()

if __name__ == '__main__':
	run ()
