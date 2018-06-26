#include "../../Tuples/FizzBuzz.hpp"

TEST_CASE("First element")
{
   constexpr auto expected = std::make_tuple(1);

   REQUIRE(expected == FizzBuzz<1>());
}

TEST_CASE("First string")
{
   constexpr auto expected = std::make_tuple(
      1, 2, "Fizz");

   REQUIRE(expected == FizzBuzz<3>());
}

TEST_CASE("First Buzz")
{
   constexpr auto expected = std::make_tuple(
      1, 2, "Fizz", 4, "Buzz");

   REQUIRE(expected == FizzBuzz<5>());
}

TEST_CASE("First two digit number")
{
   constexpr auto expected = std::make_tuple(
      1, 2, "Fizz", 4, "Buzz",
      "Fizz", 7, 8, "Fizz", "Buzz",
      11);

   REQUIRE(expected == FizzBuzz<11>());
}

TEST_CASE("First FizzBuzz")
{
   constexpr auto expected = std::make_tuple(
      1, 2, "Fizz", 4, "Buzz",
      "Fizz", 7, 8, "Fizz", "Buzz",
      11, "Fizz", 13, 14, "FizzBuzz");

   REQUIRE(expected == FizzBuzz<15>());
}

TEST_CASE("First 100")
{
   constexpr auto expected = std::make_tuple(
      1, 2, "Fizz", 4, "Buzz",
      "Fizz", 7, 8, "Fizz", "Buzz",
      11, "Fizz", 13, 14, "FizzBuzz",
      16, 17, "Fizz", 19, "Buzz",
      "Fizz", 22, 23, "Fizz", "Buzz",
      26, "Fizz", 28, 29, "FizzBuzz",
      31, 32, "Fizz", 34, "Buzz",
      "Fizz", 37, 38, "Fizz", "Buzz",
      41, "Fizz", 43, 44, "FizzBuzz",
      46, 47, "Fizz", 49, "Buzz",
      "Fizz", 52, 53, "Fizz", "Buzz",
      56, "Fizz", 58, 59, "FizzBuzz",
      61, 62, "Fizz", 64, "Buzz",
      "Fizz", 67, 68, "Fizz", "Buzz",
      71, "Fizz", 73, 74, "FizzBuzz",
      76, 77, "Fizz", 79, "Buzz",
      "Fizz", 82, 83, "Fizz", "Buzz",
      86, "Fizz", 88, 89, "FizzBuzz",
      91, 92, "Fizz", 94, "Buzz",
      "Fizz", 97, 98, "Fizz", "Buzz");

   REQUIRE(expected == FizzBuzz<100>());
}
