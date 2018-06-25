#include ""../../Second\ Pass/FizzBuzz.hpp""

TEST_CASE("First element")
{
   constexpr auto expected = constant_expression::string<1>
   {
      "1"
   };

   static_assert(expected == FizzBuzz<1>());
}

TEST_CASE("First string")
{
   constexpr auto expected = constant_expression::string<8>
   {
      "1\n2\nFizz"
   };

   static_assert(expected == FizzBuzz<3>());
}

TEST_CASE("First Buzz")
{
   constexpr auto expected = constant_expression::string<15>
   {
      "1\n2\nFizz\n4\nBuzz"
   };

   static_assert(expected == FizzBuzz<5>());
}

TEST_CASE("First two digit number")
{
   constexpr auto expected = constant_expression::string<37>
   {
      "1\n2\nFizz\n4\nBuzz\n"
      "Fizz\n7\n8\nFizz\nBuzz\n"
      "11"
   };

   static_assert(expected == FizzBuzz<11>());
}

TEST_CASE("First FizzBuzz")
{
   constexpr auto expected = constant_expression::string<57>
   {
      "1\n2\nFizz\n4\nBuzz\n"
      "Fizz\n7\n8\nFizz\nBuzz\n"
      "11\nFizz\n13\n14\nFizzBuzz"
   };

   static_assert(expected == FizzBuzz<15>());
}

TEST_CASE("First 100")
{
   constexpr auto expected = constant_expression::string<412>
   {
      "1\n2\nFizz\n4\nBuzz\n"
      "Fizz\n7\n8\nFizz\nBuzz\n"
      "11\nFizz\n13\n14\nFizzBuzz\n"
      "16\n17\nFizz\n19\nBuzz\n"
      "Fizz\n22\n23\nFizz\nBuzz\n"
      "26\nFizz\n28\n29\nFizzBuzz\n"
      "31\n32\nFizz\n34\nBuzz\n"
      "Fizz\n37\n38\nFizz\nBuzz\n"
      "41\nFizz\n43\n44\nFizzBuzz\n"
      "46\n47\nFizz\n49\nBuzz\n"
      "Fizz\n52\n53\nFizz\nBuzz\n"
      "56\nFizz\n58\n59\nFizzBuzz\n"
      "61\n62\nFizz\n64\nBuzz\n"
      "Fizz\n67\n68\nFizz\nBuzz\n"
      "71\nFizz\n73\n74\nFizzBuzz\n"
      "76\n77\nFizz\n79\nBuzz\n"
      "Fizz\n82\n83\nFizz\nBuzz\n"
      "86\nFizz\n88\n89\nFizzBuzz\n"
      "91\n92\nFizz\n94\nBuzz\n"
      "Fizz\n97\n98\nFizz\nBuzz"
   };

   static_assert(expected == FizzBuzz<100>());
}
