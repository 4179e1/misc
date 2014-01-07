from reportlab.lib import colors
from reportlab.graphics.shapes import *
from reportlab.graphics import renderPDF


data = [
# year month    predicted high low
(2013, 7, 65.6, 66.6, 64.6),
(2013, 8, 68.6, 70.6, 66.6),
(2013, 9, 71.7, 74.7, 68.7),
(2013, 10,        73.3,    78.3,    68.3),
(2013, 11,        73.9,    78.9,    68.9),
(2013, 12,        75.3,    81.3,    69.3),
(2014, 1,        77.5,    84.5,    70.5),
(2014, 2,        79.0,    86.0,    72.0),
(2014, 3,        81.2,    89.2,    73.2),
(2014, 4,        82.5,    91.5,    73.5),
(2014, 5,        82.0,    91.0,    73.0),
(2014, 6,        81.2,    91.2,    71.2),
(2014, 7,        79.8,    89.8,    69.8),
(2014, 8,        78.9,    88.9,    68.9),
(2014, 9,        77.6,    87.6,    67.6),
(2014, 10,        76.2,    86.2,    66.2),
(2014, 11,        74.8,    84.8,    64.8),
(2014, 12,        73.3,    83.3,    63.3),
]

drawing = Drawing (200,150)

pred = [row[2]-40 for row in data]
high = [row[3]-40 for row in data]
low = [row[4]-40 for row in data]
times = [200*((row[0] + row[1]/12.0) - 2013)-110 for row in data]

drawing.add (PolyLine (zip(times, pred), strokeColor=colors.blue))
drawing.add (PolyLine (zip(times, high), strokeColor=colors.red))
drawing.add (PolyLine (zip(times, low), strokeColor=colors.green))
drawing.add (String(65, 115, 'SunSpots', fontSize=18, fillColor=colors.red))

renderPDF.drawToFile (drawing, 'report1.pdf', 'Sunspots')
