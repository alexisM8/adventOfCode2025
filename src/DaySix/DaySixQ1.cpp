#include "utils.hpp"
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

using ull = unsigned long long;
auto gather_input_nums(const std::vector<std::string> &, ull)
    -> std::vector<std::string>;

auto compute_sum(const std::vector<std::string> &nums,
                 const std::vector<std::string> &ops) -> ull;

static constexpr const char *puzzle_input = "DaySix/day_six.txt";
int main(int argc, char **argv) {
  using namespace aoc::utils;

  auto contents = read(puzzle_input);
  auto num_and_ops = split(contents, "\n");

  auto back = num_and_ops.back();
  auto ops = split(back, " ");
  num_and_ops.pop_back();

  auto nums = gather_input_nums(num_and_ops, ops.size());
  ull ans = compute_sum(nums, ops);
  std::cout << "answer to math hw: " << ans << "\n";
  return 0;
}

auto compute_sum(const std::vector<std::string> &nums,
                 const std::vector<std::string> &ops) -> ull {
  ull total_sum = 0;
  try {
    for (std::size_t i = 0; i < ops.size(); i++) {
      if (ops[i] == "+") {
        auto args = aoc::utils::split(nums[i], ",");
        ull temp = 0;
        for (auto &arg : args) {
          temp += std::stoi(arg);
        }
        total_sum += temp;
      } else if (ops[i] == "*") {
        auto args = aoc::utils::split(nums[i], ",");
        ull temp = 1;
        for (auto &arg : args) {
          temp *= std::stoi(arg);
        }
        total_sum += temp;
      }
    }
  } catch (std::exception &e) {
    std::cout << "error in compute_sum, error: " << e.what() << "\n";
  }

  return total_sum;
  // + 1 gold star
  // 4583860641327
}

auto gather_input_nums(const std::vector<std::string> &nums, ull size)
    -> std::vector<std::string> {
  std::vector<std::string> out(size);

  try {
    for (auto &line : nums) {

      auto inputs = aoc::utils::split(line, " ");

      if (inputs.size() < size) {
        throw std::runtime_error("Insufficient fields in line: " + line);
      }

      for (ull i = 0; i < size; i++) {
        out[i].append(inputs[i]);
        out[i].push_back(',');
      }
    }
  } catch (const std::exception &e) {
    std::cout << "error in gather_input_nums: " << e.what() << "\n";
  }

  return out;
}
