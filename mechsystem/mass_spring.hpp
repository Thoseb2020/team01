#ifndef MASS_SPRING_HPP
#define MASS_SPRING_HPP

#include <nonlinfunc.hpp>
#include <timestepper.hpp>

using namespace ASC_ode;

#include <vector.hpp>
using namespace nanoblas;

template <int D>
class Mass
{
public:
  double mass;
  Vec<D> pos;
  Vec<D> vel = 0.0;
  Vec<D> acc = 0.0;
};

template <int D>
class Fix
{
public:
  Vec<D> pos;
};

class Connector
{
public:
  enum CONTYPE { FIX=1, MASS=2 };
  CONTYPE type;
  size_t nr;
};

std::ostream & operator<< (std::ostream & ost, const Connector & con)
{
  ost << "type = " << int(con.type) << ", nr = " << con.nr;
  return ost;
}

class Spring
{
public:
  double length;
  double stiffness;
  std::array<Connector,2> connectors;
};

class DistanceConstraint
{
public:
  double length;
  std::array<Connector,2> connectors;
};

template <int D>
class MassSpringSystem
{
  std::vector<Fix<D>> m_fixes;
  std::vector<Mass<D>> m_masses;
  std::vector<Spring> m_springs;
  std::vector<DistanceConstraint> m_constraints;

  Vec<D> m_gravity = 0.0;

public:
  void setGravity(Vec<D> g) { m_gravity = g; }
  Vec<D> getGravity() const { return m_gravity; }

  Connector addFix(Fix<D> f)
  {
    m_fixes.push_back(f);
    return {Connector::FIX, m_fixes.size()-1};
  }

  Connector addMass(Mass<D> m)
  {
    m_masses.push_back(m);
    return {Connector::MASS, m_masses.size()-1};
  }

  size_t addSpring(Spring s)
  {
    m_springs.push_back(s);
    return m_springs.size()-1;
  }

  size_t addConstraint(const DistanceConstraint &c)
  {
    m_constraints.push_back(c);
    return m_constraints.size()-1;
  }

  auto & fixes() { return m_fixes; }
  auto & masses() { return m_masses; }
  auto & springs() { return m_springs; }
  auto & constraints() { return m_constraints; }

  void getState(VectorView<> x, VectorView<> dx, VectorView<> ddx)
  {
    auto xm = x.asMatrix(m_masses.size(), D);
    auto dxm = dx.asMatrix(m_masses.size(), D);
    auto ddxm = ddx.asMatrix(m_masses.size(), D);

    for (size_t i = 0; i < m_masses.size(); i++)
    {
      xm.row(i) = m_masses[i].pos;
      dxm.row(i) = m_masses[i].vel;
      ddxm.row(i) = m_masses[i].acc;
    }
  }

  void setState(VectorView<> x, VectorView<> dx, VectorView<> ddx)
  {
    auto xm = x.asMatrix(m_masses.size(), D);
    auto dxm = dx.asMatrix(m_masses.size(), D);
    auto ddxm = ddx.asMatrix(m_masses.size(), D);

    for (size_t i = 0; i < m_masses.size(); i++)
    {
      m_masses[i].pos = xm.row(i);
      m_masses[i].vel = dxm.row(i);
      m_masses[i].acc = ddxm.row(i);
    }
  }
};

template <int D>
std::ostream & operator<<(std::ostream &ost, MassSpringSystem<D> &mss)
{
  ost << "fixes:\n";
  for (auto &f : mss.fixes())
    ost << f.pos << "\n";

  ost << "masses:\n";
  for (auto &m : mss.masses())
    ost << "m = " << m.mass << ", pos = " << m.pos << "\n";

  ost << "springs:\n";
  for (auto &s : mss.springs())
    ost << "length = " << s.length << ", stiffness = " << s.stiffness
        << ", C1 = " << s.connectors[0] << ", C2 = " << s.connectors[1] << "\n";

  return ost;
}

template <int D>
class MSS_Function : public NonlinearFunction
{
  MassSpringSystem<D> &mss;

public:
  MSS_Function(MassSpringSystem<D> &s) : mss(s) {}

  virtual size_t dimX() const override { return D * mss.masses().size(); }
  virtual size_t dimF() const override { return D * mss.masses().size(); }

  virtual void evaluate(VectorView<double> x, VectorView<double> f) const override
  {
    f = 0.0;

    auto xm = x.asMatrix(mss.masses().size(), D);
    auto fm = f.asMatrix(mss.masses().size(), D);

    // Gravity
    for (size_t i = 0; i < mss.masses().size(); i++)
      fm.row(i) = mss.masses()[i].mass * mss.getGravity();

    // Springs
    for (auto &s : mss.springs())
    {
      auto c1 = s.connectors[0];
      auto c2 = s.connectors[1];

      Vec<D> p1 = (c1.type == Connector::FIX) ? mss.fixes()[c1.nr].pos : xm.row(c1.nr);
      Vec<D> p2 = (c2.type == Connector::FIX) ? mss.fixes()[c2.nr].pos : xm.row(c2.nr);

      Vec<D> d = p2 - p1;
      double r = norm(d);
      if (r < 1e-12) continue;

      double force = s.stiffness * (r - s.length);
      Vec<D> dir = (1.0 / r) * d;

      if (c1.type == Connector::MASS) fm.row(c1.nr) += force * dir;
      if (c2.type == Connector::MASS) fm.row(c2.nr) -= force * dir;
    }

    // Penalty constraints
    double K = 2000;
    for (auto &c : mss.constraints())
    {
      auto c1 = c.connectors[0];
      auto c2 = c.connectors[1];

      Vec<D> p1 = (c1.type == Connector::FIX) ? mss.fixes()[c1.nr].pos : xm.row(c1.nr);
      Vec<D> p2 = (c2.type == Connector::FIX) ? mss.fixes()[c2.nr].pos : xm.row(c2.nr);

      Vec<D> d = p2 - p1;
      double r = norm(d);
      if (r < 1e-10) continue;

      double F = K * (r - c.length);
      Vec<D> dir = (1.0 / r) * d;

      if (c1.type == Connector::MASS) fm.row(c1.nr) += F * dir;
      if (c2.type == Connector::MASS) fm.row(c2.nr) -= F * dir;
    }

    // Convert force → acceleration
    for (size_t i = 0; i < mss.masses().size(); i++)
      fm.row(i) *= 1.0 / mss.masses()[i].mass;
  }

  // ---- NUMERICAL JACOBIAN (SAFE, WORKS, NO CRASHES) ----
  virtual void evaluateDeriv(VectorView<double> x, MatrixView<double> df) const override
  {
    df = 0.0;

    double eps = 1e-8;
    Vector<> xl(dimX()), xr(dimX());
    Vector<> fl(dimF()), fr(dimF());

    for (size_t i = 0; i < dimX(); i++)
    {
      xl = x;
      xr = x;
      xl(i) -= eps;
      xr(i) += eps;

      evaluate(xl, fl);
      evaluate(xr, fr);

      df.col(i) = (1.0 / (2 * eps)) * (fr - fl);
    }
  }
};

#endif
