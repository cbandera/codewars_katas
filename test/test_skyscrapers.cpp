#include "catch2/catch.hpp"
#include "skyscrapers.hpp"
#include <cstring>

static int clues[][16] = {
    {2, 2, 1, 3, 2, 2, 3, 1, 1, 2, 2, 3, 3, 2, 1, 3},
    {0, 0, 1, 2, 0, 2, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0},
};

int outcomes[][4][4] = {
    {{1, 3, 4, 2}, {4, 2, 1, 3}, {3, 4, 2, 1}, {2, 1, 3, 4}},
    {{2, 1, 4, 3}, {3, 4, 1, 2}, {4, 2, 3, 1}, {1, 3, 2, 4}},
};

int equal(int **puzzle, int expected[4][4]) {
  if (!puzzle || !expected)
    return 0;
  for (int i = 0; i < 4; ++i)
    if (memcmp(puzzle[i], expected[i], 4 * sizeof(int)))
      return 0;
  return 1;
}

TEST_CASE("4 By 4 Skyscrapers", "[solvePuzzle]") {
  REQUIRE(equal(SolvePuzzle(clues[0]), outcomes[0]));
  REQUIRE(equal(SolvePuzzle(clues[1]), outcomes[1]));
}
