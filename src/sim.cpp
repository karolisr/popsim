#include "sim.h"

double next_p(double p, double u, double v, double wAA, double wAa,
              double waa) {
  double pu = p * u;
  double pv = (1 - p) * v;
  double puv = p - pu + pv;
  double puv_sq = pow(puv, 2.0);
  double one_minus_puv = 1 - puv;
  double wbar = puv_sq * wAA + 2 * puv * one_minus_puv * wAa +
                pow(one_minus_puv, 2.0) * waa;
  double puvw = (puv_sq * wAA + puv * one_minus_puv * wAa) / wbar;
  return puvw;
}

double next_p_finite(std::mt19937 *rgen, unsigned int size, double p, double u,
                     double v, double wAA, double wAa, double waa) {
  double puvw = next_p(p, u, v, wAA, wAa, waa);
  unsigned int allele_count = 2 * size;
  std::binomial_distribution<unsigned int> rbinom(allele_count, puvw);
  return (double)rbinom(*rgen) / (double)allele_count;
}
