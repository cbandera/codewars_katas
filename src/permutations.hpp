#pragma once
// https://www.codewars.com/kata/5254ca2719453dcc0b00027d/
#include <algorithm>
#include <string>
#include <vector>

std::vector<std::string> permutations(std::string s) {
  std::sort(s.begin(), s.end());
  std::vector<std::string> permutations{s};
  while (std::next_permutation(s.begin(), s.end())) {
    permutations.emplace_back(s);
  }
  return permutations;
}