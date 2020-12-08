import os, sys, pygame
from pygame.locals import *
import objects, config
import time

class State:
	def handle(sel, event):
		if event.type == QUIT:
			sys.exit()
		elif event.type == KEYDOWN and event.key == K_ESCAPE:
			sys.exit()

	def firstDisplay (self, screen):
		screen.fill (config.background_color)
		pygame.display.flip()

	def display (self, screen):
		pass

class Level(State):
	def __init__ (self, number=1):
		self.number = number
		self.remaining = config.weights_per_level
		speed = config.drop_speed
		speed += (self.number - 1) * config.speed_increase

		self.weight = objects.Weight(speed)
		self.banana = objects.Banana()
		both = self.weight, self.banana
		self.sprites = pygame.sprite.RenderUpdates(both)

	def update (self, game):
		self.sprites.update()
		if self.banana.touches (self.weight):
			game.nextState = GameOver()

		elif self.weight.landed:
			self.weight.reset()
			self.remaining -= 1
			if self.remaining == 0:
				game.nextState = LevelCleared (self.number)
	def display (self, screen):
		screen.fill (config.background_color)
		updates = self.sprites.draw(screen)
		pygame.display.update(updates)

class Paused (State):
	finished = 0
	image = None
	text = ''

	def handle (self, event):
		State.handle (self, event)
		if event.type in [MOUSEBUTTONDOWN, KEYDOWN]:
			self.finished = 1

	def update (self, game):
		if self.finished:
			game.nextState = self.nextState()

	def firstDisplay (self, screen):
		screen.fill (config.background_color)
		font = pygame.font.Font (None, config.font_size)
		lines = self.text.strip().splitlines()
		height = len(lines) * font.get_linesize()

		center, top = screen.get_rect().center
		top -= height

		if self.image:
			image = pygame.image.load (self.image).convert_alpha()
			r = image.get_rect()
			top += r.height // 2
			r.midbottom = center, top - 20
			screen.blit (image, r)
		antialias = 1
		black = 0, 0, 0

		for line in lines:
			text = font.render (line.strip(), antialias, black)
			r = text.get_rect()
			r.midtop = center, top
			screen.blit (text, r)
			top += font.get_linesize()

		pygame.display.flip()

class Info (Paused):
	nextState = Level
	text = '''
	In this game you are a banana.
	trying to survive a course in
	self-defense against fruit, where the
	participants will "defend" themselves
	against you with a 1 ton weight.'''

class StartUp (Paused):
	nextState = Info
	image = config.splash_image
	text = '''
	Welcome to Squish.
	the game of Fruit Self-Defense'''

class LevelCleared (Paused):
	def __init__ (self, number):
		self.number = number
		self.text = '''Level %i cleared
		Click to start next level''' % self.number

	def nextState(self):
		return Level(self.number+1)

class GameOver (Paused):
	nextState = Level
	text = '''
	Game Over
	Click to Restart. Esc to Quit'''

	
class Game:
	def __init__ (self, *args):
		path = os.path.abspath(args[0])
		dir = os.path.split(path)[0]
		os.chdir(dir)
		self.state = None
		self.nextState = StartUp()
	
	def run(self):
		pygame.init()
		flag = 0
		if config.full_screen:
			flag = FULLSCREEN
	
		screen_size = config.screen_size
		screen = pygame.display.set_mode(screen_size, flag)
	
		pygame.display.set_caption ('Fruit Self Defense')
		pygame.mouse.set_visible(False)
	
		while True:
			if self.state != self.nextState:
				self.state = self.nextState
				self.state.firstDisplay(screen)
			for event in pygame.event.get():
				self.state.handle(event)
			self.state.update(self)
			self.state.display(screen)

if __name__ == '__main__':
	game = Game (*sys.argv)
	game.run()

