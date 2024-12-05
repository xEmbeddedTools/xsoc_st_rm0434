#pragma once

/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// std
#include <cstdint>

// soc
#include <xmcu/soc/ST/arm/m4/wb/rm0434/config.hpp>

// xmcu
#include <xmcu/non_constructible.hpp>

namespace xmcu::soc::st::arm::m4::wb::rm0434::peripherals::ll {
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
};

#if defined(XMCU_GPIOA_PRESENT) && defined(XMCU_GPIOB_PRESENT)
constexpr bool operator==(gpio_base::A, gpio_base::B)
{
    return false;
}
#endif
#if defined(XMCU_GPIOA_PRESENT) && defined(XMCU_GPIOC_PRESENT)
constexpr bool operator==(gpio_base::A, gpio_base::C)
{
    return false;
}
#endif
#if defined(XMCU_GPIOA_PRESENT) && defined(XMCU_GPIOE_PRESENT)
constexpr bool operator==(gpio_base::A, gpio_base::E)
{
    return false;
}
#endif
#if defined(XMCU_GPIOA_PRESENT) && defined(XMCU_GPIOH_PRESENT)
constexpr bool operator==(gpio_base::A, gpio_base::H)
{
    return false;
}
#endif
#if defined(XMCU_GPIOB_PRESENT) && defined(XMCU_GPIOA_PRESENT)
constexpr bool operator==(gpio_base::B, gpio_base::A)
{
    return false;
}
#endif
#if defined(XMCU_GPIOB_PRESENT) && defined(XMCU_GPIOC_PRESENT)
constexpr bool operator==(gpio_base::B, gpio_base::C)
{
    return false;
}
#endif
#if defined(XMCU_GPIOB_PRESENT) && defined(XMCU_GPIOE_PRESENT)
constexpr bool operator==(gpio_base::B, gpio_base::E)
{
    return false;
}
#endif
#if defined(XMCU_GPIOB_PRESENT) && defined(XMCU_GPIOH_PRESENT)
constexpr bool operator==(gpio_base::B, gpio_base::H)
{
    return false;
}
#endif
#if defined(XMCU_GPIOC_PRESENT) && defined(XMCU_GPIOA_PRESENT)
constexpr bool operator==(gpio_base::C, gpio_base::A)
{
    return false;
}
#endif
#if defined(XMCU_GPIOC_PRESENT) && defined(XMCU_GPIOB_PRESENT)
constexpr bool operator==(gpio_base::C, gpio_base::B)
{
    return false;
}
#endif
#if defined(XMCU_GPIOC_PRESENT) && defined(XMCU_GPIOE_PRESENT)
constexpr bool operator==(gpio_base::C, gpio_base::E)
{
    return false;
}
#endif
#if defined(XMCU_GPIOC_PRESENT) && defined(XMCU_GPIOH_PRESENT)
constexpr bool operator==(gpio_base::C, gpio_base::H)
{
    return false;
}
#endif
#if defined(XMCU_GPIOE_PRESENT) && defined(XMCU_GPIOA_PRESENT)
constexpr bool operator==(gpio_base::E, gpio_base::A)
{
    return false;
}
#endif
#if defined(XMCU_GPIOE_PRESENT) && defined(XMCU_GPIOB_PRESENT)
constexpr bool operator==(gpio_base::E, gpio_base::B)
{
    return false;
}
#endif
#if defined(XMCU_GPIOE_PRESENT) && defined(XMCU_GPIOC_PRESENT)
constexpr bool operator==(gpio_base::E, gpio_base::C)
{
    return false;
}
#endif
#if defined(XMCU_GPIOE_PRESENT) && defined(XMCU_GPIOH_PRESENT)
constexpr bool operator==(gpio_base::E, gpio_base::H)
{
    return false;
}
#endif
#if defined(XMCU_GPIOH_PRESENT) && defined(XMCU_GPIOA_PRESENT)
constexpr bool operator==(gpio_base::H, gpio_base::A)
{
    return false;
}
#endif
#if defined(XMCU_GPIOH_PRESENT) && defined(XMCU_GPIOB_PRESENT)
constexpr bool operator==(gpio_base::H, gpio_base::B)
{
    return false;
}
#endif
#if defined(XMCU_GPIOH_PRESENT) && defined(XMCU_GPIOC_PRESENT)
constexpr bool operator==(gpio_base::H, gpio_base::C)
{
    return false;
}
#endif
#if defined(XMCU_GPIOH_PRESENT) && defined(XMCU_GPIOE_PRESENT)
constexpr bool operator==(gpio_base::H, gpio_base::E)
{
    return false;
}
#endif
} // namespace xmcu::soc::st::arm::m4::wb::rm0434::peripherals::ll