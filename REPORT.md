## Part 3 - Exercise 1: Mass-Spring System 
### 1. Testing existing explicit Euler method
Our goal in this task was to examine the behavior of the explicit Euler method for the mass-spring system. To obtain a reasonable estimation, the system was tested using different time steps and end times. All tests were automated using the `runmassspring.sh` script.


Explicit Euler method can be implemented as: 

$$
y_{n+1} = y_n + h \cdot f(x_n, y_n)
$$

Where:  
- $y_n$ — current value of the variable  
- $y_{n+1}$ — next value of the variable  
- $h$ — time step  
- $f(x_n, y_n)$ — derivative of $y$ at step $n$


Our system of mass-sprint is described by the following relation:
$$
y_0' = y_1
$$

$$
y_1' = -\frac{k}{m} y_0
$$



With the original settings, we obtain the following results:

<div style="display: inline-block; text-align: center; margin-right: 10px;">
  <img src="demos/plots/explicit/explicit Time_evolution_4 pi_100 steps_.png" alt="Time_evolution" width="300">
</div>
<div style="display: inline-block; text-align: center;">
  <img src="demos/plots/explicit/explicit Phase_plot_4 pi_100 steps_.png" alt="Phase_plot" width="300">
</div>

As we can observe, this is not the solution for a mass-spring system without damping. A dissipative error is evident, as the magnitude of the motion increases over time. The solution appears to "explode," causing both the velocity and position to tend toward infinity. In an undamped system, however, the magnitudes of velocity and position should remain constant over time. Additionally, we would expect the position-velocity chart to take an elliptical shape, not exhibit divergence.
We can assume that the phase relationship between displacement and velocity is correct and equal to 90 degrees, meaning no dispersive error is observed.



By increasing the step size, we can fix this for short times:

<div style="display: inline-block; text-align: center; margin-right: 10px;">
  <img src="demos/plots/explicit/explicit Time_evolution_4 pi_10000 steps_.png" alt="Time_evolution" width="300">
</div>
<div style="display: inline-block; text-align: center;">
  <img src="demos/plots/explicit/explicit Phase_plot_4 pi_10000 steps_.png" alt="Phase_plot" width="300">
</div>

The results of the simulation align with expectations, i.e., the relationship between velocity and position is conserved over time. However, it only seems to work properly for a limited duration. As the simulation time increases, instability in the system becomes apparent, triggering dissipative errors and rendering the algorithm unreliable.

<div style="display: inline-block; text-align: center; margin-right: 10px;">
  <img src="demos/plots/explicit/explicit Time_evolution_60 pi_10000 steps_.png" alt="Time_evolution" width="300">
</div>
<div style="display: inline-block; text-align: center;">
  <img src="demos/plots/explicit/explicit Phase_plot_60 pi_10000 steps_.png" alt="Phase_plot" width="300">
</div>

Using this approach for shorter simulation times, increasing the timestep improves the solution up to a certain point. One could suspect a hidden relationship between the timestep and the simulation interval that must be maintained to ensure a stable solution within the given time frame.

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



`comment: i will finish the report later - M.C`

For implementing this method, we copied the Explicit Euler method in `timestepper.hpp` and changed a view details.

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