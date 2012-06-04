#!/usr/bin/env python

'''
ID3 Dumper

Usage: python dump.py [options] [file]

Options:
	-e ..., --encoding=...   specify encoding
	-t ..., --to=...         specify destination encoding
'''

import sys
import getopt
import os.path
import mutagen.id3

frames = \
(
	('AENC', 'Audio encryption'), 
	('APIC', 'Attached picture'),
	('COMM', 'Comments'),
	('COMR', 'Commercial frame'),
	('ENCR', 'Encryption method registration'),
	('EQUA', 'Equalization'),
	('ETCO', 'Event timing codes'),
	('GEOB', 'General encapsulated object'),
	('GRID', 'Group identification registration'),
	('IPLS', 'Involved people list'),
	('LINK', 'Linked information'),
	('MCDI', 'Music CD identifier'),
	('MLLT', 'MPEG location lookup table'),
	('OWNE', 'Ownership frame'),
	('PRIV', 'Private frame'),
	('PCNT', 'Play counter'),
	('POPM', 'Popularimeter'),
	('POSS', 'Position synchronisation frame'),
	('RBUF', 'Recommended buffer size'),
	('RVAD', 'Relative volume adjustment'),
	('RVRB', 'Reverb'),
	('SYLT', 'Synchronized lyric/text'),
	('SYTC', 'Synchronized tempo codes'),
	('TALB', 'Album/Movie/Show title'),
	('TBPM', 'BPM (beats per minute)'),
	('TCOM', 'Composer'),
	('TCON', 'Content type'),
	('TCOP', 'Copyright message'),
	('TDAT', 'Date'),
	('TDLY', 'Playlist delay'),
	('TENC', 'Encoded by'),
	('TEXT', 'Lyricist/Text writer'),
	('TFLT', 'File type'),
	('TIME', 'Time'),
	('TIT1', 'Content group description'),
	('TIT2', 'Title/songname/content description'),
	('TIT3', 'Subtitle/Description refinement'),
	('TKEY', 'Initial key'),
	('TLAN', 'Language(s)'),
	('TLEN', 'Length'),
	('TMED', 'Media type'),
	('TOAL', 'Original album/movie/show title'),
	('TOFN', 'Original filename'),
	('TOLY', 'Original lyricist(s)/text writer(s)'),
	('TOPE', 'Original artist(s)/performer(s)'),
	('TORY', 'Original release year'),
	('TOWN', 'File owner/licensee'),
	('TPE1', 'Lead performer(s)/Soloist(s)'),
	('TPE2', 'Band/orchestra/accompaniment'),
	('TPE3', 'Conductor/performer refinement'),
	('TPE4', 'Interpreted, remixed, or otherwise modified by'),
	('TPOS', 'Part of a set'),
	('TPUB', 'Publisher'),
	('TRCK', 'Track number/Position in set'),
	('TRDA', 'Recording dates'),
	('TRSN', 'Internet radio station name'),
	('TRSO', 'Internet radio station owner'),
	('TSIZ', 'Size'),
	('TSRC', 'ISRC (international standard recording code)'),
	('TSSE', 'Software/Hardware and settings used for encoding'),
	('TYER', 'Year'),
	('TXXX', 'User defined text information frame'),
	('UFID', 'Unique file identifier'),
	('USER', 'Terms of use'),
	('USLT', 'Unsychronized lyric/text transcription'),
	('WCOM', 'Commercial information'),
	('WCOP', 'Copyright/Legal information'),
	('WOAF', 'Official audio file webpage'),
	('WOAR', 'Official artist/performer webpage'),
	('WOAS', 'Official audio source webpage'),
	('WORS', 'Official internet radio station homepage'),
	('WPAY', 'Payment'),
	('WPUB', 'Publishers official webpage'),
	('WXXX', 'User defined URL link frame')
)

def usage():
	sys.stderr.write(__doc__)
	
def dump_frames(file, encoding='utf8', to='utf8'):
	try:
		audio = mutagen.id3.ID3 (file)
	except mutagen.id3.ID3NoHeaderError:
		sys.stderr.write ("Warning: %s doesn't contain vaild ID3 Tag!\n" % file)
		return
	for frame, desc in frames:
		if audio.has_key(frame):
			if encoding == to:
				print frame, audio[frame]
		#print frame, desc

def main(argv):
	encoding='utf8'
	to='utf8'
	try:
		opts, args = getopt.getopt (argv, 'e:t:h', ['encoding=', 'to=', 'help'])
	except getopt.GetoptError:
		usage()
		sys.exit(1)
	for opt, arg in opts:
		if opt in ('-h', '--help'):
			usage()
			sys.exit (1)
		elif opt in ('-e', '--encoding'):
			encoding = arg
		elif opt in ('-t', '--to'):
			to = arg
	for arg in args:
		if os.path.isfile (arg):
			dump_frames(arg, encoding)
		else:
			sys.stderr.write ("Warning: %s is not a valid file!\n" % arg);


if __name__ == '__main__':
	main(sys.argv[1:])
