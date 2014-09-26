#!/usr/bin/python

# TODO:
#     allow user to choose what variables to plot
#     (setting custom labels+entries for each system might be necessary)

import matplotlib
# use the Tk backend
matplotlib.use('TkAgg')
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from mpl_toolkits.mplot3d import Axes3D
import subprocess
import time

from Tkinter import (Button, DoubleVar, END, Entry, Frame, IntVar, Label,
                     OptionMenu, StringVar, Tk, W)

methods = {
        "Forward Euler"        : 'fweuler',
        "4th-order Runge-Kutta": 'rk4',
        "Bulirsch-Stoer"       : 'bulsto',
        }

systems = {
        "Brusselator"               : 'brusselator',
        "Chen system"               : 'chen',
        "Damped spring"             : 'damped_spring',
        "Double pendulum"           : 'double_pendulum',
        "Duffing equation"          : 'duffing',
        "Lorenz system"             : 'lorenz',
        "Lotka-Volterra equations"  : 'lotka',
        "Parrot system"             : 'parrot',
        "Rossler system"            : 'rossler',
        "Symmetric top"             : 'symmetric_top',
        "Van der Pol oscillator"    : 'vanderpol',
        "2-D Van der Pol oscillator": 'vanderpol2d',
        }

dims = {
        "Brusselator"               : 2,
        "Chen system"               : 3,
        "Damped spring"             : 2,
        "Double pendulum"           : 4,
        "Duffing equation"          : 2,
        "Lorenz system"             : 3,
        "Lotka-Volterra equations"  : 2,
        "Parrot system"             : 2,
        "Rossler system"            : 3,
        "Symmetric top"             : 6,
        "Van der Pol oscillator"    : 2,
        "2-D Van der Pol oscillator": 2,
        }

state_vars = {
        "Brusselator"               : ("x", "y"),
        "Chen system"               : ("x", "y", "z"),
        "Damped spring"             : ("x", "v"),
        "Double pendulum"           : ("theta_1", "theta_2", "p_1", "p_2"),
        "Duffing equation"          : ("x", "v"),
        "Lorenz system"             : ("x", "y", "z"),
        "Lotka-Volterra equations"  : ("x", "y"),
        "Parrot system"             : ("x", "y"),
        "Rossler system"            : ("x", "y", "z"),
        "Symmetric top"             : ("theta", "phi", "psi", "theta_dot",
                                       "phi_dot", "psi_dot"),
        "Van der Pol oscillator"    : ("x", "v"),
        "2-D Van der Pol oscillator": ("x", "y"),
        }

#class StateVars(object):
#    pass


