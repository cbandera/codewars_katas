// https://www.codewars.com/kata/525c7c5ab6aecef16e0001a5
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

static const std::unordered_map<std::string, long> lookup_map{
    {"zero", 0},     {"one", 1},        {"two", 2},       {"three", 3},
    {"four", 4},     {"five", 5},       {"six", 6},       {"seven", 7},
    {"eight", 8},    {"nine", 9},       {"ten", 10},      {"eleven", 11},
    {"twelve", 12},  {"thirteen", 13},  {"fourteen", 14}, {"fifteen", 15},
    {"sixteen", 16}, {"seventeen", 17}, {"eighteen", 18}, {"nineteen", 19},
    {"twenty", 20},  {"thirty", 30},    {"forty", 40},    {"fifty", 50},
    {"sixty", 60},   {"seventy", 70},   {"eighty", 80},   {"ninety", 90},
};

static const std::vector<std::pair<std::string, long>> order_specifiers{
    {"million", 1000000},
    {"thousand", 1000},
    {"hundred", 100},
};

std::vector<std::string> splitWords(const std::string &number) {
  std::vector<std::string> parts{};
  auto begin_it = number.begin();
  while (begin_it != number.end()) {
    auto end_it = std::find_if(begin_it, number.end(), [](const auto &c) {
      return (c == ' ' || c == '-');
    });
    parts.emplace_back(begin_it, end_it);
    begin_it = end_it;
    if (begin_it != number.end()) {
      begin_it++;
    }
  }
  return parts;
}

long translate(const std::string &word) {
  try {
    return lookup_map.at(word);
  } catch (std::out_of_range) {
    return 0;
  }
};

template <typename Iterator>
long split_and_translate(Iterator begin, Iterator end) {
  // split at order specifiers and recurse
  for (const auto &specifier : order_specifiers) {
    auto it = std::find(begin, end, specifier.first);
    if (it != end) {
      return split_and_translate(begin, it) * specifier.second +
             split_and_translate(++it, end);
    }
  }
  // Sum up translated words
  return std::transform_reduce(begin, end, 0, std::plus<>(), translate);
};

long parse_int(std::string number) {
  const auto parts = splitWords(number);
  const long result = split_and_translate(parts.begin(), parts.end());
  return result;
}