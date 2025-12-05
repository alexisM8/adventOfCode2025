#include "utils.hpp"
#include <iostream>
#include <stack>

auto calculate_joltage(std::string_view str) -> unsigned long long;

static constexpr const char *puzzle_input = "DayThree/day_three.txt";

int main(int argc, char **argv) {
  using namespace aoc::utils;
  auto contents = read(puzzle_input);
  auto banks = split(contents, "\n");

  auto total = 0ULL;
  for (const auto &bank : banks) {
    total += calculate_joltage(bank);
  }
  std::cout << "total joltage: " << total << "\n";
  // 169077317650774
  // + 1 gold start
}

auto calculate_joltage_old(std::string_view str) -> unsigned long long {
  std::string joltage;
  std::stack<int> storage;
  try {
    for (std::size_t i = 0; i < str.size(); i++) {
      if (storage.empty()) {
        storage.push(str.at(i) - '0');
      } else {
        if (storage.top() >= str.at(i) - '0') {
          storage.push(str.at(i) - '0');
          continue;
        }
        while (storage.top() < str.at(i) - '0' &&
               str.substr(i, str.size() - 1).size() > 12 && !storage.empty()) {
          storage.pop();
        }
        storage.push(str.at(i) - '0');
      }
    }
    while (!storage.empty()) {
      joltage.append(std::to_string(storage.top()));
      storage.pop();
    }
    std::reverse(joltage.begin(), joltage.end());
    std::cout << "joltage for " << str << " -> " << joltage.substr(0, 12)
              << "\n";
    return std::stoull(joltage.substr(0, 12));

  } catch (std::exception &e) {
    std::cout << "error: " << e.what() << "\n";
  }
}

auto calculate_joltage(std::string_view str) -> unsigned long long {
  const std::size_t TARGET_LEN = 12;
  const std::size_t n = str.size();
  std::size_t to_remove = n - TARGET_LEN;

  std::string stack;
  stack.reserve(n);

  for (char c : str) {
    while (!stack.empty() && to_remove > 0 && stack.back() < c) {
      stack.pop_back();
      --to_remove;
    }
    stack.push_back(c);
  }
  std::string joltage = stack.substr(0, TARGET_LEN);

  std::cout << "joltage for " << str << " -> " << joltage << "\n";
  return std::stoull(joltage);
}
