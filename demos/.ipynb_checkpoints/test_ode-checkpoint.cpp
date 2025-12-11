
#include <iostream>
#include <fstream>
#include <memory>
#include "nonlinfunc.hpp"
#include "timestepper.hpp"
#include "implicitRK.hpp"
#include "massspring.cpp"

using namespace ASC_ode;
using namespace nanoblas;

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        std::cout << "Usage: ./test_ode T_relative steps method\n";
        std::cout << "Example: ./test_ode 4 100 RK2\n";
        return 1;
    }

    double tend_relative = atof(argv[1]);
    int steps = atoi(argv[2]);
    std::string algorithm = argv[3];

    double tend = tend_relative * M_PI;
    double tau = tend / steps;

    Vector<> y = {1.0, 0.0};
    auto rhs = std::make_shared<MassSpring>(1.0, 1.0);

    // ========================================================
    // Choose timestepper
    // ========================================================
    std::unique_ptr<TimeStepper> stepper;

    if (algorithm == "explicit")
        stepper = std::make_unique<ExplicitEuler>(rhs);
    else if (algorithm == "improved")
        stepper = std::make_unique<ImprovedEuler>(rhs);
    else if (algorithm == "implicit")
        stepper = std::make_unique<ImplicitEuler>(rhs);
    else if (algorithm == "CN")
        stepper = std::make_unique<CrankNicolson>(rhs);
    else if (algorithm == "RK2")
        stepper = std::make_unique<RungeKutta2>(rhs);
    else
    {
        std::cout << "Choose method: explicit / improved / implicit / CN / RK2\n";
        return 1;
    }

    // ========================================================
    // Write output file
    // ========================================================
    //std::ofstream outfile ("output_test_ode.txt");
    std::cout << 0.0 << "  " << y(0) << " " << y(1) << std::endl;
    //outfile << 0.0 << "  " << y(0) << " " << y(1) << std::endl;

  for (int i = 0; i < steps; i++)
  {
     stepper->doStep(tau, y);

     std::cout << (i+1) * tau << "  " << y(0) << " " << y(1) << std::endl;
     //outfile << (i+1) * tau << "  " << y(0) << " " << y(1) << std::endl;
  }
   /* 
  // Gauss3c .. points tabulated, compute a,b:
  auto [Gauss3a,Gauss3b] = computeABfromC (Gauss3c);
  ImplicitRungeKutta stepper(rhs, Gauss3a, Gauss3b, Gauss3c);

    for (int i = 0; i < steps; i++)
    {
        stepper.doStep(tau, y);

        double t = (i + 1) * tau;
        std::cout << t << "  " << y(0) << " " << y(1) << "\n";
        outfile << t << "  " << y(0) << " " << y(1) << "\n";
    }

  auto [a, b] = computeABfromC(c);
  ImplicitRungeKutta stepper(rhs, a, b, c);
  

   
  // arbitrary order Radau
  int stages = 5;
  Vector<> c(stages), b1(stages);
  GaussRadau(c, b1);

  auto [a, b] = computeABfromC(c);
  ImplicitRungeKutta stepper(rhs, a, b, c);*/
  
}
