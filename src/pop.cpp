#include "pop.h"

// Pop ------------------------------------------------------------------------
Pop::Pop(double p, double u, double v, double wAA, double wAa, double waa) {
  _p = p;
  _u = u;
  _v = v;
  _wAA = wAA;
  _wAa = wAa;
  _waa = waa;
  _ngen = 0;
  // Not the best design choice using QLineSeries.
  // QChart takes ownership of QLineSeries, so should
  // not delete _history in the destructor.
  _history = new QLineSeries();
  _history->append(_ngen, _p);
}

Pop::~Pop() = default;

void Pop::update_parameters(double u, double v, double wAA, double wAa,
                            double waa) {
  _u = u;
  _v = v;
  _wAA = wAA;
  _wAa = wAa;
  _waa = waa;
}

void Pop::next_gen() {
  _ngen = _ngen + 1;
  _history->append(_ngen, _p);
}

QLineSeries *Pop::history() { return _history; }

// InfinitePop ----------------------------------------------------------------
InfinitePop::InfinitePop(double p, double u, double v, double wAA, double wAa,
                         double waa)
    : Pop(p, u, v, wAA, wAa, waa) {}

InfinitePop::~InfinitePop() = default;

void InfinitePop::update_parameters(double u, double v, double wAA, double wAa,
                                    double waa) {
  Pop::update_parameters(u, v, wAA, wAa, waa);
}

void InfinitePop::next_gen() {
  _p = next_p(_p, _u, _v, _wAA, _wAa, _waa);
  Pop::next_gen();
}

// FinitePop ------------------------------------------------------------------
FinitePop::FinitePop(std::mt19937 *rgenptr, unsigned int size, double p,
                     double u, double v, double wAA, double wAa, double waa)
    : Pop(p, u, v, wAA, wAa, waa), _rgenptr(rgenptr), _size(size) {}

FinitePop::~FinitePop() = default;

void FinitePop::update_parameters(double u, double v, double wAA, double wAa,
                                  double waa) {
  Pop::update_parameters(u, v, wAA, wAa, waa);
}

void FinitePop::update_parameters(unsigned int size, double u, double v,
                                  double wAA, double wAa, double waa) {
  _size = size;
  Pop::update_parameters(u, v, wAA, wAa, waa);
}

void FinitePop::next_gen() {
  _p = next_p_finite(_rgenptr, _size, _p, _u, _v, _wAA, _wAa, _waa);
  Pop::next_gen();
}
