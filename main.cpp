#include <array>
#include <iostream>
#include <boost/mpl/string.hpp>
#include <string_view>

template <bool baseCase, unsigned value>
struct ConvertToStringHelper
{
   using type =
      typename boost::mpl::push_back<
         typename ConvertToStringHelper<
            value < 10,
            value / 10
         >::type,
         boost::mpl::char_<'0' + value % 10>
      >::type;
};

template <>
struct ConvertToStringHelper<true, 0>
{
   using type = boost::mpl::string<>;
};


template <unsigned value>
struct ConvertToString
{
   using type =
      typename boost::mpl::c_str<
         typename ConvertToStringHelper<
            value < 10,
            value
         >::type
      >::type;
};

template<unsigned current>
constexpr std::string_view FizzBuzzHelper()
{
   if constexpr (!(current % 3) && !(current % 5))
   {
      return { "FizzBuzz" };
   }
   if constexpr (!(current % 3))
   {
      return { "Fizz" };
   }
   if constexpr (!(current % 5))
   {
      return { "Buzz" };
   }
    
   return { ConvertToString<current>::type::value };
}

template<unsigned count>
struct FizzBuzzArray
{
   template<typename... OutputStrings>
   static constexpr auto Generate(OutputStrings&&... args)
   {
      return FizzBuzzArray<count - 1>::Generate(
         FizzBuzzHelper<count>(),
         args...);
   }
};

template<>
struct FizzBuzzArray<0>
{
   template<typename... OutputStrings>
   static constexpr auto Generate(OutputStrings&&... args)
   {
      return std::array<std::string_view, sizeof...(OutputStrings)>
      {
         args...
      };
   }
};

template<unsigned end>
void FizzBuzz()
{
   auto output = FizzBuzzArray<end>::Generate();
   for (auto&& entry : output)
   {
      std::cout << entry << std::endl;
   }
}

int main()
{
   FizzBuzz<100>();
}
