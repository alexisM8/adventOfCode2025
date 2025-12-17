#include "utils.hpp"
#include <iostream>

auto check_repeating_substring(std::string_view str) -> bool;

static constexpr const char *puzzle_input = "DayTwo/day_two.txt";

int main(int argc, char **argv) {
  using namespace aoc::utils;

  auto contents = read(puzzle_input);
  auto ranges = split(contents, ",");

  unsigned long long tally = 0;
  for (const auto &range : ranges) {
    auto values = split(range, "-");
    auto start = std::stoll(*values.begin());
    auto end = std::stoll(*--values.end());
    for (auto i = start; i <= end; i++) {
      auto val = std::to_string(i);
      if (check_repeating_substring(val)) {
        tally += i;
        std::cout << i << " is invalid\n";
        std::cout << "running tally=" << tally << "\n";
      }
    }
  }
  std::cout << "puzzle output: " << tally << std::endl;
  // 65794984339
  // +1 gold star
}

auto check_repeating_substring(std::string_view str) -> bool {
  // current length of substring to check
  std::cout << "inspecting " << str << "\n";
  auto current_size = 1;
  bool invalid = false;
  while (current_size < str.size() && !invalid) {
    // start at begining
    for (auto i = 0; i < str.size(); i += current_size) {
      auto to_check = str.substr(0, current_size);
      bool matching = true;
      for (auto j = current_size; j < str.size(); j += current_size) {
        std::cout << "checking " << to_check << " against "
                  << str.substr(j, current_size) << "\n";
        if (to_check != str.substr(j, current_size)) {
          matching = false;
          break;
        }
      }
      if (matching) {
        invalid = true;
        break;
      }

      current_size++;
    }
  }
  return invalid;
}
