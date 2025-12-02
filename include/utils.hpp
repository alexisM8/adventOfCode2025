#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace aoc {
namespace utils {
template <typename Container = std::vector<std::string>,
          typename Delim = std::string>
Container split(std::string_view text, Delim delim) {
  using value_type = typename Container::value_type;
  static_assert(std::is_constructible_v<value_type, std::string_view>,
                "Container::value_type must be constructible from string_view");

  Container result;

  // helper to ignore empty tokens
  auto push_token = [&](std::string_view sv) {
    if (!sv.empty()) {
      result.emplace_back(sv);
    }
  };

  // Case 1 — char delimiter
  if constexpr (std::is_same_v<Delim, char>) {
    std::size_t start = 0;
    while (start <= text.size()) {
      std::size_t pos = text.find(delim, start);
      if (pos == std::string_view::npos) {
        push_token(text.substr(start));
        break;
      }
      push_token(text.substr(start, pos - start));
      start = pos + 1;
    }
  }
  // Case 2 — string or string_view delimiter (multi-character)
  else {
    std::string_view dv = delim; // works for const char* and string
    if (dv.empty()) {
      push_token(text);
      return result;
    }

    std::size_t start = 0;
    while (start <= text.size()) {
      std::size_t pos = text.find(dv, start);
      if (pos == std::string_view::npos) {
        push_token(text.substr(start));
        break;
      }
      push_token(text.substr(start, pos - start));
      start = pos + dv.size();
    }
  }

  return result;
}

std::string read(std::string_view relative_path) {
  namespace fs = std::filesystem;

  fs::path full_path = fs::path(PUZZLE_INPUT) / relative_path;

  std::ifstream input(full_path);

  if (!input) {
    std::cerr << "[Error] could not open file: " << full_path << "\n";
    std::exit(1);
  }

  std::stringstream ss;
  ss << input.rdbuf();
  return ss.str();
}
} // namespace utils
} // namespace aoc
