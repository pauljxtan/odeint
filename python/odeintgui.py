#!/usr/bin/python

import matplotlib
# use the Tk backend
matplotlib.use('TkAgg')

from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from mpl_toolkits.mplot3d import Axes3D
import subprocess
from Tkinter import (Button, DoubleVar, END, Entry, Frame, IntVar, Label,
                     OptionMenu, StringVar, Tk, W)

methods = {
        "Forward Euler"        : 'fweuler',
        "4th-order Runge-Kutta": 'rk4',
        "Bulirsch-Stoer"       : 'bulsto',
        }

systems = {
        "Lorenz"        : 'lorenz',
        "Lotka-Volterra": 'lotka',
        }

dims = {
        "Lorenz": 3,
        "Lotka-Volterra" : 2,
        }

class OdeIntGui:
    def __init__(self, master):
        self.frame = Frame(master)
        self.frame.grid()

        #--- Subframes
        self.frame_menus = Frame(self.frame)
        self.frame_entries = Frame(self.frame)
        self.frame_canvas = Frame(self.frame)
        self.frame_buttons = Frame(self.frame)

        self.frame_menus.grid(row=0)
        self.frame_entries.grid(row=1)
        self.frame_canvas.grid(row=2)
        self.frame_buttons.grid(row=3)
        #---

        #--- String variables
        self.method = StringVar(self.frame_menus)
        self.method.set(methods.keys()[2])
        self.system = StringVar(self.frame_menus)
        self.system.set(systems.keys()[0])
        #---

        #--- Double variables
        self.dt = DoubleVar(self.frame_entries)
        self.t0 = DoubleVar(self.frame_entries)
        self.X0a = DoubleVar(self.frame_entries)
        self.X0b = DoubleVar(self.frame_entries)
        self.X0c = DoubleVar(self.frame_entries)
        #---

        #--- Integer variables
        self.n = IntVar(self.frame_entries)
        #---

        #--- Menu subframe
        self.label_methods = Label(self.frame_menus, text="Method:")
        self.menu_methods = OptionMenu(self.frame_menus, self.method,
                                       *methods.keys(),
                                       command=self.menu_onclick)
        self.label_systems = Label(self.frame_menus, text="System:")
        self.menu_systems = OptionMenu(self.frame_menus, self.system,
                                       *systems.keys(),
                                       command=self.menu_onclick)
        # Put the "number of steps" entry here too
        self.label_n = Label(self.frame_menus, text="Number of steps:")
        self.entry_n = Entry(self.frame_menus, textvariable=self.n,
                             width=9)

        self.label_methods.grid(row=0, column=0)
        self.menu_methods.grid(row=0, column=1)
        self.label_systems.grid(row=0, column=2)
        self.menu_systems.grid(row=0, column=3)
        self.label_n.grid(row=0, column=4)
        self.entry_n.grid(row=0, column=5)
        #---

        #--- Entry subframe
        self.label_dt = Label(self.frame_entries, text="Step size:")
        self.entry_dt = Entry(self.frame_entries, textvariable=self.dt,
                              width=9)

        self.label_t0 = Label(self.frame_entries, text="Initial time:")
        self.entry_t0 = Entry(self.frame_entries, textvariable=self.t0,
                              width=9)

        self.label_X0 = Label(self.frame_entries, text="Initial state:")
        self.entry_X0 = [Entry(self.frame_entries, textvariable=self.X0a,
                               width=9),
                         Entry(self.frame_entries, textvariable=self.X0b,
                               width=9)]
        if dims[self.system.get()] == 3:
            self.entry_X0.append(Entry(self.frame_entries,
                                       textvariable=self.X0c,
                                       width=9))

        self.label_dt.grid(row=0, column=0)
        self.entry_dt.grid(row=0, column=1)
        self.label_t0.grid(row=0, column=2)
        self.entry_t0.grid(row=0, column=3)
        self.label_X0.grid(row=0, column=4)
        self.entry_X0[0].grid(row=0, column=5)
        self.entry_X0[1].grid(row=0, column=6)
        if dims[self.system.get()] == 3:
            self.entry_X0[2].grid(row=0, column=7)
        #---

        #--- Canvas subframe
        self.figure = Figure(figsize=(7.8, 4.9))
        self.canvas = FigureCanvasTkAgg(self.figure, master=self.frame_canvas)

        self.canvas.get_tk_widget().grid(row=2, column=0)
        #---

        #--- Button subframe
        self.button_plot = Button(self.frame_buttons, text="Plot",
                                  command=self.plot)
        self.button_clear = Button(self.frame_buttons, text="Clear",
                                   command=self.clear_figure)
        self.button_quit = Button(self.frame_buttons, text="Quit",
                                  command=self.frame.quit)
        
        self.button_plot.grid(row=3, column=0)
        self.button_clear.grid(row=3, column=1)
        self.button_quit.grid(row=3, column=2)
        #---

    def plot(self):
        cmd = ("../src/integrate %s %s -d %s -t %s "
               % (methods[self.method.get()], systems[self.system.get()],
                  self.dt.get(), self.t0.get()))
        if dims[self.system.get()] == 2:
            cmd += "-x %s -x %s " % (self.X0a.get(), self.X0b.get())
        elif dims[self.system.get()] == 3:
            cmd += "-x %s -x %s -x %s " % (self.X0a.get(), self.X0b.get(),
                                           self.X0c.get())
        cmd += "-n %s -v " % self.n.get()
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
        print "Integrate %s using %s" % (self.system.get(),
                                         self.method.get())
        
        # Adjust number of state variables
        if dims[self.system.get()] == 2:
            self.entry_X0[2].grid_forget()
        elif dims[self.system.get()] == 3:
            self.entry_X0[2].grid(row=0, column=7)

        self.clear_figure()

    def clear_figure(self):
        self.figure.clear()
        self.canvas.draw()

def center(win):
    win.update_idletasks()
    width = win.winfo_width()
    height = win.winfo_height()
    x = (win.winfo_screenwidth() // 2) - (width // 2)
    y = (win.winfo_screenheight() // 2) - (height // 2)
    win.geometry('{}x{}+{}+{}'.format(width, height, x, y))

def main():
    root = Tk()
    root.geometry('640x480')
    center(root)
    odeintgui = OdeIntGui(root)
    root.mainloop()

if __name__ == '__main__':
    main()
