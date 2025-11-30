# Numerical Methods for ODEs — Homework Report  


---

## 1. Introduction
This report summarizes the implementation and results of several numerical methods for solving ordinary differential equations (ODEs). It covers:

- **HW 17.4:** Implicit Euler, Crank–Nicolson, and RC circuit simulation  
- **HW 18:** Forward-mode Automatic Differentiation  
- **HW 19:** Runge–Kutta methods (RK2 and RK4)

All methods were integrated into a unified `TimeStepper` framework and tested using the provided mass–spring and RC circuits.

---

## 2. HW 17.4 — Implicit Euler, Crank–Nicolson & RC Circuit

### 2.1 Mass–Spring System
We study the classical system:

$$
x' = v, \qquad v' = -\frac{k}{m}x
$$

This describes a harmonic oscillator.  
The following methods were implemented and tested:

- Explicit Euler  
- Improved Euler  
- **Implicit Euler**  
- **Crank–Nicolson**

Plots for the solution trajectories and phase-space behavior were generated.

#### **Observations**
- **Explicit Euler**: noticeable phase error and amplitude drift.  
- **Improved Euler**: better accuracy but still accumulates drift.  
- **Implicit Euler**: unconditionally stable, slightly overdamped.  
- **Crank–Nicolson**: best accuracy among Euler-type schemes, symmetric and stable.

---

### 2.2 RC Circuit ODE
The charging of a capacitor follows:

$$
C \frac{dU_c}{dt} = \frac{U_s - U_c}{R}
$$

which was written in autonomous form and solved using all four methods.

#### **Observations**
- Explicit Euler can behave poorly for stiff choices of \( R \) and \( C \).  
- Improved Euler is stable for moderate step sizes.  
- Implicit Euler and Crank–Nicolson give smooth, stable curves.  
- Crank–Nicolson consistently provides the most accurate evolution.

Plots of capacitor voltage vs. time were produced for comparison.

---

## 3. HW 18 — Automatic Differentiation (AD)

A forward-mode **AutoDiff<N,T>** class was implemented to automatically compute derivatives.

### 3.1 Features Implemented
- Stores:
  - a **value**  
  - a **vector of derivatives** of size `N`
- Supports any number of variables.
- Operator overloading implemented:
  - `+`, `-`, `*`, `/`
- Elementary functions implemented:
  - `sin`, `cos`, `exp`, `log`, `pow`
- Variables created as `Variable<I>` with correct derivative seeding.

### 3.2 Test Function
$$
f(x) = x^2 + 3\sin(x)
$$

Derivatives computed using AutoDiff matched numerical finite-difference approximations.

#### **Observation**
- AutoDiff produced derivatives that matched numerical approximations accurately.
- Confirms correct implementation of forward-mode AD.

---

## 4. HW 19 — Runge–Kutta Methods

Two Runge–Kutta methods were added:

### 4.1 RK2 (Midpoint Method)
- Second-order accurate
- Better accuracy than Euler methods
- Simple to implement

### 4.2 RK4 (Classical 4th-order Method)
- Very high accuracy
- Error decreases rapidly with smaller steps
- Standard method for non-stiff ODEs

### 4.3 Testing and Plots
Both RK2 and RK4 were tested with:

- 50 steps  
- 100 steps  
- 200 steps  
- 400 steps  

Plots were generated using the mass–spring system.

#### **Observations**
- **RK2**: noticeable improvement over Euler, but still shows small phase drift.  
- **RK4**: extremely accurate even with large time steps.  
- With 200+ steps, RK4 is almost indistinguishable from the true harmonic oscillator solution.  
- RK4’s error decreases much faster than lower-order methods.  

This demonstrates the advantage of higher-order time integration.

---

## 5. Overall Conclusions

- **Implicit Euler** is stable and robust for stiff systems.  
- **Crank–Nicolson** provides the best accuracy among Euler-based integrators.  
- **Automatic Differentiation** enables exact derivative calculation and works well with templated operations.  
- **RK4** is the most accurate method implemented and performs exceptionally even with coarse step sizes.  
- The unified ODE framework allowed consistent comparison of all methods across the same test problems.

---
