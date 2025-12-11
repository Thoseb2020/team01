#include "nonlinfunc.hpp"

using namespace ASC_ode;

// ========================================================
// Mass–Spring System:  y' = f(y)
// y = [x, v]
// x' = v
// v' = -(k/m) * x
// ========================================================
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

