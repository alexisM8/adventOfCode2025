
#include "utils.hpp"
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using ull = unsigned long long;

struct Worksheet {
  std::vector<std::string> grid; // all lines, padded to same width
  std::size_t num_value_rows;    // number of rows with numbers (all but last)
  std::size_t width;             // number of columns
};

auto load_worksheet(const char *path) -> Worksheet;
auto compute_cephalopod_total(const Worksheet &ws) -> ull;
auto reduce_stack(const std::vector<ull> &stack, char op) -> ull;

// static constexpr const char *puzzle_input = "DaySix/day_six.txt";
static constexpr const char *puzzle_input = "DaySix/day_six.txt";

int main(int argc, char **argv) {
  try {
    auto ws = load_worksheet(puzzle_input);
    ull ans = compute_cephalopod_total(ws);
    std::cout << "answer to math hw (part 2): " << ans << "\n";
    // + 1 gold star
    // 11602774058280
  } catch (const std::exception &e) {
    std::cerr << "Fatal error: " << e.what() << "\n";
    return 1;
  }
  return 0;
}

// Read file, split into lines, drop trailing empties, pad to equal width
auto load_worksheet(const char *path) -> Worksheet {
  using namespace aoc::utils;

  auto contents = read(path);
  auto lines = split(contents, "\n");

  // Remove trailing empty lines
  while (!lines.empty() && lines.back().empty()) {
    lines.pop_back();
  }

  if (lines.empty()) {
    throw std::runtime_error("Input file is empty: " + std::string(path));
  }

  // Compute max width
  std::size_t width = 0;
  for (const auto &line : lines) {
    if (line.size() > width) {
      width = line.size();
    }
  }

  // Pad all lines to that width with spaces
  for (auto &line : lines) {
    if (line.size() < width) {
      line.append(width - line.size(), ' ');
    }
  }

  Worksheet ws;
  ws.grid = std::move(lines);
  ws.width = width;
  ws.num_value_rows = ws.grid.size() - 1; // last row is ops

  if (ws.num_value_rows == 0) {
    throw std::runtime_error("No value rows found in worksheet");
  }

  return ws;
}

// Reduce stack of numbers using given operator
auto reduce_stack(const std::vector<ull> &stack, char op) -> ull {
  if (stack.empty())
    return 0;

  if (op == '+') {
    ull s = 0;
    for (ull n : stack)
      s += n;
    return s;
  } else if (op == '*') {
    ull p = 1;
    for (ull n : stack)
      p *= n;
    return p;
  } else {
    throw std::runtime_error(std::string("Unknown operator: ") + op);
  }
}

// Walk columns right-to-left, build cephalopod numbers, sum problem values
auto compute_cephalopod_total(const Worksheet &ws) -> ull {
  const auto &grid = ws.grid;
  const std::string &ops_row = grid.back();

  ull total = 0;
  std::vector<ull> stack; // numbers for the current cephalopod problem
  stack.reserve(ws.num_value_rows);

  // Columns: right to left
  for (int col = static_cast<int>(ws.width) - 1; col >= 0; --col) {
    // Build a vertical slice (excluding the operator row)
    std::string column;
    column.reserve(ws.num_value_rows);
    for (std::size_t row = 0; row < ws.num_value_rows; ++row) {
      column.push_back(grid[row][col]);
    }

    // Trim spaces from vertical string
    auto first = column.find_first_not_of(' ');
    if (first != std::string::npos) {
      auto last = column.find_last_not_of(' ');
      std::string num_str = column.substr(first, last - first + 1);

      // Check if this slice is all digits
      bool all_digits = !num_str.empty();
      for (char c : num_str) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
          all_digits = false;
          break;
        }
      }

      if (all_digits) {
        stack.push_back(std::stoull(num_str));
      }
    }

    // If there's an operator in this column, reduce current problem
    char op = ops_row[col];
    if ((op == '+' || op == '*') && !stack.empty()) {
      ull val = reduce_stack(stack, op);
      total += val;
      stack.clear();
    }
  }

  return total;
}