class OdeIntGui(object):
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
        self.system = StringVar(self.frame_menus)
        # SET DEFAULTS HERE
        self.method.set("4th-order Runge-Kutta")
        self.system.set("Lorenz system")
        self.prev_system = self.system.get()
        #---

        #--- Double variables
        self.dt = DoubleVar(self.frame_entries)
        self.t0 = DoubleVar(self.frame_entries)
        self.X0a = DoubleVar(self.frame_entries)
        self.X0b = DoubleVar(self.frame_entries)
        self.X0c = DoubleVar(self.frame_entries)
        self.X0d = DoubleVar(self.frame_entries)
        self.X0e = DoubleVar(self.frame_entries)
        self.X0f = DoubleVar(self.frame_entries)
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
                             width=5)

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
                              width=5)

        self.label_t0 = Label(self.frame_entries, text="Initial time:")
        self.entry_t0 = Entry(self.frame_entries, textvariable=self.t0,
                              width=5)

        self.label_X0 = Label(self.frame_entries, text="Initial state:")
        self.entry_X0 = [
            Entry(self.frame_entries, textvariable=self.X0a, width=5),
            Entry(self.frame_entries, textvariable=self.X0b, width=5),
            Entry(self.frame_entries, textvariable=self.X0c, width=5),
            Entry(self.frame_entries, textvariable=self.X0d, width=5),
            Entry(self.frame_entries, textvariable=self.X0e, width=5),
            Entry(self.frame_entries, textvariable=self.X0f, width=5),
            ]

        self.label_dt.grid(row=0, column=0)
        self.entry_dt.grid(row=0, column=1)
        self.label_t0.grid(row=0, column=2)
        self.entry_t0.grid(row=0, column=3)
        self.label_X0.grid(row=0, column=4)
        self.entry_X0[0].grid(row=0, column=6)
        self.entry_X0[1].grid(row=0, column=8)
        if dims[self.system.get()] >= 3:
            self.entry_X0[2].grid(row=0, column=10)
        if dims[self.system.get()] >= 4:
            self.entry_X0[3].grid(row=0, column=12)
        if dims[self.system.get()] >= 5:
            self.entry_X0[4].grid(row=0, column=14)
        if dims[self.system.get()] >= 6:
            self.entry_X0[5].grid(row=0, column=16)

        self.label_X0a = Label(self.frame_entries, text="")
        self.label_X0b = Label(self.frame_entries, text="")
        self.label_X0c = Label(self.frame_entries, text="")
        self.label_X0d = Label(self.frame_entries, text="")
        self.label_X0e = Label(self.frame_entries, text="")
        self.label_X0f = Label(self.frame_entries, text="")

        self.label_X0a.grid(row=0, column=5)
        self.label_X0b.grid(row=0, column=7)
        self.label_X0c.grid(row=0, column=9)
        self.label_X0d.grid(row=0, column=11)
        self.label_X0e.grid(row=0, column=13)
        self.label_X0f.grid(row=0, column=15)

        self.label_X0a.config(text=state_vars[self.system.get()][0])
        self.label_X0b.config(text=state_vars[self.system.get()][1])
        if dims[self.system.get()] >= 3:
            self.label_X0c.config(text=state_vars[self.system.get()][2])
        if dims[self.system.get()] >= 4:
            self.label_X0d.config(text=state_vars[self.system.get()][3])
        if dims[self.system.get()] >= 5:
            self.label_X0e.config(text=state_vars[self.system.get()][4])
        if dims[self.system.get()] >= 6:
            self.label_X0f.config(text=state_vars[self.system.get()][5])
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
    
    def menu_onclick(self, event):
        print "%s with %s" % (self.system.get(), self.method.get())
        
        # Adjust number of state variables
        self.entry_X0[0].grid_forget()
        self.entry_X0[1].grid_forget()
        if dims[self.prev_system] >= 3:
            self.entry_X0[2].grid_forget()
        if dims[self.prev_system] >= 4:
            self.entry_X0[3].grid_forget()
        if dims[self.prev_system] >= 5:
            self.entry_X0[4].grid_forget()
        if dims[self.prev_system] >= 6:
            self.entry_X0[5].grid_forget()

        self.entry_X0[0].grid(row=0, column=6)
        self.entry_X0[1].grid(row=0, column=8)
        if dims[self.system.get()] >= 3:
            self.entry_X0[2].grid(row=0, column=10)
        if dims[self.system.get()] >= 4:
            self.entry_X0[3].grid(row=0, column=12)
        if dims[self.system.get()] >= 5:
            self.entry_X0[4].grid(row=0, column=14)
        if dims[self.system.get()] >= 6:
            self.entry_X0[5].grid(row=0, column=16)
        
        # Update labels for state variables
        self.label_X0a.config(text="")
        self.label_X0b.config(text="")
        if dims[self.prev_system] >= 3:
            self.label_X0c.config(text="")
        if dims[self.prev_system] >= 4:
            self.label_X0f.config(text="")
        if dims[self.prev_system] >= 5:
            self.label_X0e.config(text="")
        if dims[self.prev_system] >= 6:
            self.label_X0f.config(text="")
        self.label_X0a.config(text=state_vars[self.system.get()][0])
        self.label_X0b.config(text=state_vars[self.system.get()][1])
        if dims[self.system.get()] >= 3:
            self.label_X0c.config(text=state_vars[self.system.get()][2])
        if dims[self.system.get()] >= 4:
            self.label_X0d.config(text=state_vars[self.system.get()][3])
        if dims[self.system.get()] >= 5:
            self.label_X0e.config(text=state_vars[self.system.get()][4])
        if dims[self.system.get()] >= 6:
            self.label_X0f.config(text=state_vars[self.system.get()][5])

        self.clear_figure()
        
        prev_system = self.system.get()

    def plot(self):
        cmd = ("../src/integrate %s %s -d %s -t %s "
               % (methods[self.method.get()], systems[self.system.get()],
                  self.dt.get(), self.t0.get()))
        if dims[self.system.get()] >= 2:
            cmd += "-x %s -x %s " % (self.X0a.get(), self.X0b.get())
        if dims[self.system.get()] >= 3:
            cmd += "-x %s " % self.X0c.get()
        if dims[self.system.get()] >= 4:
            cmd += "-x %s " % self.X0d.get()
        if dims[self.system.get()] >= 5:
            cmd += "-x %s " % self.X0e.get()
        if dims[self.system.get()] >= 6:
            cmd += "-x %s " % self.X0f.get()
        cmd += "-n %s -v " % self.n.get()
        print cmd
        
        print "Computing..."

        t0 = time.clock()
        # heard "shell=True" might not be safe?
        integration = subprocess.Popen(cmd, stdout=subprocess.PIPE, shell=True)
        t1 = time.clock()
        print "Finished in %.9f s" % (t1 - t0)
        
        print "Processing data..."
        integration_stdout = integration.communicate()[0]

        print "Plotting..."
        data = []
        for line in integration_stdout.split("\n"):
            if line != "":
                data.append(map(float, line.split(" ")))
        arrays = zip(*data)
        t = arrays[0]
        # TODO: fix this
        # ===== HACK ALERT =====
        if len(arrays[1:]) == 2:
            self.graph = self.figure.add_subplot(111, projection='3d')
            self.graph.plot(arrays[1], arrays[2])
        elif len(arrays[1:]) == 3:
            self.graph = self.figure.add_subplot(111, projection='3d')
            self.graph.plot(arrays[1], arrays[2], arrays[3])
        #--- Especially need to fix these
        elif len(arrays[1:]) == 4:
            self.graph = self.figure.add_subplot(111, projection='3d')
            self.graph.plot(arrays[1], arrays[2], arrays[3])
        elif len(arrays[1:]) == 6:
            self.graph = self.figure.add_subplot(111, projection='3d')
            self.graph.plot(arrays[1], arrays[2], arrays[3])
        #---
        self.canvas.draw()

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
    root.title("odeint GUI")
    center(root)
    odeintgui = OdeIntGui(root)
    root.mainloop()

if __name__ == '__main__':
    main()
