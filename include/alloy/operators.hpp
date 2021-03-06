#ifndef ALLOY_OPERATORS_HPP
#define ALLOY_OPERATORS_HPP

#include "config.hpp"
#include "detail.hpp"
#include "filter/model.hpp"
#include "sink/model.hpp"
#include "source/model.hpp"

namespace alloy::detail {
    template<typename F,
        typename G,
        requires<instanceof <F, filter>> = valid,
        requires<instanceof <G, filter>> = valid>
    constexpr decltype(auto) operator>>(F&& f, G&& g) noexcept {
        return filter{[&f, &g](auto&& snk) -> decltype(auto) {
            return static_cast<F&&>(f)
                >> (static_cast<G&&>(g) >> static_cast<decltype(snk)>(snk));
        }};
    }

    template<typename F,
        typename Src,
        requires<! instanceof <Src, filter>> = valid,
        requires<instanceof <F, filter>> = valid>
    constexpr decltype(auto) operator>>(Src&& src, F&& f) noexcept {
        return source{[&src, &f](auto&& snk) -> decltype(auto) {
            return static_cast<Src&&>(src)
                >> (static_cast<F&&>(f) >> static_cast<decltype(snk)>(snk));
        }};
    }

    template<typename Snk,
        typename F,
        requires<instanceof <F, filter>> = valid,
        requires<! instanceof <Snk, filter>> = valid>
    constexpr decltype(auto) operator>>(F&& f, Snk&& snk) {
        return sink{invoke(static_cast<F&&>(f), static_cast<Snk&&>(snk))};
    }

    template<typename Snk,
        typename Src,
        requires<! instanceof <Src, filter>> = valid,
        requires<! instanceof <Snk, filter>> = valid,
        requires<instanceof <Src, source> || instanceof <Snk, sink>> = valid>
    constexpr decltype(auto) operator>>(Src&& src, Snk&& snk) {
        return invoke(static_cast<Src&&>(src), static_cast<Snk&&>(snk));
    }
}

#endif
