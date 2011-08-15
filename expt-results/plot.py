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
    count = 0
    heading = ''
    x_label = ''
    y_label = ''
    for line in files:
        if count == 0:
            tmp = line.split()
            x_label = tmp[0]
            y_label = tmp[1]
            heading = x_label + ' vs ' + y_label
        else:
            tmp = line.split()
            x.append(tmp[0])
            y.append(tmp[1])
        count += 1
    figure(i)
    plot(x, y)
    xlabel(x_label)
    ylabel(y_label)
    title(heading)
    savefig(heading)
