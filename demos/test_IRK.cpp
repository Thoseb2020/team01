#include <iostream>
#include <memory>
#include <cmath>

#include "nonlinfunc.hpp"
#include "implicitRK.hpp"
#include "timestepper.hpp"

using namespace ASC_ode;

// ========================================================
// Mass–Spring system
// y = [x, v]
// x' = v
// v' = -x
// ========================================================
class MassSpring : public NonlinearFunction
{
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

private:
    double mass;
    double stiffness;
};


// ========================================================
// Factory for IRK methods defined in implicitRK.hpp
// ========================================================
std::unique_ptr<TimeStepper>
MakeIRK(const std::string& name, std::shared_ptr<NonlinearFunction> rhs)
{
    using namespace ASC_ode;

    if (name == "Gauss2")
        return std::make_unique<ImplicitRungeKutta>(rhs, Gauss2a, Gauss2b, Gauss2c);

    if (name == "Gauss3")
    {
        auto [A, B] = ComputeABfromC(Gauss3c);
        return std::make_unique<ImplicitRungeKutta>(rhs, A, B, Gauss3c);
    }

    if (name == "Radau")
    {
        Vector<> c(3), w(3);
        GaussRadau(c, w);
        auto [A, B] = ComputeABfromC(c);
        return std::make_unique<ImplicitRungeKutta>(rhs, A, B, c);
    }

    std::cerr << "Unknown method: " << name << "\n";
    std::cerr << "Available: Gauss2, Gauss3, Radau\n";
    std::exit(1);
}


// ========================================================
// Main program
// ========================================================
int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        std::cout << "Usage: ./test_IRK  T_relative  steps  method\n";
        std::cout << "Example: ./test_IRK 4 100 Gauss2\n";
        return 1;
    }

    double Trel = atof(argv[1]);
    int steps = atoi(argv[2]);
    std::string method = argv[3];

    double T = Trel * M_PI;
    double tau = T / steps;

    // Initial condition
    Vector<> y = {1.0, 0.0};

    auto rhs = std::make_shared<MassSpring>(1.0, 1.0);

    // Create IRK integrator
    auto stepper = MakeIRK(method, rhs);

    // Print initial state
    double t = 0.0;
    std::cout << t << " " << y(0) << " " << y(1) << "\n";

    // Time stepping
    for (int i = 0; i < steps; i++)
    {
        stepper->DoStep(tau, y);
        t += tau;

        std::cout << t << " " << y(0) << " " << y(1) << "\n";
    }

    return 0;
}
