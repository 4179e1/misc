from sgmllib import SGMLParser
import htmlentitydefs

class ListProcessor (SGMLParser):
	def reset (self):
		self.pieces = []
		SGMLParser.reset (self)

	def unknown_starttag (self, tag, attrs):
		print "Start tag: %s, attrs " % tag
		print attrs

	def unknown_endtag (self, tag):
		print "End tag: %s" % tag

	def handle_charref (self, ref):
		print "Charref: %" % ref

	def handle_entityref (self, ref):
		print "Entityref: %s" % ref

	def handle_data (self, text):
		print "Data: %s" % text

	def handle_comment (self, text):
		print "Comment: %s" % text

	def handle_pi (self, text):
		print "PI: %s" % text

	def handle_decl (self, text):
		print "Decl: %s" % text

if __name__ == "__main__":
	f = open ("sample.html")
	html = f.read()
	parser = ListProcessor ()
	parser.feed (html)
	f.close()
	parser.close()

	
