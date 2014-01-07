from urllib import urlopen
from reportlab.graphics.shapes import *
from reportlab.graphics.charts.lineplots import LinePlot
from reportlab.graphics.charts.textlabels import Label
from reportlab.graphics import renderPDF

URL = 'http://www.swpc.noaa.gov/ftpdir/weekly/Predict.txt'
COMMENT_CHARS = '#:'

drawing = Drawing (400, 200)
data=[]
for line in urlopen(URL).readlines():
    if not line.isspace() and not line[0] in COMMENT_CHARS:
        data.append ([float(n) for n in line.split()])

print data
