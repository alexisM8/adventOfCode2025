#include "utils.hpp"
#include <cassert>
#include <iostream>

auto compute_next_position(int current_pos, std::string_view dir, int count)
    -> std::pair<int, int>;

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
      auto [new_pos, new_zeros] =
          compute_next_position(dial_pos, direction, std::stoi(count));
      if (new_pos == 0) {
        zeds++;
        std::cout << "pointing at zero end of rotation. zed++\n";
      }
      zeds += new_zeros;
      dial_pos = new_pos;
    }();
  }

  std::cout << "combo is: " << zeds << "\n";
  // +1 gold star: 6684
}

auto compute_next_position(int current_pos, std::string_view dir, int count)
    -> std::pair<int, int> {

  int remaining = count;
  int zeds = 0;
  if (dir.starts_with("L")) {
    while (remaining > 0) {
      std::cout << "DIR=L" << ", cur=" << current_pos << ", rem=" << remaining
                << "\n";
      if (current_pos - remaining >= 0) {
        current_pos -= remaining;
        remaining = 0;
      } else if (current_pos - remaining < 0) {
        std::cout << "curr-remaining=" << current_pos - remaining
                  << ". zed++\n";
        if (current_pos != 0) {
          zeds++;
        }
        remaining -= current_pos + 1;
        current_pos = 99;
      }
    }
  } else if (dir.starts_with("R")) {
    while (remaining > 0) {
      std::cout << "DIR=R" << ", cur=" << current_pos << ", rem=" << remaining
                << "\n";

      if (current_pos + remaining <= 99) {
        current_pos += remaining;
        remaining = 0;
      } else if (current_pos + remaining > 99) {
        if (current_pos + remaining > 100) {
          std::cout << "curr+remaining=" << current_pos + remaining
                    << ". zed++\n";
          zeds++;
        }
        remaining -= 99 - current_pos;
        current_pos = -1;
      }
    }
  }
  return std::make_pair(current_pos, zeds);
}
