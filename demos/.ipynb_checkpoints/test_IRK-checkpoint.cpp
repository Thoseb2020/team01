#include <iostream>
#include <cmath>
#include "implicitRK.hpp"
#include "nonlinfunc.hpp"
#include "rccircuit.hpp"
using namespace nanoblas;
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

    void evaluate(VectorView<double> x, VectorView<double> f) const override
    {
        f(0) = x(1);
        f(1) = -stiffness / mass * x(0);
    }

    void evaluateDeriv(VectorView<double> x, MatrixView<double> df) const override
    {
        df = 0.0;
        df(0, 1) = 1.0;
        df(1, 0) = -stiffness / mass;
    }
};



int main(int argc, char* argv[]){

    double tend_relative = atof(argv[1]);
    int steps = atoi(argv[2]);
    std::string ode = argv[3];

    // ___Calculate a, b and c coefficients___
    Vector<> w2 {0,0};
    Vector<> w3 {0,0,0};
    
    Vector<> c_gl2 {0,0};
    GaussLegendre(c_gl2, w2);
    auto [a_gl2, b_gl2] = ComputeABfromC(c_gl2);
    
    Vector<> c_gl3 {0,0,0};
    GaussLegendre(c_gl3, w3);
    auto [a_gl3, b_gl3] = ComputeABfromC(c_gl3);
    
    Vector<> c_rad2 {0,0};
    GaussLegendre(c_rad2, w2);
    auto [a_rad2, b_rad2] = ComputeABfromC(c_rad2);
    
    Vector<> c_rad3 {0,0,0};
    GaussLegendre(c_rad3, w3);
    auto [a_rad3, b_rad3] = ComputeABfromC(c_rad3);

    //___Solving-ODE___

    auto sys = std::make_shared<MassSpring>(1.0, 1.0);
    auto MS = std::make_shared<MassSpring>(1.0, 1.0);
    auto RC = std::make_shared<RCCircuit>(100.0, 1e-6);
    if (ode == "MS")
        auto sys = MS;
    else if (ode == "RC")
        auto sys = RC;
    else{
        std::cout << "invalid ode, try MS or RC";
        return 1;
    }

    Vector<> yg2 = {1.0, 0.0};
    Vector<> yg3 = {1.0, 0.0};
    Vector<> yr2 = {1.0, 0.0};
    Vector<> yr3 = {1.0, 0.0};
    double tau = M_PI * tend_relative / steps;
    double t = 0.0;
    
    std::unique_ptr<TimeStepper> G2;
    std::unique_ptr<TimeStepper> G3;
    std::unique_ptr<TimeStepper> rad2;
    std::unique_ptr<TimeStepper> rad3;

    G2 = std::make_unique<ImplicitRungeKutta>(sys, a_gl2, b_gl2, c_gl2);
    G3 = std::make_unique<ImplicitRungeKutta>(sys, a_gl3, b_gl3, c_gl3);
    rad2 = std::make_unique<ImplicitRungeKutta>(sys, a_rad2, b_rad2, c_rad2);
    rad3 = std::make_unique<ImplicitRungeKutta>(sys, a_rad3, b_rad3, c_rad3);

    
    std::cout << "time, " <<  "Gauss2x, " << "Gauss2y, " << "Gauss3x, " << "Gauss3y, " << "Rad2x, " << "Rad2y, " << "Rad3x, " << "Rad3y, " << "\n";
    for(int i; i <= steps; i++){
        std::cout << t << ", " << yg2(0) << ", " << yg2(1) << ", " << yg3(0) << ", " << yg3(1) << ", " << yr2(0) << ", " << yr2(1) << ", " << yr3(0) << ", " << yr3(1) << "\n" ; 
        
        G2 -> DoStep(tau,yg2);
        G3 -> DoStep(tau,yg3);
        rad2 -> DoStep(tau,yr2);
        rad3 -> DoStep(tau,yr3); 
        t = t + tau;
        
    }
            
    return 0;
        
}  
