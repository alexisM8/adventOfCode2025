#include "utils.hpp"
#include <cmath>
#include <set>

struct JunctionBox;

std::uint64_t junction_id(const JunctionBox &j);

struct Circut {
  int id;
  std::set<int> ids;
};

struct JunctionBox {
  int x, y, z;

  JunctionBox &operator-=(const JunctionBox &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }

  constexpr JunctionBox operator-(const JunctionBox &other) const noexcept {
    JunctionBox result = *this;
    result -= other;
    return result;
  }
};

double distance(const JunctionBox &a, const JunctionBox &b) {
  auto diff = a - b;
  return std::sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
}

static constexpr const char *puzzle_input = "DayEight/day_eight_example.txt";

int main(int argc, char **argv) {
  using namespace aoc::utils;

  auto contents = read(puzzle_input);
  auto rows = split(contents, "\n");

  std::vector<JunctionBox> boxes;
  for (auto row : rows) {
    auto [x, y, z] = split(row, ",").as<tuple_n<int, 3>>();
    boxes.emplace_back(x, y, z);
  }

  std::vector<Circut> circuts;
  for (auto &b : boxes) {
    circuts.emplace_back(junction_id(b));
  }

  for (auto i{0uz}; i < boxes.size(); i++) {
    auto current = boxes[i];
    for (auto j{i + 1}; j < boxes.size(); j++) {
      auto to_check = boxes[j];
      if (distance(current, to_check))
    }
  }
}

std::uint64_t junction_id(const JunctionBox &j) {
  constexpr std::uint64_t OFFSET = 1'000'000;
  constexpr std::uint64_t RANGE = 2 * OFFSET + 1;

  return (j.x + OFFSET) + (j.y + OFFSET) * RANGE +
         (j.z + OFFSET) * RANGE * RANGE;
}
