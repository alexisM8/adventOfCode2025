#include "utils.hpp"
#include <iostream>

auto count_adjacent_neighbors(const aoc::utils::split_view &data, int row,
                              int column) -> int;

auto solve(const aoc::utils::split_view &data) -> int;

static constexpr const char *puzzle_input = "DayFour/day_four.txt";

int main(int argc, char **argv) {
  using namespace aoc::utils;
  auto contents = read(puzzle_input);
  auto rows = split(contents, "\n");
  int count = solve(rows);
  std::cout << "rolls reachable: " << count << std::endl;
  // + 1 gold star
  // 1527
}

auto solve(const aoc::utils::split_view &data) -> int {
  int count = 0;
  for (int row = 0; row < data.size(); row++) {
    for (int column = 0; column < data[row].size(); column++) {
      if (data[row][column] == '@') {
        int neighbors = count_adjacent_neighbors(data, row, column);
        if (neighbors < 4) {
          count++;
        }
      }
    }
  }
  return count;
}

auto count_adjacent_neighbors(const aoc::utils::split_view &data, int row,
                              int column) -> int {
  int count = 0;
  for (int i = row - 1; i <= row + 1; i++) {
    for (int j = column - 1; j <= column + 1; j++) {
      // Skip the center cell itself
      if (i == row && j == column) {
        continue;
      }

      // Bounds check
      if (i < 0 || i >= static_cast<int>(data.size())) {
        continue;
      }
      if (j < 0 || j >= static_cast<int>(data[i].size())) {
        continue;
      }

      if (data[i][j] == '@') {
        count++;
      }
    }
  }
  std::cout << "point(" << row << ", " << column << ") has " << count
            << " neighbors\n";
  return count;
}
