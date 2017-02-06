// Copyright Bruno Dutra 2016-2017
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE.txt or copy at http://boost.org/LICENSE_1_0.txt

#ifndef ALLOY_DETAIL_OBJECT_HPP
#define ALLOY_DETAIL_OBJECT_HPP

#include <alloy/config.hpp>

#include <alloy/detail/traits.hpp>

#include <cstddef>

namespace alloy::detail {
    template<std::size_t I, typename X,
        bool = std::is_empty<X>::value && !std::is_final<X>::value
    >
    struct prop {
        X x;

        constexpr prop() = default;
        constexpr prop(prop&&) = default;
        constexpr prop(prop const&) = default;

        constexpr prop(X const& x)
            noexcept(noexcept(X(x)))
            : x(x)
        {}

        template<typename Y>
        constexpr prop(Y&& y)
            noexcept(noexcept(X(static_cast<Y&&>(y))))
            : x(static_cast<Y&&>(y))
        {}

        constexpr operator transfer<prop&, X>() & noexcept {
            return static_cast<transfer<prop&, X>>(x);
        }

        constexpr operator transfer<prop const&, X>() const& noexcept {
            return static_cast<transfer<prop const&, X>>(x);
        }

        constexpr operator transfer<prop&&, X>() && noexcept {
            return static_cast<transfer<prop&&, X>>(x);
        }

        constexpr operator transfer<prop const&&, X>() const&& noexcept {
            return static_cast<transfer<prop const&&, X>>(x);
        }
    };

    template<std::size_t I, typename X>
    struct prop<I, X, true> : X {
        constexpr prop() = default;
        constexpr prop(prop&&) = default;
        constexpr prop(prop const&) = default;

        constexpr prop(X const& x)
            noexcept(noexcept(X(x)))
            : X(x)
        {}

        template<typename Y>
        constexpr prop(Y&& y)
            noexcept(noexcept(X(static_cast<Y&&>(y))))
            : X(static_cast<Y&&>(y))
        {}
    };

    template<typename... Props>
    struct object;

    template<auto... Is, typename... Xs>
    struct object<prop<Is, Xs>...> : prop<Is, Xs>... {
        constexpr object() = default;
        constexpr object(object&&) = default;
        constexpr object(object const&) = default;

        constexpr object(Xs const&... xs)
            noexcept((... && noexcept(prop<Is, Xs>(xs))))
            : prop<Is, Xs>(xs)...
        {}

        template<typename... Ys>
        constexpr object(Ys&&... ys)
            noexcept((... && noexcept(prop<Is, Xs>(static_cast<Ys&&>(ys)))))
            : prop<Is, Xs>(static_cast<Ys&&>(ys))...
        {}
    };

    template<>
    struct object<> {
        constexpr object() = default;
        constexpr object(object&&) = default;
        constexpr object(object const&) = default;
    };
}

#endif