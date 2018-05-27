#ifndef ALLOY_VENDOR_HPP
#define ALLOY_VENDOR_HPP

#if !defined(METAL_VERSION)
#include "vendor/metal/metal.hpp"
#endif

#if METAL_VERSION < METAL_SEMVER(0, 7, 0)
#error Unsuported Metal version
#endif

#endif
