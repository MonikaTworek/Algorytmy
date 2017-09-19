#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt

step, minCompares, avgCompares, maxCompares = np.loadtxt('C:\\Users\\Mona\\Desktop\\lol\\lista_4\\find.txt', delimiter=' ', unpack=True)

fig = plt.figure()
ax = fig.add_subplot(111)

ax.set_title("Number of compares depending on the size of tree")
ax.set_xlabel('Number of steps')
ax.set_ylabel('Compares')

plt.plot(step, minCompares, 'ro', label='Minimum', markersize=0.9)
plt.plot(step, avgCompares, 'mo', label='Average', markersize=0.9)
plt.plot(step, maxCompares, 'bo', label='Maximum', markersize=0.9)

leg = ax.legend()
plt.show()


