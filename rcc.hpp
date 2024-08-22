#pragma once

/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// std
#include <cstddef>
#include <cstdint>
#include <limits>

// xmcu
#include <xmcu/non_constructible.hpp>

namespace xmcu {
namespace soc {
namespace m4 {
namespace stm32wb {
template<typename Periph_t, std::uint32_t id = std::numeric_limits<std::uint32_t>::max()> class rcc
    : private xmcu::non_constructible
{
};
} // namespace stm32wb
} // namespace m4
} // namespace soc
} // namespace xmcu