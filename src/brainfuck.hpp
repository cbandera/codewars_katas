#pragma once
// https://www.codewars.com/kata/526156943dfe7ce06200063e/

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

template <typename Iterator>
size_t find_matching_bracket(const std::string &code, Iterator it) {
  int idx = std::distance(code.begin(), it);
  const char opening_bracket = *it;
  const char closing_bracket = opening_bracket == '[' ? ']' : '[';
  const int idx_inc = opening_bracket == '[' ? +1 : -1;
  const int idx_end = opening_bracket == '[' ? code.size() : -1;
  int counter = 0;
  for (; idx != idx_end; idx += idx_inc) {
    if (code[idx] == opening_bracket)
      ++counter;
    else if (code[idx] == closing_bracket) {
      --counter;
      if (counter == 0)
        break;
    }
  }
  return static_cast<size_t>(idx);
}

std::string brainLuck(const std::string &code, const std::string &input) {
  std::array<uint8_t, 10000> tape{{}};
  size_t idx = 0U;
  auto it = input.begin();
  std::string output;
  std::unordered_map<char, std::function<void(std::string::const_iterator &)>>
      commandLookup{
          {',', [&](auto) { tape[idx] = *it++; }},
          {'.', [&](auto) { output.append(1, static_cast<char>(tape[idx])); }},
          {'>', [&](auto) { ++idx; }},
          {'<', [&](auto) { --idx; }},
          {'+', [&](auto) { ++tape[idx]; }},
          {'-', [&](auto) { --tape[idx]; }},
          {'[',
           [&](auto &c) {
             if (tape[idx] == 0U)
               c = code.begin() + find_matching_bracket(code, c);
           }},
          {']',
           [&](auto &c) {
             if (tape[idx] != 0U)
               c = code.begin() + find_matching_bracket(code, c);
           }},
      };
  for (auto c = code.begin(); c != code.end(); ++c) {
    commandLookup[*c](c);
  }
  return output;
}