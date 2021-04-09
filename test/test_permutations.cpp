#include "catch2/catch.hpp"
#include "permutations.hpp"

TEST_CASE("Permutation Sample Tests") {
  REQUIRE(std::vector<std::string>{"a"} == permutations("a"));
  REQUIRE(std::vector<std::string>{"ab", "ba"} == permutations("ab"));
  REQUIRE(std::vector<std::string>{"aabb", "abab", "abba", "baab", "baba",
                                   "bbaa"} == permutations("aabb"));
}