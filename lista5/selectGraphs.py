# !/usr/bin/python
import numpy
import matplotlib.pyplot as plt

step, min, avg, max = numpy.loadtxt('C:\\Users\\Mona\\Desktop\\lista5\\osSelect.txt', delimiter=' ', unpack=True)


fig = plt.figure()
ax = fig.add_subplot(111)

ax.set_title("OS-Select")
ax.set_xlabel('Steps')
ax.set_ylabel('Number of')

plt.plot(step, min, 'ro', label='minSelect', markersize=0.9)
plt.plot(step, avg, 'bo', label='avgSelect', markersize=0.9)
plt.plot(step, max, 'yo', label='maxSelect', markersize=0.9)

leg = ax.legend()


plt.show()

