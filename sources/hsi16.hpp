#pragma once

/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// xmcu
#include <xmcu/Duration.hpp>
#include <xmcu/Frequency.hpp>
#include <xmcu/bit.hpp>
#include <xmcu/non_constructible.hpp>

namespace xmcu {
namespace soc {
namespace m4 {
namespace stm32wb {
namespace sources {
class hsi16 : private non_constructible
{
public:
    static void enable();
    static bool enable(Milliseconds a_timeout);

    static void disable();
    static bool disable(Milliseconds a_timeout);

    static bool is_enabled()
    {
        return bit::flag::is(RCC->CR, RCC_CR_HSIRDY);
    }

    static std::uint32_t get_frequency_Hz()
    {
        if (true == is_enabled())
        {
            return 16_MHz;
        }

        return 0u;
    }
};
} // namespace sources
} // namespace stm32wb
} // namespace m4
} // namespace soc
} // namespace xmcu
