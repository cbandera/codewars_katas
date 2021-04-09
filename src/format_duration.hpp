#pragma once
// https://www.codewars.com/kata/52742f58faf5485cae000b9a/
#include <sstream>
#include <string>
#include <vector>

// years, days, hours, minutes and seconds
std::vector<std::pair<std::string, int>> formatters{
    {"second", 0}, {"minute", 60}, {"hour", 60}, {"day", 24}, {"year", 365},
};

std::string format_duration(int seconds) {
  if (seconds == 0)
    return "now";

  // Compute counters
  std::vector<int> counters{seconds};
  for (size_t i = 1; i < formatters.size(); ++i) {
    counters.emplace_back(counters[i - 1] / formatters[i].second);
    counters[i - 1] = counters[i - 1] % formatters[i].second;
  }

  // Create formatted strings
  std::vector<std::string> msgs{};
  for (int i = static_cast<int>(formatters.size()) - 1; i >= 0; --i) {
    if (counters[i] > 0) {
      std::ostringstream msg;
      auto s = counters[i] > 1 ? "s" : "";
      msg << counters[i] << " " << formatters[i].first << s;
      msgs.emplace_back(msg.str());
    }
  }

  // Join strings
  std::string result{};
  for (size_t i = 0; i < msgs.size(); ++i) {
    result += msgs[i];
    if (static_cast<int>(i) < static_cast<int>(msgs.size()) - 2)
      result += ", ";
    else if (static_cast<int>(i) == static_cast<int>(msgs.size()) - 2)
      result += " and ";
  }

  return result;
}