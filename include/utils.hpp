#pragma once

#include <array>
#include <charconv>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <vector>

namespace aoc {
namespace utils {

template <class T> T parse_token(std::string_view sv) {
  if constexpr (std::is_same_v<T, std::string>) {
    return std::string(sv);
  } else if constexpr (std::is_integral_v<T> && !std::is_same_v<T, bool>) {
    T value{};
    auto first = sv.data();
    auto last = sv.data() + sv.size();
    auto [ptr, ec] = std::from_chars(first, last, value);
    if (ec != std::errc{} || ptr != last) {
      throw std::runtime_error("parse_token: invalid integer");
    }
    return value;
  } else if constexpr (std::is_floating_point_v<T>) {
    T value{};
    auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), value);
    if (ec != std::errc{} || ptr != sv.data() + sv.size())
      throw std::runtime_error("parse_token: invalid float");
    return value;
  } else {
    static_assert(!sizeof(T),
                  "parse_token: unsupported type (add specialization)");
  }
}

// ---------- type traits ----------
template <class T> struct is_std_array : std::false_type {};
template <class U, std::size_t N>
struct is_std_array<std::array<U, N>> : std::true_type {};

template <class T> struct is_std_tuple : std::false_type {};
template <class... Ts>
struct is_std_tuple<std::tuple<Ts...>> : std::true_type {};

// Optional helper: tuple_n<T,3> gives std::tuple<T,T,T>
template <class T, std::size_t N, class Seq = std::make_index_sequence<N>>
struct tuple_n_impl;
template <class T, std::size_t N, std::size_t... I>
struct tuple_n_impl<T, N, std::index_sequence<I...>> {
  template <std::size_t> using always_T = T;
  using type = std::tuple<always_T<I>...>;
};
template <class T, std::size_t N>
using tuple_n = typename tuple_n_impl<T, N>::type;

// ---------- split_view proxy ----------
struct split_view {
  std::vector<std::string_view> parts;

  std::size_t size() const { return parts.size(); }
  const std::string_view &operator[](std::size_t i) const { return parts[i]; }

  auto begin() { return parts.begin(); }
  auto end() { return parts.end(); }
  auto begin() const { return parts.begin(); }
  auto end() const { return parts.end(); }
  auto cbegin() const { return parts.cbegin(); }
  auto cend() const { return parts.cend(); }

  template <class Out> Out as() const {
    if constexpr (is_std_array<Out>::value) {
      return as_array<Out>();
    } else if constexpr (is_std_tuple<Out>::value) {
      return as_tuple<Out>();
    } else {
      static_assert(
          !sizeof(Out),
          "split_view::as<Out> supports std::array and std::tuple only");
    }
  }

private:
  template <class Arr> Arr as_array() const {
    using Elem = typename Arr::value_type;
    constexpr std::size_t N = std::tuple_size_v<Arr>;
    if (parts.size() != N)
      throw std::runtime_error("split.as<array>: wrong token count");

    Arr out{};
    for (std::size_t i = 0; i < N; ++i) {
      out[i] = parse_token<Elem>(parts[i]);
    }
    return out;
  }

  template <class Tup, std::size_t... I>
  Tup as_tuple_impl(std::index_sequence<I...>) const {
    return Tup{parse_token<std::tuple_element_t<I, Tup>>(parts[I])...};
  }

  template <class Tup> Tup as_tuple() const {
    constexpr std::size_t N = std::tuple_size_v<Tup>;
    if (parts.size() != N)
      throw std::runtime_error("split.as<tuple>: wrong token count");
    return as_tuple_impl<Tup>(std::make_index_sequence<N>{});
  }
};

template <typename Delim = std::string>
split_view split(std::string_view text, Delim delim) {
  split_view result;

  auto push_token = [&](std::string_view sv) {
    if (!sv.empty())
      result.parts.emplace_back(sv);
  };

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
  } else {
    std::string_view dv = delim;
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
