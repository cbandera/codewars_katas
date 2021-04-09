// https://www.codewars.com/kata/54eb33e5bc1a25440d000891
#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

namespace Decomp {

namespace internal {

long long sum_of_squares(const std::vector<long long> &vec) {
  return std::inner_product(vec.begin(), vec.end(), vec.begin(), 0LL);
}

long long is_sum_reachable(long long n, const long long sum) {
  long long result{0};
  while (n > 0 && result < sum) {
    result += n * n;
    --n;
  }
  return result >= sum;
}

long long next_best_guess(const long long n, const long long sum) {
  return std::min(static_cast<long long>(std::sqrt(sum)), n - 1);
}
} // namespace internal

std::vector<long long> decompose(const long long n, const long long sum) {
  using namespace internal;

  // Exit early when done or if goal is not reachable anymore
  if (sum == 0 || n == 0 || !is_sum_reachable(n, sum)) {
    return {};
  }

  // Recurse and form solution
  const auto squared = n * n;
  const auto next_guess = next_best_guess(n, sum - squared);
  auto result = decompose(next_guess, sum - squared);
  result.push_back(n);

  // Test solution and return up or try again without n
  if (sum_of_squares(result) == sum) {
    return result;
  } else {
    const auto next_guess = next_best_guess(n, sum);
    return decompose(next_guess, sum);
  }
}

std::vector<long long> decompose(const long long n) {
  return decompose(n - 1, n * n);
}

class Decomp {
public:
  static std::vector<long long> decompose(long long n) {
    auto list = std::vector<long long>();
    if (Divide(list, n * n, n))
      return list;
    return std::vector<long long>() = {};
  }

private:
  static bool Divide(std::vector<long long> &numbers, double remain,
                     long long last) {
    if (remain <= 0)
      return remain == 0;
    for (long long i = last - 1; i > 0; i--) {
      if (Divide(numbers, remain - (i * i), i)) {
        numbers.push_back(i);
        return true;
      }
    }
    return false;
  }
};
}; // namespace Decomp
