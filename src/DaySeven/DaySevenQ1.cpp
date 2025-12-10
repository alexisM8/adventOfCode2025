#include "utils.hpp"
#include <iostream>
#include <string_view>
#include <vector>

static constexpr const char *puzzle_input = "DaySeven/day_seven.txt";

auto build_tree(std::vector<std::string> &sv, int rows, int cols)
    -> std::vector<std::string>;

auto count_splits(std::vector<std::string> &sv) -> int;

int main(int argc, char **argv) {
  auto contents = aoc::utils::read(puzzle_input);
  auto rows = aoc::utils::split(contents, "\n");
  auto tree = build_tree(rows, rows.size(), rows.front().size());
  auto ans = count_splits(tree);

  std::cout << "splitters hit: " << ans << std::endl;
  // + 1 gold star
  // 1570
}

auto count_splits(std::vector<std::string> &sv) -> int {
  int count = 0;
  for (int i = 0; i < sv.size(); i++) {
    for (int j = 0; j < sv.front().size(); j++) {
      // if we encounter a split look row - 1
      // and count if there is a '|'
      if (sv[i][j] == '^') {
        if (sv[i - 1][j] == '|') {
          count++;
        }
      }
    }
  }
  return count;
}

auto build_tree(std::vector<std::string> &sv, int rows, int cols)
    -> std::vector<std::string> {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (sv[i][j] == 'S') {
        // startking we should insert a '|' in row + 1
        sv[i + 1][j] = '|';
      }
      if (sv[i][j] == '|') {
        // we are a pipe we should continue down
        // unless we encounter a '^'
        if (sv[i + 1][j] == '.') {
          sv[i + 1][j] = '|';
        } else if (sv[i + 1][j] == '^') {
          // if we hit a spliter then we should split the beam
          if (sv[i + 1][j - 1] == '.' or sv[i + 1][j - 1] == '|') {
            sv[i + 1][j - 1] = '|';
          }
          if (sv[i + 1][j + 1] == '.' or sv[i + 1][j + 1] == '|') {
            sv[i + 1][j + 1] = '|';
          }
        }
      }
    }
  }

  for (auto &row : sv) {
    std::cout << row << "\n";
  }

  return sv;
}
