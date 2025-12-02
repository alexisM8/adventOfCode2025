#include "utils.hpp"
#include <cassert>
#include <iostream>

auto compute_next_position(int current_pos, std::string_view dir, int count)
    -> int;

int main(int argc, char **argv) {
  using namespace aoc::utils;
  static constexpr const char *puzzle_input = "DayOne/day_one.txt";
  auto contents = read(puzzle_input);
  auto moves = split(contents, "\n");

  auto dial_pos = 50;
  auto zeds = 0;

  for (const auto &move : moves) {
    assert(move.size() >= 2);
    auto direction = move.substr(0, 1);
    auto count = move.substr(1, move.size() - 1);

    [&]() {
      dial_pos = compute_next_position(dial_pos, direction, std::stoi(count));
      if (dial_pos == 0) {
        zeds++;
      }
    }();
  }

  std::cout << "combo is: " << zeds << "\n";
  // +1 gold star: 1139
}

auto compute_next_position(int current_pos, std::string_view dir, int count)
    -> int {

  int remaining = count;
  if (dir.starts_with("L")) {
    while (remaining > 0) {
      if (current_pos - remaining >= 0) {
        current_pos -= remaining;
        remaining = 0;
      } else if (current_pos - remaining < 0) {
        remaining -= current_pos + 1;
        current_pos = 99;
      }
    }
  } else if (dir.starts_with("R")) {
    while (remaining > 0) {
      if (current_pos + remaining <= 99) {
        current_pos += remaining;
        remaining = 0;
      } else if (current_pos + remaining > 99) {
        remaining -= 99 - current_pos;
        current_pos = -1;
      }
    }
  }
  return current_pos;
}
