#include "utils.hpp"
#include <iostream>
#include <string_view>
#include <vector>

static constexpr const char *puzzle_input = "DaySeven/day_seven.txt";

auto count_timelines(const std::vector<std::string> &diagram) -> long long;

int main(int argc, char **argv) {
  auto contents = aoc::utils::read(puzzle_input);
  auto rows = aoc::utils::split(contents, "\n");
  auto ans = count_timelines(rows);

  std::cout << "timelines hit: " << ans << std::endl;
  // + 1 gold star
  // 15118009521693
}

auto count_timelines(const std::vector<std::string> &diagram) -> long long {
  const int num_rows = diagram.size();
  const int num_cols = diagram[0].size();

  // Locate the starting point 'S'
  int start_row = -1;
  int start_col = -1;
  bool found = false;
  for (int row = 0; row < num_rows; row++) {
    for (int col = 0; col < num_cols; col++) {
      if (diagram[row][col] == 'S') {
        start_row = row;
        start_col = col;
        found = true;
      }
    }
    if (found) {
      break;
    }
  }

  // timelines[row][col] = number of timelines that reach this cell
  std::vector<std::vector<long long>> timelines(
      num_rows, std::vector<long long>(num_cols, 0));

  // The particle starts moving directly below 'S'
  timelines[start_row + 1][start_col] = 1;

  long long completed_timelines = 0;

  // Process the manifold top to bottom
  for (int row = start_row + 1; row < num_rows; row++) {
    for (int col = 0; col < num_cols; col++) {
      long long current_paths = timelines[row][col];
      if (current_paths == 0)
        continue;

      // If we've reached the bottom, this timeline is finished
      if (row == num_rows - 1) {
        completed_timelines += current_paths;
        continue;
      }

      char cell_below = diagram[row + 1][col];

      // Straight pipe — timeline continues downward
      if (cell_below == '.') {
        timelines[row + 1][col] += current_paths;
      }
      // Splitter — timeline splits into left and right
      else if (cell_below == '^') {
        if (col > 0)
          timelines[row + 1][col - 1] += current_paths;
        if (col + 1 < num_cols)
          timelines[row + 1][col + 1] += current_paths;
      }
      // Blocked or invalid — timeline ends here
      else {
        completed_timelines += current_paths;
      }
    }
  }

  return completed_timelines;
}
