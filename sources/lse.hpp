#pragma once

/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// external
#pragma GCC diagnostic ignored "-Wvolatile"
#include <stm32wbxx.h>
#pragma GCC diagnostic pop

// xmcu
#include <xmcu/Duration.hpp>
#include <xmcu/bit.hpp>
#include <xmcu/non_constructible.hpp>

namespace xmcu {
namespace soc {
namespace m4 {
namespace stm32wb {
namespace rm0434 {
namespace sources {
class lse : private non_constructible
{
public:
    struct xtal : private non_constructible
    {
        enum class Drive : std::uint32_t
        {
            low = 0x0u,
            medium_low = RCC_BDCR_LSEDRV_0,
            medium_high = RCC_BDCR_LSEDRV_1,
            high = RCC_BDCR_LSEDRV_0 | RCC_BDCR_LSEDRV_1
        };

        static void enable(Drive a_drive_config);
        static bool enable(Drive a_drive_config, Milliseconds a_timeout);
    };

    struct bypass : private non_constructible
    {
        static void enable();
        static bool enable(Milliseconds a_timeout);
    };

    static void disable();
    static bool disable(Milliseconds a_timeout);

    static bool is_enabled()
    {
        return bit::flag::is(RCC->BDCR, RCC_BDCR_LSERDY);
    }

    static std::uint32_t get_frequency_Hz()
    {
        if (true == is_enabled())
        {
            return 32768u;
        }

        return 0u;
    }
};
} // namespace sources
} // namespace rm0434
} // namespace stm32wb
} // namespace m4
} // namespace soc
} // namespace xmcu