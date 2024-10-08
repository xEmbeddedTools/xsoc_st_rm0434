#pragma once

/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// std
#include <cstdint>

// xmcu
#include <xmcu/non_constructible.hpp>

#define XMCU_SOC_STM32WB35CEU6A 1876651536769855465

namespace xmcu::soc::m4::stm32wb::rm0434::peripherals::ll {
#if (XMCU_SOC_MODEL == XMCU_SOC_STM32WB35CEU6A)
#define XMCU_GPIOA_PRESENT
#define XMCU_GPIOB_PRESENT
#define XMCU_GPIOC_PRESENT
#define XMCU_GPIOE_PRESENT
#define XMCU_GPIOH_PRESENT

struct gpio_base : private non_constructible
{
public:
    enum class A : std::uint8_t
    {
        _0,
        _1,
        _2,
        _3,
        _4,
        _5,
        _6,
        _7,
        _8,
        _9,
        _10,
        _11,
        _12,
        _13,
        _14,
        _15
    };
    enum class B : std::uint8_t
    {
        _0,
        _1,
        _2,
        _3,
        _4,
        _5,
        _6,
        _7,
        _8,
        _9,
    };
    enum class C : std::uint8_t
    {
        _14_OSC32_IN,
        _15_OSC32_OUT
    };
    enum class E : std::uint8_t
    {
        _4,
    };
    enum class H : std::uint8_t
    {
        _3_BOOT0,
    };

public:
    friend constexpr bool operator==(gpio_base::A, gpio_base::B)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::A, gpio_base::C)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::A, gpio_base::E)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::A, gpio_base::H)
    {
        return false;
    }

    friend constexpr bool operator==(gpio_base::B, gpio_base::A)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::B, gpio_base::C)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::B, gpio_base::E)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::B, gpio_base::H)
    {
        return false;
    }

    friend constexpr bool operator==(gpio_base::C, gpio_base::A)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::C, gpio_base::B)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::C, gpio_base::E)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::C, gpio_base::H)
    {
        return false;
    }

    friend constexpr bool operator==(gpio_base::E, gpio_base::A)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::E, gpio_base::B)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::E, gpio_base::C)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::E, gpio_base::H)
    {
        return false;
    }

    friend constexpr bool operator==(gpio_base::H, gpio_base::A)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::H, gpio_base::B)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::H, gpio_base::C)
    {
        return false;
    }
    friend constexpr bool operator==(gpio_base::H, gpio_base::E)
    {
        return false;
    }
};
#endif
} // namespace xmcu::soc::m4::stm32wb::rm0434::peripherals::ll