SCREEN_SIZE = (800, 600)

from OpenGL.GL import *
from OpenGL.GLU import *

import pygame
from pygame.locals import *

def resize (width, height):
	glViewport (0, 0, width, height)
	glMatrixMode (GL_PROJECTION)
	glLoadIdentity()
	gluPerspective (45.0, float (width)/height, .1, 1000.)
	glMatrixMode (GL_MODELVIEW)
	glLoadIdentity()

def init():
	glEnable (GL_TEXTURE_2D)
	glEnable (GL_BLEND)
	glClearColor (1.0, 1.0, 1.0, 1.0)

def upload_texture (filename, use_alpha=False):
	if use_alpha:
		format, gl_format, bits_per_pixel = 'RGBA', GL_RGBA, 4
	else:
		format, gl_format, bits_per_pixel = 'RGB', GL_RGB, 3

	img_surface = pygame.image.load (filename)
	data = pygame.image.tostring (img_surface, format, True)

	texture_id = glGenTextures (1)
	glBindTexture (GL_TEXTURE_2D, texture_id)

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1)

	width, height = img_surface.get_rect().size
	glTexImage2D (GL_TEXTURE_2D,
					0,
					bits_per_pixel,
					bits_per_pixel,
					width,
					height,
					0,
					gl_format,
					GL_UNSIGNED_BYTE,
					data)

	return texture_id

def draw_quad (x, y, z, w, h):
	glBegin (GL_QUADS)
	glTexCoord2f (0, 0)
	glVertex3f (x-w/2, y-h/2, z)
	glTexCoord2f (1, 0)
	glVertex3f (x+w/2, y-h/2, z)
	glTexCoord2f (1, 1)
	glVertex3f (x+w/2, y+h/2, z)
	glTexCoord2f (0, 1)
	glVertex3f (x-w/2, y+h/2, z)
	glEnd ()

def run():
	pygame.init ()
	screen = pygame.display.set_mode (SCREEN_SIZE, HWSURFACE|OPENGL|DOUBLEBUF)
	resize (*SCREEN_SIZE)
	init ()

	background_tex = upload_texture ('background.png')
	fugu_tex = upload_texture ('fugu.png', True)

	while True:
		for evnet in pygame.event.get():
			if event.type == QUIT:
				return
			elif event.type == KEYDOWN:
				if event.key == K_1:
					glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
					glBlendEquation (GL_FUNC_ADD)
				elif event.key == K_2:
					glBlendFunc (GL_SRC_ALPAH, GL_ONE)
					glBlendEquation (GL_FUNC_ADD)
				elif event.key == K_3:
					glBlendFunc (GL_SRC_ALPAH, GL_ONE)
					glBlendEquation (GL_FUNC_REVERSE_SUBTRACT)
			glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

			glBindTexure (GL_TEXTURE_2D, background_Tex)
			glDisable (GL_BLEND)
			draw_quad (0, 0, -SCREEN_SIZE[1], 600, 600)
			glEnable (GL_BLEND)

			glBindTexture (GL_TEXTURE_2D, fugu_tex)
			x, y  = pygame.mouse.get_pos ()
			x -= SCREEN_SIZE[0]/2
			y -= SCREEN_SIZE[1]/2
			draw_quad (x, y, -SCREEN_SIZE[1], 256, 256)

			pygame.display.flip()

	glDeleteTextures (backgroud_tex)
	glDeleteTextures (fugu_tex)

if __name__ == '__main__':
	run()
				
