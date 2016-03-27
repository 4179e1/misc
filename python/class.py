__metaclass__ = type

class Test:
	def __init__ (self, href, title, cite, desc):
		self.href = href
		self.title = title
		self.cite = cite
		self.desc = desc

	def format (self):
		print ('<section><a href="%s">%s</a><cite>%s</cite><p class="desc">%s</p></section>' % (self.href, self.title, self.cite, self.desc))

if __name__ == "__main__":
	t = Test ("http://www.poetpalace.org", "Poetpalace", "poetpalace.org > home", "hello world")

	t.format()

