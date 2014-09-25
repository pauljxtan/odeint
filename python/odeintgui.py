#!/usr/bin/python

import matplotlib
# use the Tk backend
matplotlib.use('TkAgg')

from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from mpl_toolkits.mplot3d import Axes3D
import subprocess
from Tkinter import (Button, END, Frame, Label, OptionMenu, StringVar, Tk, W)

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

        self.method = StringVar(self.frame)
        self.method.set(methods.keys()[2])
        self.system = StringVar(self.frame)
        self.system.set(systems.keys()[0])

        # TODO: Add entry widgets
        self.dt = 0.01
        self.t0 = 0.0
        self.X0 = (0.01, 0.01, 0.01)
        self.n = 10000

        self.label_methods = Label(self.frame, text="Method:")
        self.menu_methods = OptionMenu(self.frame, self.method,
                                       *methods.keys(),
                                       command=self.menu_onclick)

        self.label_systems = Label(self.frame, text="System:")
        self.menu_systems = OptionMenu(self.frame, self.system,
                                       *systems.keys(),
                                       command=self.menu_onclick)

        self.figure = Figure(figsize=(7.8, 5))
        self.canvas = FigureCanvasTkAgg(self.figure, master=master)

        self.button_plot = Button(self.frame, text="Plot", command=self.plot)

        self.button_clear = Button(self.frame, text="Clear",
                                   command=self.clear_figure)

        self.button_quit = Button(self.frame, text="Quit",
                                  command=self.frame.quit)
        
        # Arrange widgets
        self.label_methods.grid(row=0, column=0)
        self.menu_methods.grid(row=0, column=1)
        self.label_systems.grid(row=0, column=2)
        self.menu_systems.grid(row=0, column=3)
        self.canvas.get_tk_widget().grid(row=2, column=0)
        self.button_plot.grid(row=3, column=0)
        self.button_clear.grid(row=3, column=1)
        self.button_quit.grid(row=3, column=4)

    def plot(self):
        cmd = ("../src/integrate %s %s -d %s -t %s "
               % (methods[self.method.get()], systems[self.system.get()],
                  self.dt, self.t0))
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
            self.graph = self.figure.add_subplot(111, projection='3d')
            self.graph.plot(arrays[1], arrays[2])
        elif len(arrays) == 4:
            self.graph = self.figure.add_subplot(111, projection='3d')
            self.graph.plot(arrays[1], arrays[2], arrays[3])
        self.canvas.draw()

    def menu_onclick(self, event):
        print "Integrating %s using %s" % (self.system.get(),
                                           self.method.get())
        self.clear_figure()

    def clear_figure(self):
        self.figure.clear()
        self.canvas.draw()
        print "----- Cleared figure -----"

def center(win):
    win.update_idletasks()
    width = win.winfo_width()
    height = win.winfo_height()
    x = (win.winfo_screenwidth() // 2) - (width // 2)
    y = (win.winfo_screenheight() // 2) - (height // 2)
    win.geometry('{}x{}+{}+{}'.format(width, height, x, y))

def main():
    root = Tk()
    root.geometry('640x640')
    center(root)
    odeintgui = OdeIntGui(root)
    root.mainloop()

if __name__ == '__main__':
    main()
