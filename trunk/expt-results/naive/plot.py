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
    y = []
    y1 = []
    y2 = []
    y3 = []
    count = 0
    heading = ''
    heading1 = ''
    x_label = ''
    y_label = ''
    y1_label = ''
    y2_label = ''
    y3_label = ''
    for line in files:
        if count == 0:
            tmp = line.split()
            x_label = tmp[0]
            y_label = tmp[1]
            y1_label = tmp[2]
            y2_label = tmp[3]
            y3_label = tmp[4]
            heading = x_label + ' vs ' + y_label
            heading1 = x_label + ' vs ' + y1_label + ', ' + y2_label + ', ' + y3_label
        else:
            tmp = line.split()
            x.append(tmp[0])
            y.append(tmp[1])
            y1.append(tmp[2])
            y2.append(tmp[3])
            y3.append(tmp[4])
        count += 1
    
    figure(i)
    plot(x, y)
    xlabel(x_label)
    ylabel(y_label)
    title(heading)
    savefig(heading)
    i += 1

    figure(i)
    p1 = plot(x, y1, 'b')
    p2 = plot(x, y2, 'g')
    p3 = plot(x, y3, 'r')
    xlabel(x_label)
    figlegend( (p1, p2, p3),
               (y1_label, y2_label, y3_label),
               'right' )
    title(heading1)
    savefig(heading1)
