// https://www.codewars.com/kata/5263c6999e0f40dee200059d
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

static const std::unordered_map<char, std::string> possibilities{
    {'0', "08"},    {'1', "124"},  {'2', "2135"}, {'3', "326"},   {'4', "4157"},
    {'5', "52468"}, {'6', "6359"}, {'7', "748"},  {'8', "85790"}, {'9', "968"},

};

std::vector<std::string> get_pins(std::string observed,
                                  std::string prefix = "") {
  if (observed.empty())
    return {""};

  std::vector<std::string> results{};
  for (const auto digit : possibilities.at(observed[0])) {
    for (auto pin : get_pins(observed.substr(1), prefix + digit)) {
      results.push_back(digit + pin);
    }
  }
  return results;
}