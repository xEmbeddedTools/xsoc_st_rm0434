#pragma once

/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// externals
#pragma GCC diagnostic ignored "-Wvolatile"
#include <stm32wbxx.h>
#pragma GCC diagnostic pop

// xmcu
#include <xmcu/bit.hpp>
#include <xmcu/Duration.hpp>
#include <xmcu/non_constructible.hpp>
#include <xmcu/Frequency.hpp>

namespace xmcu {
namespace soc {
namespace m4 {
namespace wb {
namespace rm0434 {
namespace sources {
class hsi48 : private non_constructible
{
public:
    static void enable();
    static bool enable(Milliseconds a_timeout);

    static void disable();
    static bool disable(Milliseconds a_timeout);

    static bool is_enabled()
    {
        return bit::flag::is(RCC->CRRCR, RCC_CRRCR_HSI48RDY);
    }

    static std::uint32_t get_frequency_Hz()
    {
        if (true == is_enabled())
        {
            return 48_MHz;
        }

        return 0u;
    }
};
} // namespace sources
} // namespace rm0434
} // namespace wb
} // namespace m4
} // namespace soc
} // namespace xmcu