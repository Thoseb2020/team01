## Part 3 - Exercise 1: Mass-Spring System 
### 1. Testing existing explicit Euler method
We built the exlicit Euer method for the mass-spring system.  
Several different time-steps and end-times were tried out automatically with the shell script "runmassspring.sh".  

With the original settings, we obtain the following results:

<div style="display: inline-block; text-align: center; margin-right: 10px;">
  <img src="demos/plots/explicit/explicit Time_evolution_4 pi_100 steps_.png" alt="Time_evolution" width="300">
</div>
<div style="display: inline-block; text-align: center;">
  <img src="demos/plots/explicit/explicit Phase_plot_4 pi_100 steps_.png" alt="Phase_plot" width="300">
</div>

Clearly, this does not represent the energy conversation law which is of course always observed in the harmonic oscillator.

By increasing the step size, we can fix this for short times:

<div style="display: inline-block; text-align: center; margin-right: 10px;">
  <img src="demos/plots/explicit/explicit Time_evolution_4 pi_10000 steps_.png" alt="Time_evolution" width="300">
</div>
<div style="display: inline-block; text-align: center;">
  <img src="demos/plots/explicit/explicit Phase_plot_4 pi_10000 steps_.png" alt="Phase_plot" width="300">
</div>

If we observe the simulation with this stepsize however, we will see that for larger times the energy is also increasing...

<div style="display: inline-block; text-align: center; margin-right: 10px;">
  <img src="demos/plots/explicit/explicit Time_evolution_60 pi_10000 steps_.png" alt="Time_evolution" width="300">
</div>
<div style="display: inline-block; text-align: center;">
  <img src="demos/plots/explicit/explicit Phase_plot_60 pi_10000 steps_.png" alt="Phase_plot" width="300">
</div>

... which can again be fixed by an even larger stepsize ...
<div style="display: inline-block; text-align: center; margin-right: 10px;">
  <img src="demos/plots/explicit/explicit Time_evolution_60 pi_1000000 steps_.png" alt="Time_evolution" width="300">
</div>
<div style="display: inline-block; text-align: center;">
  <img src="demos/plots/explicit/explicit Phase_plot_60 pi_1000000 steps_.png" alt="Phase_plot" width="300">
</div>


### 2. Implementing improved euler method

The Improved euler Method is defined as the following algorithm:
$$
\tilde{y} = y_n + \frac{\tau}{2} f(y_n)
$$

$$
y_{n+1} = y_n + \tau f(\tilde{y})
$$

For implementing this method, we copied the Explicit Euler method in timestepper.hpp and changed a view details.

The Improved euler method achieves far better results compared to the explicit method.

The Improved method is in general more accurate for the same number of steps:  

<div style="display: inline-block; text-align: center; margin-right: 10px;">
  <img src="demos/plots/explicit/explicit Phase_plot_10 pi_100 steps_.png" alt="Time_evolution" width="300">
</div>
<div style="display: inline-block; text-align: center;">
  <img src="demos/plots/improved/improved Phase_plot_10 pi_100 steps_.png" alt="Phase_plot" width="300">  
</div>

It is accurate for step sizes were the explicit method still diverges:

<div style="display: inline-block; text-align: center; margin-right: 10px;">
  <img src="demos/plots/explicit/explicit Time_evolution_60 pi_5000 steps_.png" alt="Time_evolution" width="300">
</div>
<div style="display: inline-block; text-align: center;">
  <img src="demos/plots/improved/improved Time_evolution_60 pi_5000 steps_.png" alt="Phase_plot" width="300">
</div>


<div style="display: inline-block; text-align: center; margin-right: 10px;">
  <img src="demos/plots/explicit/explicit Phase_plot_60 pi_5000 steps_.png" alt="Time_evolution" width="300">
</div>
<div style="display: inline-block; text-align: center;">
  <img src="demos/plots/improved/improved Phase_plot_60 pi_5000 steps_.png" alt="Phase_plot" width="300">
</div>