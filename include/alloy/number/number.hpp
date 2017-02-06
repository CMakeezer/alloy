// Copyright Bruno Dutra 2016-2017
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE.txt or copy at http://boost.org/LICENSE_1_0.txt

#ifndef ALLOY_NUMBER_NUMBER_HPP
#define ALLOY_NUMBER_NUMBER_HPP

#include <alloy/config.hpp>

#include <type_traits>

namespace alloy {
    template<auto I>
    using number = std::integral_constant<decltype(I), I>;
}

#endif
