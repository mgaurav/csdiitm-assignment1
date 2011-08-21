from pylab import *
import os

files = os.popen('ls *.txt').read().split()
file_list = []

for names in files:
    file_list.append(open(names))

i = 0

for files in file_list:
    i += 1
    x = []
    y1 = []
    y2 = []
    y3 = []
    count = 0
    heading = ''
    x_label = ''
    y1_label = ''
    y2_label = ''
    y3_label = ''
    for line in files:
        if count == 0:
            tmp = line.split()
            x_label = tmp[0]
            y1_label = tmp[1]
            y2_label = tmp[2]
            y3_label = tmp[3]
            heading = x_label + ' vs ' + y1_label + ', ' + y2_label + ', ' + y3_label
        else:
            tmp = line.split()
            x.append(tmp[0])
            y1.append(tmp[1])
            y2.append(tmp[2])
            y3.append(tmp[3])
        count += 1
    figure(i)
    p1 = plot(x, y1, 'b')
    p2 = plot(x, y2, 'g')
    p3 = plot(x, y3, 'r')
    xlabel(x_label)
    figlegend( (p1, p2, p3),
               (y1_label, y2_label, y3_label),
               'right' )
    title(heading)
    savefig(heading)
