#include "catch2/catch.hpp"
#include "format_duration.hpp"

TEST_CASE("Human readable duration format") {
  REQUIRE(format_duration(0) == "now");
  REQUIRE(format_duration(1) == "1 second");
  REQUIRE(format_duration(62) == "1 minute and 2 seconds");
  REQUIRE(format_duration(120) == "2 minutes");
  REQUIRE(format_duration(3662) == "1 hour, 1 minute and 2 seconds");
}