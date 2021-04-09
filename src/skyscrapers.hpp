// https://www.codewars.com/kata/5671d975d81d6c1c87000022
#include <algorithm>
#include <array>
#include <cstring>
#include <vector>

using Row = std::array<int, 4>;
using Square = std::array<Row, 4>;
using Clues = std::array<int, 16>;

std::vector<Row> generate_permutations() {
  Row prototype{1, 2, 3, 4};
  std::vector<Row> permutations{prototype};
  permutations.reserve(4 * 3 * 2 * 1);
  while (std::next_permutation(prototype.begin(), prototype.end())) {
    permutations.push_back(prototype);
  }
  return permutations;
}
static const auto g_all_permutations = generate_permutations();

template <typename Iterator> int calc_clue(Iterator begin, Iterator end) {
  int maximum{0};
  int count = std::count_if(begin, end, [&maximum](const int a) {
    bool new_max = a > maximum;
    maximum = std::max(a, maximum);
    return new_max;
  });
  return count;
}
Row get_column(const Square &square, int col) {
  return Row{square[0][col], square[1][col], square[2][col], square[3][col]};
}

bool check_row(const Row &row, const Clues &clues, size_t clueIdxLeft,
               size_t clueIdxRight) {
  auto left = calc_clue(row.begin(), row.end());
  auto cleft = clues[clueIdxLeft];
  if (cleft && left != cleft)
    return false;

  auto right = calc_clue(row.rbegin(), row.rend());
  auto cright = clues[clueIdxRight];
  if (cright && right != cright)
    return false;
  return true;
}

bool check_solution(const Square &square, const Clues &clues) {
  for (size_t rowIdx = 0; rowIdx < square.size(); ++rowIdx) {
    const auto &row = square[rowIdx];
    size_t clueIdxLeft = square.size() * 4 - 1 - rowIdx;
    size_t clueIdxRight = square.size() * 1 + rowIdx;
    if (!check_row(row, clues, clueIdxLeft, clueIdxRight))
      return false;
  }
  for (size_t colIdx = 0; colIdx < square.size(); ++colIdx) {
    const auto &col = get_column(square, colIdx);
    size_t clueIdxLeft = 0 + colIdx;
    size_t clueIdxRight = square.size() * 3 - 1 - colIdx;
    if (!check_row(col, clues, clueIdxLeft, clueIdxRight))
      return false;
  }
  return true;
}

int **new_to_old(const Square &square) {
  int **x = new int *[square.size()];
  for (size_t row = 0; row < square.size(); ++row) {
    x[row] = new int[square.size()];
    std::memcpy(x[row], square[row].data(), square[row].size() * sizeof(int));
  }
  return x;
}

Clues old_to_new(int *raw_clues) {
  Clues clues{};
  std::memcpy(clues.data(), raw_clues, clues.size() * sizeof(int));
  return clues;
}

bool is_valid_candidate(const Square &square, const Row &candidate,
                        const size_t level) {
  for (size_t row = 0; row < level; ++row) {
    for (size_t col = 0; col < square.size(); ++col) {
      if (square[row][col] == candidate[col]) {
        return false;
      }
    }
  }
  return true;
}

bool find_solution(Square &square, const Clues &clues, const size_t level = 0) {
  if (level == 4) {
    return check_solution(square, clues);
  }

  for (const auto &candidate : g_all_permutations) {
    if (!is_valid_candidate(square, candidate, level)) {
      continue;
    }
    square[level] = candidate;
    if (find_solution(square, clues, level + 1)) {
      return true;
    }
  }
  return false;
}

int **SolvePuzzle(int *raw_clues) {
  Clues clues = old_to_new(raw_clues);
  Square square{};
  std::ignore = find_solution(square, clues);
  return new_to_old(square);
}
