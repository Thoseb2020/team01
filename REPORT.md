## Part 3 - Exercise 1: Mass-Spring System 
### 1. Testing existing explicit Euler method
We built the exlicit Euer method for the mass-spring system.  
Several different time-steps and end-times were tried out automatically with the shell script "runmassspring.sh".  

With the original settings, we obtain the following results:

<div style="display: inline-block; text-align: center; margin-right: 10px;">
  <img src="demos/plots/Time_evolution_4%20pi_100%20steps_.png" alt="Time_evolution" width="300">
</div>
<div style="display: inline-block; text-align: center;">
  <img src="demos/plots/Phase_plot_4%20pi_100%20steps_.png" alt="Phase_plot" width="300">
</div>

Clearly, this does not represent the energy conversation law which is of course always observed in the harmonic oscillator.

By increasing the step size, we can fix this for short times:

<div style="display: inline-block; text-align: center; margin-right: 10px;">
  <img src="demos/plots/Time_evolution_4%20pi_10000%20steps_.png" alt="Time_evolution" width="300">
</div>
<div style="display: inline-block; text-align: center;">
  <img src="demos/plots/Phase_plot_4%20pi_10000%20steps_.png" alt="Phase_plot" width="300">
</div>

If we observe the simulation with this stepsize however, we will see that for larger times the energy is also increasing...

<div style="display: inline-block; text-align: center; margin-right: 10px;">
  <img src="demos/plots/Time_evolution_60%20pi_10000%20steps_.png" alt="Time_evolution" width="300">
</div>
<div style="display: inline-block; text-align: center;">
  <img src="demos/plots/Phase_plot_60%20pi_10000%20steps_.png" alt="Phase_plot" width="300">
</div>

... which can again be fixed by an even larger stepsize ...
<div style="display: inline-block; text-align: center; margin-right: 10px;">
  <img src="demos/plots/Time_evolution_60%20pi_1000000%20steps_.png" alt="Time_evolution" width="300">
</div>
<div style="display: inline-block; text-align: center;">
  <img src="demos/plots/Phase_plot_60%20pi_1000000%20steps_.png" alt="Phase_plot" width="300">
</div>