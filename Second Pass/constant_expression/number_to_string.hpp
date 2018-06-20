#pragma once

#include "string.hpp"

namespace constant_expression
{
   template<unsigned value>
   class number_to_string
   {
   public:
      constexpr static auto convert()
      {
         return number_to_string_impl<
               value < 10,
               value
            >::convert();
      }

   private:
      template<bool base_case, unsigned value>
      struct number_to_string_impl
      {
         constexpr static auto convert()
         {
            return number_to_string_impl<
                  value / 10 < 10,
                  value / 10
               >::convert() +
               string<1>{'0' + (value % 10)};
         }
      };

      template<unsigned value>
      struct number_to_string_impl<true, value>
      {
         constexpr static auto convert()
         {
            return string<1>{ '0' + value };
         }
      };
   };
}