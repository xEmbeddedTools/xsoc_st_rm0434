#pragma once

/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// soc
#include <xmcu/soc/ST/arm/m4/wb/rm0434/utils/tick_counter.hpp>
#include <xmcu/soc/ST/arm/m4/wb/rm0434/utils/wait_until.hpp>

// xmcu
#include <xmcu/Duration.hpp>
#include <xmcu/bit.hpp>
#include <xmcu/non_constructible.hpp>

// CMSIS
#include <stm32wbxx.h>

// std
#include <cstdint>
#include <cstdlib>

namespace xmcu::soc::st::arm::m4::wb::rm0434::clocks {
template<std::size_t id> class pclk : private non_constructible
{
private:
    constexpr static std::uint32_t dividers[] = { 2u, 4u, 8u, 16u };

    friend class pclk<1u>;
    friend class pclk<2u>;
};

template<> class pclk<1u> : private non_constructible
{
public:
    enum class Prescaler : std::uint32_t
    {
        _1 = 0x0u,
        _2 = RCC_CFGR_PPRE1_2,
        _4 = RCC_CFGR_PPRE1_0 | RCC_CFGR_PPRE1_2,
        _8 = RCC_CFGR_PPRE1_1 | RCC_CFGR_PPRE1_2,
        _16 = RCC_CFGR_PPRE1_0 | RCC_CFGR_PPRE1_1 | RCC_CFGR_PPRE1_2,
    };

    static void set(Prescaler a_prescaler)
    {
        bit::flag::set(&(RCC->CFGR), RCC_CFGR_PPRE1, static_cast<std::uint32_t>(a_prescaler));
        utils::wait_until::all_bits_are_set(RCC->CFGR, RCC_CFGR_PPRE1F);
    }
    static bool set(Prescaler a_prescaler, Milliseconds a_timeout)
    {
        const std::uint64_t start = utils::tick_counter<Milliseconds>::get();

        bit::flag::set(&(RCC->CFGR), RCC_CFGR_PPRE1, static_cast<std::uint32_t>(a_prescaler));
        return utils::wait_until::all_bits_are_set(
            RCC->CFGR, RCC_CFGR_PPRE1F, a_timeout.get() - (utils::tick_counter<Milliseconds>::get() - start));
    }

    static Prescaler get_Prescaler()
    {
        return {}; // TODO: implement
    }
    static std::uint32_t get_frequency_Hz() // TODO: fixme
    {
        std::uint32_t index = bit::flag::get(RCC->CFGR, RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos;

        if (index >= 4)
        {
            return SystemCoreClock / pclk<0u>::dividers[index - 4];
        }

        return SystemCoreClock;
    }
    static std::uint32_t get_Tim_frequency_Hz() // TODO: ??
    {
        std::uint32_t index = bit::flag::get(RCC->CFGR, RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos;

        if (index >= 4)
        {
            return SystemCoreClock * 2 / pclk<0u>::dividers[index - 4];
        }

        return SystemCoreClock;
    }
};
template<> class pclk<2u> : private non_constructible
{
public:
    enum class Prescaler : std::uint32_t
    {
        _1 = 0x0u,
        _2 = RCC_CFGR_PPRE2_2,
        _4 = RCC_CFGR_PPRE2_0 | RCC_CFGR_PPRE2_2,
        _8 = RCC_CFGR_PPRE2_1 | RCC_CFGR_PPRE2_2,
        _16 = RCC_CFGR_PPRE2_0 | RCC_CFGR_PPRE2_1 | RCC_CFGR_PPRE2_2,
    };

    static void set(Prescaler a_prescaler)
    {
        bit::flag::set(&(RCC->CFGR), RCC_CFGR_PPRE2, static_cast<std::uint32_t>(a_prescaler));
        utils::wait_until::all_bits_are_set(RCC->CFGR, RCC_CFGR_PPRE2F);
    }
    static bool set(Prescaler a_prescaler, Milliseconds a_timeout)
    {
        const std::uint64_t start = utils::tick_counter<Milliseconds>::get();

        bit::flag::set(&(RCC->CFGR), RCC_CFGR_PPRE2, static_cast<std::uint32_t>(a_prescaler));
        return utils::wait_until::all_bits_are_set(
            RCC->CFGR, RCC_CFGR_PPRE2F, a_timeout.get() - (utils::tick_counter<Milliseconds>::get() - start));
    }

    static Prescaler get_Prescaler()
    {
        return {}; // TODO: implement
    }
    static std::uint32_t get_frequency_Hz() // TODO: fixme
    {
        std::uint32_t index = bit::flag::get(RCC->CFGR, RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos;

        if (index >= 4)
        {
            return SystemCoreClock / pclk<0u>::dividers[index - 4];
        }

        return SystemCoreClock;
    }
    static std::uint32_t get_Tim_frequency_Hz() // TODO: ??
    {
        std::uint32_t index = bit::flag::get(RCC->CFGR, RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos;

        if (index >= 4)
        {
            return SystemCoreClock * 2 / pclk<0u>::dividers[index - 4];
        }

        return SystemCoreClock;
    }
};
} // namespace xmcu::soc::st::arm::m4::wb::rm0434::clocks