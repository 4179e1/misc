import statsout
def output (format="text"):
	output_function = getattr (statsout, "output_%s" % format, statsout.output_text)
	return output_function()

if __name__ == "__main__":
	output ("text")
	output ("xml")
	output ("html")
	output ("none")
