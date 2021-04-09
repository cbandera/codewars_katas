#include "catch2/catch.hpp"
#include "parse_ints.hpp"

TEST_CASE("Parse integers from stings", "[parse_int]") {
  REQUIRE(parse_int("one") == 1);
  REQUIRE(parse_int("twenty") == 20);
  REQUIRE(parse_int("two hundred and forty-six") == 246);
  REQUIRE(
      parse_int(
          "seven hundred eighty-three thousand nine hundred and nineteen") ==
      783919);
}
