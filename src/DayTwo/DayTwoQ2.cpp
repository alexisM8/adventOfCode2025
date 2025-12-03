#include "utils.hpp"
#include <iostream>

static constexpr const char *puzzle_input = "DayTwo/day_two_example.txt";

int main(int argc, char **argv) {
  using namespace aoc::utils;

  auto contents = read(puzzle_input);
  std::cout << contents << "\n";
}
