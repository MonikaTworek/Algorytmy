# !/usr/bin/python
import numpy
import matplotlib.pyplot as plt

step, compares  = numpy.loadtxt('C:\\Users\\Mona\\Desktop\\lista5\\lcs.txt', delimiter=' ', unpack=True)


fig = plt.figure()
ax = fig.add_subplot(111)

ax.set_title("Longest Common Subsequence")
ax.set_xlabel('Steps')
ax.set_ylabel('Number of compares')

plt.plot(step, compares, 'ro', label='Compares', markersize=0.9)

leg = ax.legend()

plt.show()

