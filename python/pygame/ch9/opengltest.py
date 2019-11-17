from OpenGL.GL import *
from OpenGL.GLU import *
import pygame
from pygame.locals import *

screen = pygame.display.set_mode ((640, 480), HWSURFACE | OPENGL | DOUBLEBUF)

def init ():
	glEnable (GL_DEPTH_TEST)
	glClearColor (1.0, 1.0, 1.0, 1.0)
	glShadeModel (GL_FLAT)
	glEnable (GL_COLOR_MATERIAL)

	glEnable (GL_LIGHTING)
	glEnable (GL_LIGHT0)
	glLight (GL_LIGHT0, GL_POSITION, (0, 1, 1, 0))

if __name__ == '__main__':
	init()
