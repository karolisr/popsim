#ifndef POPSIMCPP_POP_H
#define POPSIMCPP_POP_H

#include <QtCharts>

#include "sim.h"

// Pop ------------------------------------------------------------------------
class Pop {
public:
  explicit Pop(double p, double u = 0, double v = 0, double wAA = 1,
               double wAa = 1, double waa = 1);
  virtual ~Pop();
  virtual void update_parameters(double u, double v, double wAA, double wAa,
                                 double waa);
  virtual void next_gen();
  virtual QLineSeries *history();

protected:
  double _p;
  double _u;
  double _v;
  double _wAA;
  double _wAa;
  double _waa;
  double _ngen;
  QLineSeries *_history;
};

// InfinitePop ----------------------------------------------------------------
class InfinitePop : public Pop {
public:
  explicit InfinitePop(double p, double u = 0, double v = 0, double wAA = 1,
                       double wAa = 1, double waa = 1);
  ~InfinitePop() override;
  void update_parameters(double u, double v, double wAA, double wAa,
                         double waa) override;
  void next_gen() override;
};

// FinitePop ------------------------------------------------------------------
class FinitePop : public Pop {
public:
  FinitePop(std::mt19937 *rgenptr, unsigned int size, double p, double u = 0,
            double v = 0, double wAA = 1, double wAa = 1, double waa = 1);
  ~FinitePop() override;
  void update_parameters(double u, double v, double wAA, double wAa,
                         double waa) override;
  void update_parameters(unsigned int size, double u, double v, double wAA,
                         double wAa, double waa);
  void next_gen() override;

protected:
  std::mt19937 *_rgenptr;
  unsigned int _size;
};

#endif // POPSIMCPP_POP_H
