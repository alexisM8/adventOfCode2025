cmake_minimum_required(VERSION 3.21)

project(AOC2025 VERSION 0.1 LANGUAGES CXX)

# Global C++ settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Default to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING
      "Choose the type of build, options are: Debug Release."
      FORCE)
endif()

# Option example, keep if you actually use it somewhere
set(BUILD_STATIC FALSE CACHE BOOL "Set this to link external libraries statically")

# More modern way to add warnings/flags per configuration
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(
    "$<$<CONFIG:Debug>:-Wall;-Wextra;-g;-gdwarf-4;-O0>"
    "$<$<CONFIG:Release>:-O3>"
  )
endif()

# ---------------------------------------------------------------------------
# Project layout
# ---------------------------------------------------------------------------

set(SRC_DIR     "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(PUZZLE_INPUT "${CMAKE_CURRENT_SOURCE_DIR}/puzzle_input")

# Helper to add DayXQ1 and DayXQ2 in one go
function(add_aoc_day day_name)
  foreach(part 1 2)
    set(target "${day_name}Q${part}")
    add_executable(${target}
      "${SRC_DIR}/${day_name}/${day_name}Q${part}.cpp"
    )
    target_include_directories(${target}
      PRIVATE
        "${INCLUDE_DIR}"
    )
    target_include_directories(${target} PRIVATE "${PUZZLE_INPUT}")
    add_compile_definitions(PUZZLE_INPUT="${PUZZLE_INPUT}")
  endforeach()
endfunction()

# List the days you’ve implemented
foreach(day
  # DayOne
  # DayTwo
  # DayThree
  # DayFour
  DayFive
)
  add_aoc_day(${day})
endforeach()

