# Report 3 — Mass–Spring System, Constraints, and Mechanical Simulation


## 1. Introduction

This report documents the implementation and simulation of a multi-body mechanical system based on masses, springs, and distance constraints.  
The work corresponds to **Exercise 20**, which requires:

- extending the existing framework,  
- adding new mechanical structures,  
- enforcing constraints,  
- implementing the exact Jacobian, and  
- running several demonstration simulations.

The extended system now supports:

- gravitational forces  
- spring forces with rest length and stiffness  
- distance constraints acting as rigid links  
- an analytical Jacobian for Newton iterations  
- simulation of multiple example structures using the Newmark integrator  

These additions enable the modelling of flexible and rigid multi-body systems within the same environment.

---

## 2. System Implementation

### 2.1 Core Components

The implementation centres around the class

`MassSpringSystem<D>`, which stores

- fixed nodes  
- masses  
- springs  
- distance constraints  
- gravity  

This class provides the interface for building mechanical structures.

The system dynamics are defined in

`MSS_Function<D>`, which computes

- total forces  
- accelerations  
- the analytical Jacobian needed for the Newton iteration inside the ODE solver  

The system is solved using the **Newmark method**, which is suitable for stiff mechanical systems.

### 2.2 Distance Constraints

Distance constraints enforce a fixed length between two points.  
The interface for adding a constraint is of the form

- `mss.addConstraint({L, {connectorA, connectorB}});`

These constraints act similarly to rigid bars.  
They are used in both the **crane structure** and the **spinning top** to maintain geometric rigidity during motion.

### 2.3 Exact Analytical Derivative (Jacobian)

The original version relied on **numerical differentiation**, which is slow and unstable for stiff systems.

This was replaced by a manually derived **analytical Jacobian** for spring forces.

**Advantages:**

- faster and more reliable Newton iterations  
- improved stability for large stiffness values  
- essential for simulations involving rigid constraints  

---

## 3. Simulation Experiments

The following structures were constructed and simulated as required by the assignment:

1. Mass–spring chain (extension of the double pendulum)  
2. Crane-like triangular structure with rigid constraints  
3. Spinning top (“Kreisel”) modelled with rigid triangular constraints  

Each simulation prints the time evolution of the system using the Newmark solver.

### 3.1 Example A — Mass–Spring Chain

#### Structure

A chain of four masses connected in series, with the first point fixed at the origin:

- Fix at (0, 0)  
- Masses at (1, 0), (2, 0), (3, 0), (4, 0)  
- Springs of rest length 1 and stiffness 20 between each pair  

#### Code Summary

- `auto f0 = mss.addFix({ {0, 0} });`  
- `auto m1 = mss.addMass({1, {1, 0}});`  
- `auto m2 = mss.addMass({1, {2, 0}});`  
- `auto m3 = mss.addMass({1, {3, 0}});`  
- `auto m4 = mss.addMass({1, {4, 0}});`  

- `mss.addSpring({1, 20, {f0, m1}});`  
- `mss.addSpring({1, 20, {m1, m2}});`  
- `mss.addSpring({1, 20, {m2, m3}});`  
- `mss.addSpring({1, 20, {m3, m4}});`  

#### Observed Output (first lines)

- `t = 0.01, x = 1, -0.0004905, 2, -0.0004905`  
- `t = 0.02, x = 1, -0.001962, 2, -0.001962`  
- `t = 0.03, x = 1, -0.0044145, 2, -0.0044145`  

#### Behaviour

Under gravity, the masses sag downward, and the springs oscillate.  
The resulting motion is smooth and physically plausible, confirming correct force computation.

---

### 3.2 Example B — Crane Structure (Rigid Triangle)

#### Structure

A triangular rigid body is attached to a fixed support by three distance constraints:

- Fix at (0, 0)  
- Masses at (1, 0), (0.5, -1), (1.5, -1)  
- Distance constraints enforce the triangle’s shape  

#### Code Summary

- `auto f0 = mss.addFix({ {0, 0} });`  

- `auto m1 = mss.addMass({1, {1, 0}});`  
- `auto m2 = mss.addMass({1, {0.5, -1}});`  
- `auto m3 = mss.addMass({1, {1.5, -1}});`  

- `mss.addConstraint({1.0, {m1, m2}});`  
- `mss.addConstraint({1.0, {m2, m3}});`  
- `mss.addConstraint({1.0, {m3, m1}});`  

#### Observed Output (first lines)

- `t = 0.01, x = 1, -0.0191634, 0.504281, -0.991154`  
- `t = 0.02, x = 1, -0.0681725, 0.513677, -0.968857`  
- `t = 0.03, x = 1, -0.125967, 0.519808, -0.943638`  

#### Behaviour

The triangle behaves almost like a **rigid crane arm**, swinging as a single unit under gravity.  
Over long simulation times, the constraint forces become large, eventually causing Newton’s method to fail—an expected outcome for stiff, penalty-based constraints.

---

### 3.3 Example C — Spinning Top (Kreisel)

#### Structure

Three masses forming an equilateral triangle are connected by distance constraints, creating a rigid spinning body.  
Initial velocities are chosen so that the triangle rotates.

#### Code Summary

- `auto m1 = mss.addMass({1, {0, 0}});`  
- `auto m2 = mss.addMass({1, {1, 0}});`  
- `auto m3 = mss.addMass({1, {0.5, 0.866}});`  

- `double L = 1.0;`  
- `mss.addConstraint({L, {m1, m2}});`  
- `mss.addConstraint({L, {m2, m3}});`  
- `mss.addConstraint({L, {m3, m1}});`  

- Initial angular velocity:  
  - `mss.masses()[0].vel = {0, 1};`  
  - `mss.masses()[1].vel = {-1, 0};`  
  - `mss.masses()[2].vel = {1, -1};`  

#### Observed Output (first lines)

- `t = 0.01, x = -0.000692, 0.009063, 0.990825, -0.001214`  
- `t = 0.02, x = -0.003741, 0.015637, 0.984482, -0.005984`  
- `t = 0.03, x = -0.010072, 0.019112, 0.982212, -0.015735`  

#### Behaviour

The triangular body rotates around its centre due to conservation of angular momentum.  
The constraint forces keep the shape rigid, producing behaviour similar to a simple physical spinning top.

---

## 4. Conclusion

All required tasks for **Exercise 20** were completed successfully:

- Mass–spring system implemented and tested  
- Distance constraints added  
- Exact analytical Jacobian implemented  
- Three mechanical systems constructed:  
  - mass–spring chain  
  - crane-like rigid body  
  - spinning top (Kreisel)  
- Simulations executed and analysed  
- Python bindings compiled and verified  

The project results in a working multi-body simulation environment capable of modelling flexible and rigid structures with constraint forces.
