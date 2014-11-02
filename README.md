# odeint #
An easily extensible ODE integrator in C. Mainly a learning project for practicing with pointers, memory allocation and data structures (used to emulate an integrator "class"); not really optimized for efficiency. 

Documented for Doxygen in Qt style -- see http://pauljxtan.github.io/odeint.

### Currently implemented ###
Method (struct_name):
* 4th-order Runge-Kutta (rk4)
* Forward Euler (fweuler)
* Bulirsch-Stoer (bulsto)

System (function_name):
* Brusselator (brusselator)
* Chen system (chen)
* Damped spring (damped_spring)
* Double pendulum (double_pendulum)
* Duffing equation (duffing)
* Lorenz attractor (lorenz)
* Lotka-Volterra equations (lotka)
* Parrot system {Borelli & Coleman 1987} (parrot)
* Rossler system (rossler)
* Symmetric top (symmetric_top)
* Van der pol oscillator (vanderpol)
* Van der pol oscillator 2-D (vanderpol2d)

### Quick start ###
Integrate the Lorenz attractor using RK4, with the following parameters:
* time-step size  : 0.01
* initial time    : 0.0
* initial state   : x=0.01, y=0.01, z=0.01
* number of steps : 10000
* verbose mode    : yes (might be a big bottleneck for program speed)
* print parameters: yes
* write to file   : yes [filename="lorenz.dat"]

```bash
$ ./src/integrate rk4 lorenz -d 0.01 -t 0.0 -x 0.01 -x 0.01 -x 0.01 -n 10000 -v -y -w
```

Then one could visualize the results with gnuplot, for example:
gnuplot> splot "lorenz.dat" using 2:3:4 with lines

(To browse all available systems, run ./integrate without arguments.)

### Real-time plotting ###
We can plot the time-series for each variable in real-time by piping the integration data into the Python plotting script, e.g.:

```bash
$ ./integrate rk4 lotka -d 0.05 -t 0.0 -x 10.0 -x 5.0 -n 1000 -v | ./plot_stdin_timeseries.py
```

### Adding systems ###
1. Declare the function in ./include/eoms.h
2. Define the constants in ./include/eoms.h
3. Add the function to the function table and function list in ./src/eoms.c
4. Define the function in ./src/eoms.c
5. All set!

### GUI ###
A Tkinter-based GUI is located at ./python/odeintgui.py. Requires matplotlib 1.0.0+ with the Tk backend.

### To-do ###
* Add "kwargs" functionality for passing additional parameters (e.g. constants) to integrator

### Future ###
* Adaptive methods upcoming...
