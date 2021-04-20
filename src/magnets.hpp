#pragma once
// https://www.codewars.com/kata/56c04261c3fcf33f2d000534/
#include <cmath>

namespace Magnets {
double v(int k, int n) { return 1.0 / (k * std::pow(n + 1, 2 * k)); }
double u(int k, int N) {
  double result{};
  for (int n = 1; n <= N; ++n) {
    result += v(k, n);
  }
  return result;
}
double doubles(int maxk, int maxn) {
  double result{};
  for (int k = 1; k <= maxk; ++k) {
    result += u(k, maxn);
  }
  return result;
}
}; // namespace Magnets