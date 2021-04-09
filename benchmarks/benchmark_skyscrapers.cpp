#include "skyscrapers.hpp"
#include <benchmark/benchmark.h>

#include <algorithm>
#include <array>
#include <numeric>
#include <set>
#include <vector>
namespace Other {
using one_row = std::vector<int>;
std::array<std::array<std::vector<one_row>, 5>, 5> pre;
int *map[4];

int calc(one_row const &v) {
  auto ret = 0;
  auto tallest = 0;
  std::for_each(v.begin(), v.end(), [&](int x) {
    if (x > tallest) {
      tallest = x;
      ret++;
    }
  });
  return ret;
}

bool check(int *clues) {
  for (int i = 0; i < 4; i++) {
    one_row v;
    for (int j = 0; j < 4; j++)
      v.push_back(map[i][j]);

    std::set<int> check_dul(v.begin(), v.end());
    if (check_dul.size() != 4)
      return false;

    auto left = calc(v);
    auto cleft = clues[15 - i];
    if (cleft && left != cleft)
      return false;

    std::reverse(v.begin(), v.end());
    auto right = calc(v);
    auto cright = clues[4 + i];
    if (cright && right != cright)
      return false;
  }
  return true;
}

bool dfs(int dep, int *clues) {
  if (dep == 4)
    return check(clues);
  auto left = clues[dep];
  auto right = clues[11 - dep];
  for (auto const &v : pre[left][right]) {
    for (int i = 0; i < 4; i++)
      map[i][dep] = v[i];
    if (dfs(dep + 1, clues))
      return true;
  }
  return false;
}

int **SolvePuzzle(int *clues) {
  for (int i = 0; i < 4; i++)
    map[i] = new int[4];

  for (auto &i : pre)
    for (auto &j : i)
      j = std::vector<one_row>();

  one_row p(4);
  std::iota(p.begin(), p.end(), 1);

  do {
    auto left = calc(p);
    std::reverse(p.begin(), p.end());
    auto right = calc(p);
    std::reverse(p.begin(), p.end());

    pre[left][right].push_back(p);
    pre[left][0].push_back(p);
    pre[0][right].push_back(p);
    pre[0][0].push_back(p);
  } while (std::next_permutation(p.begin(), p.end()));

  dfs(0, clues);
  return map;
}
} // namespace Other
static int clues[][16] = {
    {2, 2, 1, 3, 2, 2, 3, 1, 1, 2, 2, 3, 3, 2, 1, 3},
    {0, 0, 1, 2, 0, 2, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0},
};

static void BM_SkyscraperOwn(benchmark::State &state) {
  for (auto _ : state) {
    SolvePuzzle(clues[state.range(0)]);
  }
}

static void BM_SkyscraperOther(benchmark::State &state) {
  for (auto _ : state) {
    Other::SolvePuzzle(clues[state.range(0)]);
  }
}

BENCHMARK(BM_SkyscraperOwn)->Range(0, 1)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SkyscraperOther)->Range(0, 1)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
