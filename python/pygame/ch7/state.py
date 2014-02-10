from config import *

class State (object):
	def __init__ (self, name):
		self.name = name

	def do_action (self):
		pass

	def chek_conditions (self):
		pass

	def entry_actions (self):
		pass

	def exit_actions (self):
		pass


class StateMachine (object):
	def __init__ (self):
		self.states = {}
		self.active_state = None

	def add_state (self, state):
		self.states[state.name] = state

	def think (self):
		if self.active_state is None:
			return

		self.active_state.do_actions()

		new_state_name = self.active_state.check_conditions()
		if new_state_name is not None:
			self.set_state (new_state_name)

	def set_state (self, new_state_name):
		if self.active_state is not None:
			self.active_state.exit_actions()
		self.active_state = self.states[new_state_name]
		self.active_state.entry_actions()


class AntStateExploring (State):
	def __init__ (self, ant):
		State.__init__ (self, 'exploring')
		self.ant = ant

		def random_destination (self):
			w,h = SCREEN_SIZE
			self.ant.destination = Vector2 (randint(0, w), randint (0, h))

		def do_actions (self):
			if randint (1, 20) == 1:
				self.random_destination()

		def check_conditions (self):
			leaf = self.ant.world.get_close_entity ('leaf', self.ant.location)
			if leaf is not None:
				self.ant.leaf_id = leaf.id
				return 'seeking'

			spider = self.ant.world.get_close_entity ('spider', NEST_POSITION, NEST_SIZE)
			if spider is not None:
				if self.ant.location.get_distance_to (spider.location) < 100.:
					self.ant.spider_id = spider.id
					return 'hunting'

			return None

		def entry_actions (self):
			self.ant.speed = 120. + randint (-30, 30)
			self.random_destination()



