#include <alloy.hpp>

#include "test.hpp"

template<auto X, auto Y, auto Z>
struct matrix {
    constexpr matrix() {
        decltype(auto) x = value<X, Y, Z>();
        decltype(auto) y = value<Z, X, Y>();
        decltype(auto) z = value<Y, Z, X>();

        static_assert(alloy::capture() >> expect());
        static_assert(alloy::capture(FWD(x)) >> expect(FWD(x)));
        static_assert(alloy::capture(FWD(x), FWD(y)) >> expect(FWD(x), FWD(y)));
        static_assert(alloy::capture(FWD(x), FWD(y), FWD(z)) >> expect(FWD(x), FWD(y), FWD(z)));
    }
};

int main() {
    return test<matrix>;
}
