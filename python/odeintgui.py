#!/usr/bin/python

import subprocess
from Tkinter import Button, END, Frame, Label, OptionMenu, StringVar, Tk, W

methods = {"Forward Euler"        : 'fweuler',
           "4th-order Runge-Kutta": 'rk4',
           "Bulirsch-Stoer"       : 'bulsto',
          }

systems = {"Lorenz"        : "lorenz",
           "Lotka-Volterra": "lotka",
          }

class OdeIntGui:
    def __init__(self, master):
        self.frame = Frame(master)
        self.frame.grid(row=0, column=0)

        #--- Integration parameters
        self.method = StringVar(self.frame)
        self.method.set(methods.keys()[2])
        self.system = StringVar(self.frame)
        self.system.set(systems.keys()[0])

        self.dt = 0.01
        self.t0 = 0.0
        self.X0 = (0.01, 0.01, 0.01)
        self.n = 10000
        #---

        self.menu_systems = OptionMenu(self.frame, self.system, *systems.keys())
        self.menu_systems.grid(row=0, columnspan=10)

        #self.label_system = Label(self.frame, textvariable=self.system)
        #self.label_system.grid(row=1, columnspan=10)

        self.button_plot = Button(self.frame, text="PLOT", command=self.plot)
        self.button_plot.grid(row=3, column=0)

        self.button_quit = Button(self.frame, text="QUIT",
                                  command=self.frame.quit)
        self.button_quit.grid(row=3, column=10)

    def plot(self):
        import matplotlib.pyplot as plt

        print "Integrating %s using %s" % (self.system.get(), self.method.get())

        cmd = "../src/integrate %s %s -d %s -t %s " % (methods[self.method.get()], systems[self.system.get()], self.dt, self.t0)
        for x in self.X0:
            cmd += "-x %s " % x
        cmd += "-n %s -v " % self.n
        print cmd
        
        print "Computing..."

        # heard "shell=True" might not be safe?
        integration = subprocess.Popen(cmd, stdout=subprocess.PIPE, shell=True)
        integration_stdout = integration.communicate()[0]

        print "Plotting..."

        data = []
        for line in integration_stdout.split("\n"):
            if line != "":
                data.append(map(float, line.split(" ")))
        arrays = zip(*data)
        t = arrays[0]
        if len(arrays) == 3:
            x = arrays[1]
            y = arrays[2]
            plt.plot(t, x)
            plt.plot(t, y)
        if len(arrays) == 4:
            x = arrays[1]
            y = arrays[2]
            z = arrays[3]
            plt.plot(t, x)
            plt.plot(t, y)
            plt.plot(t, z)
        plt.show()
            


def main():
    root = Tk()
    root.geometry('640x480')
    odeintgui = OdeIntGui(root)
    root.mainloop()

if __name__ == '__main__':
    main()
