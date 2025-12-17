#include "utils.hpp"
#include <iostream>
#include <set>

static constexpr const char *puzzle_input = "DayFive/day_five.txt";

int main(int argc, char **argv) {
  using namespace aoc::utils;
  auto contents = read(puzzle_input);
  auto data = split(contents, "\n\n");

  auto ranges = split(*data.begin(), "\n");
  auto availible_ids = split(*--data.end(), "\n");
  std::set<unsigned long long> seen;

  for (auto &id : availible_ids) {

    unsigned long long ida = std::stoull(id);
    for (auto &range : ranges) {
      auto cases = split(range, "-");
      unsigned long long lower = std::stoull(*cases.begin());
      unsigned long long upper = std::stoull(*--cases.end());

      std::cout << "checking id " << ida << " againt range=" << range << "\n";
      if (ida >= lower && ida <= upper) {
        seen.insert(ida);

        std::cout << ida << " is fresh\n";
        break;
      }
    }
  }

  std::cout << "fresh ids: " << seen.size() << std::endl;
  //+1 gold star
  // 617
}
