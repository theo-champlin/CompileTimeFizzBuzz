#include <iostream>
#include <tuple>
#include <utility>

template <std::size_t... Is, typename Tup>
void Write(std::index_sequence<Is...>, const Tup& values)
{
   ((std::cout << std::get<Is>(values) << std::endl), ...);
}

template<typename Tup>
void Write(const Tup& values)
{
   Write(
      std::make_index_sequence<std::tuple_size<std::decay_t<Tup>>::value>{},
      values);
}

template<std::size_t value>
constexpr auto FizzBuzzConvert()
{
   if constexpr (!(value % 3) && !(value % 5))
   {
      return "FizzBuzz";
   }
   else if constexpr (!(value % 3))
   {
      return "Fizz";
   }
   else if constexpr (!(value % 5))
   {
      return "Buzz";
   }
   else
   {
      return value;
   }
}

template<std::size_t... Indicies>
constexpr auto GenerateFuzzBuzzValues(std::index_sequence<Indicies...>)
{
   return std::make_tuple(FizzBuzzConvert<Indicies + 1UL>()...);
}

template<std::size_t Count>
constexpr auto FizzBuzz()
{
   return GenerateFuzzBuzzValues(std::make_index_sequence<Count>{});
}
