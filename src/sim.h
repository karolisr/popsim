#ifndef POPSIMCPP_SIM_H
#define POPSIMCPP_SIM_H

#include <cmath>
#include <random>

double next_p(double p, double u = 0, double v = 0, double wAA = 1,
              double wAa = 1, double waa = 1);

double next_p_finite(std::mt19937 *rgen, unsigned int size, double p,
                     double u = 0, double v = 0, double wAA = 1, double wAa = 1,
                     double waa = 1);

#endif // POPSIMCPP_SIM_H
