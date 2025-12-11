#include "mass_spring.hpp"
#include "Newmark.hpp"

int main()
{
  MassSpringSystem<2> mss;
  mss.setGravity( {0,-9.81} );


  auto m1 = mss.addMass({1, {0,0}});
  auto m2 = mss.addMass({1, {1,0}});
  auto m3 = mss.addMass({1, {0.5,0.866}});  // equilateral triangle

  double L = 1.0;
  mss.addConstraint({L, {m1, m2}});
  mss.addConstraint({L, {m2, m3}});
  mss.addConstraint({L, {m3, m1}});

  // give spinning initial velocity
  mss.masses()[0].vel = {0, 1};
  mss.masses()[1].vel = {-1, 0};
  mss.masses()[2].vel = {1, -1};



  
  std::cout << "mss: " << std::endl << mss << std::endl;


  double tend = 10;
  double steps = 1000;

  Vector<> x(2*mss.masses().size());
  Vector<> dx(2*mss.masses().size());
  Vector<> ddx(2*mss.masses().size());

  auto mss_func = std::make_shared<MSS_Function<2>> (mss);
  auto mass = std::make_shared<IdentityFunction> (x.size());

  mss.getState (x, dx, ddx);
  
  SolveODE_Newmark(tend, steps, x, dx,  mss_func, mass,
                   [](double t, VectorView<double> x) { std::cout << "t = " << t
                                                             << ", x = " << Vec<4>(x) << std::endl; });
}
