## Part 3 - Exercise 1: Mass-Spring System 
### 1. Testing existing explicit Euler method
Our goal in this task was to examine the behavior of the explicit Euler method for the mass-spring system. To obtain a reasonable estimation, the system was tested using different time steps and end times. All tests were automated using the `runmassspring.sh` script.


Explicit Euler method can be implemented as: 

$$
y_{n+1} = y_n + h \cdot f(y_n)
$$

Where:  
- $y_n$ — current value of the variable  
- $y_{n+1}$ — next value of the variable  
- $h$ — time step  
- $f(y_n)$ — derivative of $y$ at step $n$


Our system of mass-sprint is described by the following relation:

$$
y_{0}' = y_1
$$

$$
y_{1}' = -\frac{k}{m} y_0
$$



With the original settings, we obtain the following results:

<div style="display: inline-block; text-align: center; margin-right: 10px;">
  <img src="demos/plots/explicit/explicit Time_evolution_4 pi_100 steps_.png" alt="Time_evolution" width="300">
</div>
<div style="display: inline-block; text-align: center;">
  <img src="demos/plots/explicit/explicit Phase_plot_4 pi_100 steps_.png" alt="Phase_plot" width="300">
</div>

As we can observe, this is not the solution for a mass-spring system without damping. A dissipative error is evident, as the magnitude of the motion increases over time. The solution appears to "explode," causing both the velocity and position to tend toward infinity. In an undamped system, however, the magnitudes of velocity and position should remain constant over time. Position and velocity profiles should be in the form similar to harmonic oscilator i.e:

$$x(t) = Acos(\omega_0 t + \phi)$$
$$v(t) = -A\omega_0 sin(\omega_0 t + \phi)$$

where:

$$\omega = \frac{k}{m}$$

This proves that amplitudes should remain constant over time and profiles being shifted as relation between sine and cosine

Additionally, we would expect the position-velocity chart to take an elliptical shape, not exhibit divergence.
We can assume that the phase relationship between displacement and velocity is correct and equal to 90 degrees, meaning no dispersive error is observed. 


By increasing the step size, we can fix this for short intervals:

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

To achieve better performance in the spring-mass system, we introduce the Improved Euler Method, which is defined as:

$$
\tilde{y} = y_n + \frac{\tau}{2} f(y_n)
$$

$$
y_{n+1} = y_n + \tau f(\tilde{y})
$$

In order to implement replace $f(y_n)$ with  $f(\tilde{y})$ we had to make changes in file `timestepper.hpp` and modify a few other view details.



<div style="display: inline-block; text-align: center; margin-right: 10px;">
  <img src="demos/plots/explicit/explicit Phase_plot_10 pi_100 steps_.png" alt="Time_evolution" width="300">
</div>
<div style="display: inline-block; text-align: center;">
  <img src="demos/plots/improved/improved Phase_plot_10 pi_100 steps_.png" alt="Phase_plot" width="300">  
</div>

That change has introduced a major improvement; however, over time we still cannot be certain about the system's stability at aribtary numer of steps. One would expect the solution to remain 'proper' as time approaches infinity.

<div style="display: inline-block; text-align: center; margin-right: 10px;">
  <img src="demos/plots/explicit/explicit Time_evolution_60 pi_5000 steps_.png" alt="Time_evolution" width="300">
</div>
<div style="display: inline-block; text-align: center;">
  <img src="demos/plots/improved/improved Time_evolution_60 pi_5000 steps_.png" alt="Phase_plot" width="300">
</div>

Introducing a significant increase in the number of timesteps—something that would completely destabilize the classical explicit Euler method—has remarkably stabilized the behavior of the Improved Euler method, both in terms of velocity and position over time. There is no noticeable dissipative or dispersive error, and the phase plot shows that the position-velocity relationship is ideally conserved as an elliptical trajectory. We can be sure that some very small diffusive error still exists, which could grow if the simulation were extended further; however, the simulation was concluded at this step. Nevertheless, this behavior demonstrates that the system is stable. In other words, according to the rules of the stability definition, increasing the "cost" in terms of timesteps improves the accuracy of the solution

$$
\lim_{\tau \to 0} |y_n - y(t_n)| = 0
$$

where 
$$
\tau = \frac{t_{final}-t_{initial}}{N_{steps}}
$$

<div style="display: inline-block; text-align: center; margin-right: 10px;">
  <img src="demos/plots/explicit/explicit Phase_plot_60 pi_5000 steps_.png" alt="Time_evolution" width="300">
</div>
<div style="display: inline-block; text-align: center;">
  <img src="demos/plots/improved/improved Phase_plot_60 pi_5000 steps_.png" alt="Phase_plot" width="300">
</div>