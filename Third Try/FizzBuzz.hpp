#include <array>
#include <iostream>
#include <utility>

template <char... left, char... right>
constexpr auto concat(
    const std::integer_sequence<char, left...>,
    const std::integer_sequence<char, right...>)
{
    return std::integer_sequence<char, left..., right...>{};
}

template <char seperator, char... left, char... right>
constexpr auto concat(
    const std::integer_sequence<char, left...>,
    const std::integer_sequence<char, right...>)
{
    return std::integer_sequence<char, left..., seperator, right...>{};
}

template <bool, std::size_t value>
struct ConvertImpl
{
    static constexpr auto ToString()
    {
        return concat(
            ConvertImpl<value/10<10,value/10>::ToString(),
            std::integer_sequence<char,'0'+(value%10)>{});
    }
};

template <std::size_t value>
struct ConvertImpl<true, value>
{
    static constexpr auto ToString()
    {
        return std::integer_sequence<char, '0'+value>{};
    }
};

template <std::size_t value>
constexpr auto Convert()
{
    return ConvertImpl<value<10, value>::ToString();
}

template <std::size_t index, std::enable_if_t<index%3==0&&index%5==0, void*> = nullptr>
constexpr auto FizzBuzzHelper()
{
    return std::integer_sequence<char, 'F', 'i', 'z', 'z', 'B', 'u', 'z', 'z'>{};
}

template <std::size_t index, std::enable_if_t<index%3==0&&index%5!=0, void*> = nullptr>
constexpr auto FizzBuzzHelper()
{
    return std::integer_sequence<char, 'F', 'i', 'z', 'z'>{};
}

template <std::size_t index, std::enable_if_t<index%3!=0&&index%5==0, void*> = nullptr>
constexpr auto FizzBuzzHelper()
{
    return std::integer_sequence<char, 'B', 'u', 'z', 'z'>{};
}

template <std::size_t index, std::enable_if_t<index%3!=0&&index%5!=0, void*> = nullptr>
constexpr auto FizzBuzzHelper()
{
    return Convert<index>();
}

template <std::size_t index>
constexpr auto FizzBuzzImpl()
{
    return concat<'\n'>(FizzBuzzImpl<index-1>(), FizzBuzzHelper<index>());
}

template <>
constexpr auto FizzBuzzImpl<1>()
{
    return FizzBuzzHelper<1>();
}

template <char... string>
constexpr auto format(const std::integer_sequence<char, string...>&)
{
    return std::array<char, sizeof...(string)+1>{string...};
}

template <std::size_t index>
constexpr auto FizzBuzz()
{
    return format(FizzBuzzImpl<index>());
}