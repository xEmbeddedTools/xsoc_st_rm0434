#pragma once

/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// std
#include <cstdint>

// xmcu
#include <xmcu/non_constructible.hpp>

namespace xmcu {
namespace soc {
namespace m4 {
namespace stm32wb {
namespace rm0434 {
namespace peripherals {
namespace ll {

#if XMCU_SOC_STM32_MODEL == STM32WB35CEU6A
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
        _14,
        _15
    };
    enum class E : std::uint8_t
    {
        _4,
    };
    enum class H : std::uint8_t
    {
        _3,
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

} // namespace ll
} // namespace peripherals
} // namespace rm0434
} // namespace stm32wb
} // namespace m4
} // namespace soc
} // namespace xmcu