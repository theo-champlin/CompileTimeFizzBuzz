#pragma once

#include <cstddef>
#include <iterator>
#include <initializer_list>
#include <stdexcept>
#include <type_traits>

namespace constant_expression
{
   template<std::size_t length>
   class string
   {
      char m_data[length + 1];

   public:
      using size_type = std::size_t;
      using reference = char&;
      using const_reference = const char&;
      using pointer = char*;
      using const_pointer = const char*;
      using iterator = pointer;
      using const_iterator = const_pointer;
      using reverse_iterator = std::reverse_iterator<iterator>;
      using const_reverse_iterator = std::reverse_iterator<const_iterator>;

      explicit constexpr string(char c)
         : m_data{}
      {
         fill(c);
      }

      explicit constexpr string(const char(&literal)[length + 1])
         : m_data{}
      {
         copy(literal, literal + length);
      }

      constexpr string(const char* other, size_type count)
         : m_data{}
      {
         copy(other, other + count);
      }

      template<size_type other_length>
      constexpr string(const string<other_length>& other)
         : string{ other.m_data, other_length }
      {
      }

      template<size_type left_length>
      constexpr string(
         const string<left_length>& left,
         const string<length - left_length>& right)
         :
         m_data{}
      {
         copy(std::begin(left), std::end(left));
         copy(std::begin(right), std::end(right), left_length);
      }

      explicit constexpr string(std::initializer_list<char> input)
         : m_data{}
      {
         if (std::size(input) == 1)
         {
            fill(*input.begin());
            return;
         }

         copy(std::begin(input), std::end(input));
      }

      template <
         typename string_type,
         typename = std::enable_if_t<std::is_convertible_v<string_type, std::string_view>>>
      constexpr string(const string_type& other)
         : m_data{}
      {
         const auto other_view = static_cast<const std::string_view>(other);
         copy(std::begin(other_view), std::end(other_view));
      }

      constexpr string<length>& operator=(char c) noexcept
      {
         fill(c);
         return *this;
      }

      constexpr string<length>& operator=(const char(&literal)[length + 1])
      {
         copy(&literal, (&literal) + length);
         return *this;
      }

      template<size_type other_length>
      constexpr string<length>& operator=(const string<other_length>& other) noexcept
      {
         copy(std::begin(other), std::end(other));
         return *this;
      }

      constexpr string<length>& operator=(std::initializer_list<char> input) noexcept
      {
         copy(std::begin(input), std::end(input));
         return *this;
      }

      constexpr char at(size_type index) const
      {
         return m_data[index];
      }

      constexpr reference at(size_type index)
      {
         return m_data[index];
      }

      constexpr char operator[](size_type index) const
      {
         return m_data[index];
      }

      constexpr reference operator[](size_type index)
      {
         return m_data[index];
      }

      constexpr char front() const noexcept
      {
         return m_data[0];
      }

      constexpr reference front() noexcept
      {
         return m_data[0];
      }

      constexpr char back() const noexcept
      {
         return m_data[length - 1];
      }

      constexpr reference back() noexcept
      {
         return m_data[length - 1];
      }

      constexpr const_iterator begin() const noexcept
      {
         return m_data;
      }

      constexpr iterator begin() noexcept
      {
         return m_data;
      }

      constexpr const_iterator end() const noexcept
      {
         return m_data + length;
      }

      constexpr iterator end() noexcept
      {
         return m_data + length;
      }

      constexpr const_reverse_iterator rbegin() const
      {
         return const_reverse_iterator{ end() };
      }

      constexpr reverse_iterator rbegin()
      {
         return reverse_iterator{ end() };
      }

      constexpr const_reverse_iterator rend() const
      {
         return const_reverse_iterator{ begin() };
      }

      constexpr reverse_iterator rend()
      {
         return reverse_iterator{ begin() };
      }

      constexpr const_pointer data() const noexcept
      {
         return m_data;
      }

      constexpr pointer data() noexcept
      {
         return m_data;
      }

      constexpr const_pointer c_str() const noexcept
      {
         return m_data;
      }

      constexpr bool empty() const noexcept
      {
         return !length;
      }

      constexpr size_type size() const
      {
         return length;
      }

      explicit constexpr operator const_pointer() const noexcept
      {
         return m_data;
      }

      explicit constexpr operator std::string_view() const
      {
         return std::string_view{ m_data, length };
      }

      constexpr bool starts_with(char c) const noexcept
      {
         return front() == c;
      }

      constexpr bool starts_with(const char* prefix, size_type count) const
      {
         if (length < count)
         {
            return false;
         }

         for (size_type index = 0; index < count; ++index)
         {
            if (*(prefix + index) != m_data[index])
            {
               return false;
            }
         }

         return true;
      }

      constexpr bool ends_with(char c) const noexcept
      {
         return back() == c;
      }

      constexpr bool ends_with(const char* prefix, size_type count) const
      {
         if (length < count)
         {
            return false;
         }

         for (size_type index = 0; index < count; ++index)
         {
            if (*(prefix + index) != m_data[length - count + index])
            {
               return false;
            }
         }

         return true;
      }

      template<typename input_iterator>
      constexpr void copy(input_iterator first, input_iterator last, size_type start = 0)
      {
         if (first > last)
         {
            throw std::invalid_argument{ "Argument is out of range" };
         }

         const auto input_length = static_cast<size_type>(last - first);
         const auto count = length > input_length ? input_length : length;
         for (size_type index = 0; index < count; ++index)
         {
            m_data[index + start] = *(first + index);
         }
      }

      constexpr void fill(char c)
      {
         for (size_type index = 0; index < length; ++index)
         {
            m_data[index] = c;
         }
      }
   };

   template<>
   class string<0>
   {
      string() = delete;
   };

   template<std::size_t length>
   constexpr auto literal_to_string(const char(&literal)[length])
   {
      return string<length - 1>{ literal };
   }
}

template<std::size_t left_length, std::size_t right_length>
constexpr auto operator+(
   const constant_expression::string<left_length>& left,
   const constant_expression::string<right_length>& right)
{
   return constant_expression::string<left_length + right_length>{ left, right };
}