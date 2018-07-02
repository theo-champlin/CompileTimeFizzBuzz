#include <array>
#include <boost/mpl/string.hpp>
#include <string_view>

// Remove the last digit and convert the removed digit to a characted. Recursively
// call to convert all the digits, appending the current converted digit to the end.
// Base case occurs when there is only one remaining digit (value < 10).
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
constexpr auto FizzBuzzHelper() -> std::string_view
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
      // Create a string_view from the string conversion. boost::mpl::c_str
      // detects the value of the converted string type at compile time and
      // boost::mpl::size detects the size. We need to pass in the size because
      // several compilers have still not implemented strlen of string literals
      // at compile time.
      using converted = typename ConvertToString<current>::type;
      return
      {
         boost::mpl::c_str<converted>::type::value,
         boost::mpl::size<converted>::value
      };
   }

}

// Run FizzBuzz on each value from the max down to 1. The result is added to
// the parameter pack and passed to the recursive call.
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

// Insert all results into an array. This is then passed back up the recursive chain.
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
