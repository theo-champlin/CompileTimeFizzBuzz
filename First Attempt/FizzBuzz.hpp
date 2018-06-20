#include <iostream>
#include <tuple>
#include <utility>

template <typename ValueType>
void WriteLine(ValueType value)
{
   std::cout << value << std::endl;
}

template <typename ValueType, typename... Args>
void WriteLine(ValueType value, Args&&... args)
{
   std::cout << value << std::endl;
   WriteLine(std::forward<Args&&>(args)...);
}

template <std::size_t... Is, typename Tup>
void Write(std::index_sequence<Is...>, Tup values)
{
   WriteLine(std::get<Is>(values)...);
}

template<typename Tup>
void Write(Tup&& values)
{
   Write(
      std::make_index_sequence<std::tuple_size<std::decay_t<Tup>>::value>{},
      std::forward<Tup&&>(values));
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

int main()
{
   constexpr auto local = FizzBuzz<100>();
   Write(local);
}