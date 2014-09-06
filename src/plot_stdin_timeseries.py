#!/usr/bin/env python

import matplotlib.pyplot as plt
import sys

def main():
    frameskip = 1
    plt.ion()

    framecount = 0
    N = 0
    fig = plt.figure()
    sp = fig.add_subplot(111)
    
    while True:
        data = sys.stdin.readline()
        if data == '':
            break
        framecount += 1
        if framecount % frameskip != 0:
            continue
        data = data.split(" ")
        try:
            data = map(float, data)
        except ValueError:
            continue
        sp.set_title(str(framecount))
        for i in range(1, len(data)):
            sp.scatter(data[0], data[i], s=1)
        #plt.savefig("./frames1/"+str(framecount)+".png")
        plt.draw()

if __name__ == "__main__":
    sys.exit(main())
