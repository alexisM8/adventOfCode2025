#include "utils.hpp"
#include <iostream>
#include <set>

static constexpr const char *puzzle_input = "DayFive/day_five.txt";

int main(int argc, char **argv) {
  using namespace aoc::utils;
  using ull = unsigned long long;
  auto contents = read(puzzle_input);
  auto data = split(contents, "\n\n");

  auto ranges = split(data.front(), "\n");
  std::vector<std::pair<ull, ull>> intervals;

  for (auto &range : ranges) {
    auto cases = split(range, "-");
    unsigned long long lower = std::stoull(cases.front());
    unsigned long long upper = std::stoull(cases.back());
    intervals.emplace_back(lower, upper);
  }

  std::sort(intervals.begin(), intervals.end(),
            [](const auto &a, const auto &b) {
              if (a.first != b.first)
                return a.first < b.first;
              return a.second < b.second;
            });

  // Merge overlapping/adjacent intervals
  std::vector<std::pair<ull, ull>> merged;
  merged.reserve(intervals.size());

  ull cur_start = intervals[0].first;
  ull cur_end = intervals[0].second;

  for (size_t i = 1; i < intervals.size(); ++i) {
    ull s = intervals[i].first;
    ull e = intervals[i].second;

    // If there is a gap (s > cur_end + 1), start a new interval
    if (s > cur_end + 1) {
      merged.emplace_back(cur_start, cur_end);
      cur_start = s;
      cur_end = e;
    } else {
      // Overlaps or touches: extend current
      if (e > cur_end) {
        cur_end = e;
      }
    }
  }
  // Don't forget the last one
  merged.emplace_back(cur_start, cur_end);

  // Count distinct IDs: sum (end - start + 1)
  unsigned long long total = 0;
  for (const auto &[l, r] : merged) {
    total += (r - l + 1);
  }

  std::cout << "fresh ids: " << total << std::endl;
  // +1 gold star
  // 338258295736104
}
