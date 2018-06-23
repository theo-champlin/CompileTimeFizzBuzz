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
      typename ConvertToStringHelper<
         value < 10,
         value
      >::type;
};

template<unsigned current>
constexpr std::string_view FizzBuzzHelper()
{
   if constexpr (!(current % 3) && !(current % 5))
   {
      return { "FizzBuzz" };
   }
   else if constexpr (!(current % 3))
   {
      return { "Fizz" };
   }
   else if constexpr (!(current % 5))
   {
      return { "Buzz" };
   }
   else
   {
      using converted = typename ConvertToString<current>::type;
      return
      {
         boost::mpl::c_str<converted>::type::value,
         boost::mpl::size<converted>::value
      };
   }

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
constexpr auto FizzBuzz()
{
   return FizzBuzzArray<end>::Generate();
}