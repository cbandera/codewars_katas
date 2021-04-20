#include "catch2/catch.hpp"
#include "magnets.hpp"
#include <iomanip>
#include <iostream>

bool assertFuzzyEquals(double act, double exp) {
  bool inrange = std::abs(act - exp) <= 1e-6;
  if (inrange == false) {
    std::cout << std::setprecision(6);
    std::cout << "At 1e-6: Expected should be " << exp << ", but got " << act
              << std::endl;
  }
  return inrange;
}

TEST_CASE("Magnet helpers") {
  REQUIRE(Magnets::v(1, 1) == 1.0 / (1.0 * 2.0 * 2.0));
  REQUIRE(Magnets::v(1, 2) == 1.0 / (1.0 * 3.0 * 3.0));
  REQUIRE(Magnets::v(2, 1) == 1.0 / (2.0 * 2.0 * 2.0 * 2.0 * 2.0));
  REQUIRE(Magnets::v(2, 2) == 1.0 / (2.0 * 3.0 * 3.0 * 3.0 * 3.0));

  REQUIRE(Magnets::u(1, 1) == Magnets::v(1, 1));
  REQUIRE(Magnets::u(1, 2) == Magnets::v(1, 1) + Magnets::v(1, 2));
  REQUIRE(Magnets::u(2, 1) == Magnets::v(2, 1));
  REQUIRE(Magnets::u(2, 2) == Magnets::v(2, 1) + Magnets::v(2, 2));
}

TEST_CASE("Magnet particules in boxes") {
  REQUIRE(assertFuzzyEquals(Magnets::doubles(1, 10), 0.5580321939764581) ==
          true);
  REQUIRE(assertFuzzyEquals(Magnets::doubles(10, 1000), 0.6921486500921933) ==
          true);
  REQUIRE(assertFuzzyEquals(Magnets::doubles(10, 10000), 0.6930471674194457) ==
          true);
  REQUIRE(assertFuzzyEquals(Magnets::doubles(20, 10000), 0.6930471955575918) ==
          true);
}