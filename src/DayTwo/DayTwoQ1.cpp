#include "utils.hpp"
#include <iostream>

static constexpr const char *puzzle_input = "DayTwo/day_two.txt";

int main(int argc, char **argv) {
  using namespace aoc::utils;

  auto contents = read(puzzle_input);
  auto ranges = split(contents, ",");

  unsigned long long tally = 0;
  for (const auto &range : ranges) {
    auto values = split(range, "-");
    auto start = std::stoll(values.front());
    auto end = std::stoll(values.back());
    for (auto i = start; i <= end; i++) {
      auto val = std::to_string(i);
      if (val.size() % 2 == 0) {
        auto first_half = val.substr(0, val.size() / 2);
        auto second_half = val.substr(val.size() / 2, val.size() - 1);
        if (first_half == second_half) {
          tally += i;
          std::cout << i << " is invalid\n";
          std::cout << "running tally=" << tally << "\n";
        }
      }
    }
  }
  // 40398804950
  //+1 gold star
}
