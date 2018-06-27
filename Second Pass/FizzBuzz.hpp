#include "constant_expression/number_to_string.hpp"
#include "constant_expression/string.hpp"

template<unsigned value>
constexpr auto FizzBuzzConvert()
{
   if constexpr (!(value % 5) && !(value % 3))
   {
      return constant_expression::literal_to_string("FizzBuzz");
   }
   else if constexpr (!(value % 3))
   {
      return constant_expression::literal_to_string("Fizz");
   }
   else if constexpr (!(value % 5))
   {
      return constant_expression::literal_to_string("Buzz");
   }
   else
   {
      return constant_expression::number_to_string<value>::convert();
   }
}

template<unsigned value>
constexpr auto FizzBuzz()
{
   constexpr auto current = FizzBuzz<value - 1>();
   constexpr auto next = FizzBuzzConvert<value>();

   constant_expression::string<std::size(current) + std::size(next) + 1> aggregated{ 0 };

   aggregated.copy(std::begin(current), std::end(current));
   aggregated[std::size(current)] = '\n';
   aggregated.copy(std::begin(next), std::end(next), std::size(current) + 1);

   return aggregated;
}

template<>
constexpr auto FizzBuzz<1>()
{
   return FizzBuzzConvert<1>();
}
