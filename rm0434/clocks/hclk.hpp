#pragma once

/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// soc
#include <rm0434/clocks/sources/hse.hpp>
#include <rm0434/clocks/sources/hsi16.hpp>
#include <rm0434/utils/tick_counter.hpp>
#include <rm0434/utils/wait_until.hpp>

// xmcu
#include <xmcu/Duration.hpp>
#include <xmcu/Non_copyable.hpp>
#include <xmcu/non_constructible.hpp>

// CMSIS
#include <stm32wbxx.h>

// std
#include <cstdint>
#include <cstdlib>

namespace xmcu::soc::st::arm::m4::wb::rm0434::clocks {
template<std::size_t id> class hclk : private non_constructible
{
private:
    constexpr static std::uint32_t dividers[] = { 1u, 3u, 5u, 1u,  1u,  6u,   10u,  32u,
                                                  2u, 4u, 8u, 16u, 64u, 128u, 256u, 512u };

    friend class hclk<1u>;
    friend class hclk<2u>;
    friend class hclk<4u>;
};

template<> class hclk<1u> : private non_constructible
{
public:
    enum class Prescaler : std::uint32_t
    {
        _1 = 0x0u,
        _3 = RCC_CFGR_HPRE_0,
        _5 = RCC_CFGR_HPRE_1,
        _6 = RCC_CFGR_HPRE_0 | RCC_CFGR_HPRE_2,
        _10 = RCC_CFGR_HPRE_1 | RCC_CFGR_HPRE_2,
        _32 = RCC_CFGR_HPRE_0 | RCC_CFGR_HPRE_1 | RCC_CFGR_HPRE_2,
        _2 = RCC_CFGR_HPRE_3,
        _4 = RCC_CFGR_HPRE_0 | RCC_CFGR_HPRE_3,
        _8 = RCC_CFGR_HPRE_1 | RCC_CFGR_HPRE_3,
        _16 = RCC_CFGR_HPRE_0 | RCC_CFGR_HPRE_1 | RCC_CFGR_HPRE_3,
        _64 = RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_3,
        _128 = RCC_CFGR_HPRE_0 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_3,
        _256 = RCC_CFGR_HPRE_1 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_3,
        _512 = RCC_CFGR_HPRE_0 | RCC_CFGR_HPRE_1 | RCC_CFGR_HPRE_2 | RCC_CFGR_HPRE_3
    };

    static void set(Prescaler a_prescaler)
    {
        bit::flag::set(&(RCC->CFGR), RCC_CFGR_HPRE, static_cast<std::uint32_t>(a_prescaler));
        utils::wait_until::all_bits_are_set(RCC->CFGR, RCC_CFGR_HPREF);
    }
    static bool set(Prescaler a_prescaler, Milliseconds a_timeout)
    {
        const std::uint64_t start = utils::tick_counter<Milliseconds>::get();

        bit::flag::set(&(RCC->CFGR), RCC_CFGR_HPRE, static_cast<std::uint32_t>(a_prescaler));
        return utils::wait_until::all_bits_are_set(
            RCC->CFGR, RCC_CFGR_HPREF, a_timeout.get() - (utils::tick_counter<Milliseconds>::get() - start));
    }

    static Prescaler get_prescaler()
    {
        return {}; // TODO: implement
    }
    static std::uint32_t get_frequency_Hz()
    {
        return SystemCoreClock /
               hclk<0>::dividers[bit::flag::get(RCC->CFGR, RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos]; // TODO: fixme
    }
};
template<> class hclk<2u> : private non_constructible
{
public:
    enum class Prescaler : std::uint32_t
    {
        _1 = 0x0u,
        _3 = RCC_EXTCFGR_C2HPRE_0,
        _5 = RCC_EXTCFGR_C2HPRE_1,
        _6 = RCC_EXTCFGR_C2HPRE_0 | RCC_EXTCFGR_C2HPRE_2,
        _10 = RCC_EXTCFGR_C2HPRE_1 | RCC_EXTCFGR_C2HPRE_2,
        _32 = RCC_EXTCFGR_C2HPRE_0 | RCC_EXTCFGR_C2HPRE_1 | RCC_EXTCFGR_C2HPRE_2,
        _2 = RCC_EXTCFGR_C2HPRE_3,
        _4 = RCC_EXTCFGR_C2HPRE_0 | RCC_EXTCFGR_C2HPRE_3,
        _8 = RCC_EXTCFGR_C2HPRE_1 | RCC_EXTCFGR_C2HPRE_3,
        _16 = RCC_EXTCFGR_C2HPRE_0 | RCC_EXTCFGR_C2HPRE_1 | RCC_EXTCFGR_C2HPRE_3,
        _64 = RCC_EXTCFGR_C2HPRE_2 | RCC_EXTCFGR_C2HPRE_3,
        _128 = RCC_EXTCFGR_C2HPRE_0 | RCC_EXTCFGR_C2HPRE_2 | RCC_EXTCFGR_C2HPRE_3,
        _256 = RCC_EXTCFGR_C2HPRE_1 | RCC_EXTCFGR_C2HPRE_2 | RCC_EXTCFGR_C2HPRE_3,
        _512 = RCC_EXTCFGR_C2HPRE_0 | RCC_EXTCFGR_C2HPRE_1 | RCC_EXTCFGR_C2HPRE_2 | RCC_EXTCFGR_C2HPRE_3
    };

    static void set(Prescaler a_prescaler)
    {
        bit::flag::set(&(RCC->EXTCFGR), RCC_EXTCFGR_C2HPRE, static_cast<std::uint32_t>(a_prescaler));
        utils::wait_until::all_bits_are_set(RCC->EXTCFGR, RCC_EXTCFGR_C2HPREF);
    }
    static bool set(Prescaler a_prescaler, Milliseconds a_timeout)
    {
        const std::uint64_t start = utils::tick_counter<Milliseconds>::get();

        bit::flag::set(&(RCC->EXTCFGR), RCC_EXTCFGR_C2HPRE, static_cast<std::uint32_t>(a_prescaler));
        return utils::wait_until::all_bits_are_set(
            RCC->EXTCFGR, RCC_EXTCFGR_C2HPREF, a_timeout.get() - (utils::tick_counter<Milliseconds>::get() - start));
    }

    static Prescaler get_prescaler()
    {
        return {}; // TODO: implement
    }
    static std::uint32_t get_frequency_Hz()
    {
        return SystemCoreClock / hclk<0>::dividers[bit::flag::get(RCC->EXTCFGR, RCC_EXTCFGR_C2HPRE) >>
                                                   RCC_EXTCFGR_C2HPRE_Pos]; // TODO: fixme
    }
};
template<> class hclk<4u> : private non_constructible
{
public:
    enum class Prescaler : std::uint32_t
    {
        _1 = 0x0u,
        _3 = RCC_EXTCFGR_SHDHPRE_0,
        _5 = RCC_EXTCFGR_SHDHPRE_1,
        _6 = RCC_EXTCFGR_SHDHPRE_0 | RCC_EXTCFGR_SHDHPRE_2,
        _10 = RCC_EXTCFGR_SHDHPRE_1 | RCC_EXTCFGR_SHDHPRE_2,
        _32 = RCC_EXTCFGR_SHDHPRE_0 | RCC_EXTCFGR_SHDHPRE_1 | RCC_EXTCFGR_SHDHPRE_2,
        _2 = RCC_EXTCFGR_SHDHPRE_3,
        _4 = RCC_EXTCFGR_SHDHPRE_0 | RCC_EXTCFGR_SHDHPRE_3,
        _8 = RCC_EXTCFGR_SHDHPRE_1 | RCC_EXTCFGR_SHDHPRE_3,
        _16 = RCC_EXTCFGR_SHDHPRE_0 | RCC_EXTCFGR_SHDHPRE_1 | RCC_EXTCFGR_SHDHPRE_3,
        _64 = RCC_EXTCFGR_SHDHPRE_2 | RCC_EXTCFGR_SHDHPRE_3,
        _128 = RCC_EXTCFGR_SHDHPRE_0 | RCC_EXTCFGR_SHDHPRE_2 | RCC_EXTCFGR_SHDHPRE_3,
        _256 = RCC_EXTCFGR_SHDHPRE_1 | RCC_EXTCFGR_SHDHPRE_2 | RCC_EXTCFGR_SHDHPRE_3,
        _512 = RCC_EXTCFGR_SHDHPRE_0 | RCC_EXTCFGR_SHDHPRE_1 | RCC_EXTCFGR_SHDHPRE_2 | RCC_EXTCFGR_SHDHPRE_3
    };

    static void set(Prescaler a_prescaler)
    {
        bit::flag::set(&(RCC->EXTCFGR), RCC_EXTCFGR_SHDHPRE, static_cast<std::uint32_t>(a_prescaler));
        utils::wait_until::all_bits_are_set(RCC->EXTCFGR, RCC_EXTCFGR_SHDHPREF);
    }
    static bool set(Prescaler a_prescaler, Milliseconds a_timeout)
    {
        const std::uint64_t start = utils::tick_counter<Milliseconds>::get();

        bit::flag::set(&(RCC->EXTCFGR), RCC_EXTCFGR_SHDHPRE, static_cast<std::uint32_t>(a_prescaler));
        return utils::wait_until::all_bits_are_set(
            RCC->EXTCFGR, RCC_EXTCFGR_SHDHPREF, a_timeout.get() - (utils::tick_counter<Milliseconds>::get() - start));
    }

    static Prescaler get_prescaler()
    {
        return {};
    }
    static std::uint32_t get_frequency_Hz()
    {
        return SystemCoreClock /
               hclk<0>::dividers[bit::flag::get(RCC->EXTCFGR, RCC_EXTCFGR_SHDHPRE) >> RCC_EXTCFGR_SHDHPRE_Pos];
    }
};
template<> class hclk<5u> : private non_constructible
{
public:
    template<typename Source_t> static void set() = delete;
    template<typename Source_t, sources::hse::Prescaler> static void set() = delete;

    static std::uint32_t get_frequency_Hz()
    {
        return 16_MHz;
    }
};

template<> inline void hclk<5u>::set<sources::hsi16>()
{
    bit::flag::clear(&(RCC->EXTCFGR), RCC_EXTCFGR_RFCSS);
}
template<> inline void hclk<5u>::set<sources::hse, sources::hse::Prescaler::_2>()
{
    bit::flag::set(&(RCC->EXTCFGR), RCC_EXTCFGR_RFCSS);
}
} // namespace xmcu::soc::st::arm::m4::wb::rm0434::clocks
