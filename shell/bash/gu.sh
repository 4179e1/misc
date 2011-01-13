size=320
width=1
colour="-color black"
usage="Usage ${0##.*/} [-s N] [-w N] [-c S] imagefile..."
while getopts ":s:w:c:" opt; do
	case $opt in 
	s)size=$OPTARG;;
	w)width=$OPTARGS;;
	c)colour="-color $OPTARG";;
	\?)echo $usage
	exit 1;;
	esac
done

shift $(($OPTIND - 1))

if [ -z "$@" ]; then
	echo $usage
	exit 1
fi


filename=$1

if [ -z $filename ]; then
	echo "procfile: No file specified"
	exit 1
fi

for filename in "$@"; do
	pnmfile=${filename%.*}.ppm

	case $filename in
	*.jpg) exit 0;;
	*.tga) tgatoppm $filename > $pnmfile;;
	*.xpm) xpmtoppm $filename > $pnmfile;;
	*.pcx) pcxtoppm $filename > $pnmfile;;
	*.tif) tiftoppm $filename > $pnmfile;;
	*.git) giftopnm $filename > $pnmfile;;
	*)echo "procfile: $filename is an unknown graphics file."
		exit 1;;
	esac

outfile=${pnmfile%.ppm}.new.jpg
pnmscale -quitee -xysize $size $size $ppnfile | pnmmargin $colour $width | pnmtojpeg $pnmfile > $outfile
rm $pnmfile
done
