#include <iostream>
#include <fstream> 
<<<<<<< HEAD
#include <memory>
#include "nonlinfunc.hpp"
#include "timestepper.hpp"
=======

#include <nonlinfunc.hpp>
#include <timestepper.hpp>
#include <implicitRK.hpp>
>>>>>>> upstream/RungeKutta

using namespace ASC_ode;


class MassSpring : public NonlinearFunction
{
private:
  double mass;
  double stiffness;

public:
  MassSpring(double m, double k) : mass(m), stiffness(k) {}

  size_t dimX() const override { return 2; }
  size_t dimF() const override { return 2; }
  
  void evaluate (VectorView<double> x, VectorView<double> f) const override
  {
    f(0) = x(1);
    f(1) = -stiffness/mass*x(0);
  }
  
  void evaluateDeriv (VectorView<double> x, MatrixView<double> df) const override
  {
    df = 0.0;
    df(0,1) = 1;
    df(1,0) = -stiffness/mass;
  }
};


int main(int argc, char* argv[])
{
  double tend_relative = atof(argv[1]);
  double steps = atoi(argv[2]);
  std::string algorithm = argv[3];

  double tend = tend_relative*M_PI; //standard: 4*M_PI
  //int steps = 10000;  //standard: 100
  double tau = tend/steps;

  Vector<> y = { 1, 0 };  // initializer list
  auto rhs = std::make_shared<MassSpring>(1.0, 1.0);
<<<<<<< HEAD
  
  //Choose method:
  std::unique_ptr<TimeStepper> stepper;
  if(algorithm=="explicit"){
    stepper = std::make_unique<ExplicitEuler>(rhs);
  }else if(algorithm=="improved")
  {
    stepper = std::make_unique<ImprovedEuler>(rhs);
  }else if(algorithm=="implicit")
  {
    stepper = std::make_unique<ImplicitEuler>(rhs);
  }else if(algorithm=="CN")
  {
    stepper = std::make_unique<CrankNicolson>(rhs);
  }else
  {
    std::cout << "Use explicit or improved method, for example: ./runmassspring.sh 4 100 explicit";
  }
  
  //
=======



/*
  Vector<> Radau(3), RadauWeight(3);
  GaussRadau (Radau, RadauWeight);
  // not sure about weights, comput them via ComputeABfromC
  cout << "Radau = " << Radau << ", weight = " << RadauWeight <<  endl;
        Vector<> Gauss2c(2), Gauss3c(3);
*/
 

  // ExplicitEuler stepper(rhs);
>>>>>>> upstream/RungeKutta
  // ImplicitEuler stepper(rhs);

  // RungeKutta stepper(rhs, Gauss2a, Gauss2b, Gauss2c);

  // Gauss3c .. points tabulated, compute a,b:
  auto [Gauss3a,Gauss3b] = ComputeABfromC (Gauss3c);
  ImplicitRungeKutta stepper(rhs, Gauss3a, Gauss3b, Gauss3c);


  /*
  // arbitrary order Gauss-Legendre
  int stages = 5;
  Vector<> c(stages), b1(stages);
  GaussLegendre(c, b1);

  auto [a, b] = ComputeABfromC(c);
  ImplicitRungeKutta stepper(rhs, a, b, c);
  */

  /* 
  // arbitrary order Radau
  int stages = 5;
  Vector<> c(stages), b1(stages);
  GaussRadau(c, b1);

  auto [a, b] = ComputeABfromC(c);
  ImplicitRungeKutta stepper(rhs, a, b, c);
  */


  std::ofstream outfile ("output_test_ode.txt");
  std::cout << 0.0 << "  " << y(0) << " " << y(1) << std::endl;
  outfile << 0.0 << "  " << y(0) << " " << y(1) << std::endl;

  for (int i = 0; i < steps; i++)
  {
     stepper->DoStep(tau, y);

     std::cout << (i+1) * tau << "  " << y(0) << " " << y(1) << std::endl;
     outfile << (i+1) * tau << "  " << y(0) << " " << y(1) << std::endl;
  }
}
