#include "battleships.hpp"
#include "catch2/catch.hpp"
#include <iostream>
#include <vector>

TEST_CASE("Valid game field") {
  REQUIRE(validate_battlefield(Field{{1, 0, 0, 0, 0, 1, 1, 0, 0, 0},
                                     {1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
                                     {1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
                                     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                     {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                                     {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                                     {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                                     {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                                     {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}) == true);
}
TEST_CASE("Missing ship") {
  REQUIRE(validate_battlefield(Field{{1, 0, 0, 0, 0, 1, 1, 0, 0, 0},
                                     {1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                                     {1, 0, 0, 0, 1, 1, 1, 0, 1, 0},
                                     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                     {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                                     {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                                     {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                                     {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                                     {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}) == false);
}
TEST_CASE("Touching ships") {
  REQUIRE(validate_battlefield(Field{{1, 0, 0, 0, 0, 1, 1, 0, 0, 0},
                                     {1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                                     {1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
                                     {1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                                     {0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
                                     {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                                     {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                     {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}) == false);
}

TEST_CASE("Touching ships 2") {
  REQUIRE(validate_battlefield(Field{{1, 0, 0, 0, 0, 1, 1, 0, 0, 0},
                                     {1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
                                     {1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
                                     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                     {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                                     {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                                     {0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
                                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                     {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}) == false);
}

TEST_CASE("Unknown ship") {
  REQUIRE(validate_battlefield(Field{{1, 0, 0, 0, 0, 1, 1, 0, 0, 0},
                                     {1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                                     {1, 0, 0, 0, 1, 1, 1, 0, 1, 0},
                                     {1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                                     {1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
                                     {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                                     {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                                     {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                                     {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}) == false);
}