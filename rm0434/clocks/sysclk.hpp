#pragma once

/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// soc
#include <rm0434/clocks/sources/hse.hpp>
#include <rm0434/clocks/sources/hsi16.hpp>
#include <rm0434/clocks/sources/lse.hpp>
#include <rm0434/clocks/sources/msi.hpp>
#include <rm0434/clocks/sources/pll.hpp>
#include <rm0434/utils/wait_until.hpp>

// xmcu
#include <xmcu/Duration.hpp>
#include <xmcu/assertion.hpp>
#include <xmcu/non_constructible.hpp>

// std
#include <cstdlib>

namespace xmcu::soc::st::arm::m4::wb::rm0434::clocks {
template<std::size_t id> class sysclk : private non_constructible
{
};

template<> class sysclk<1u> : private non_constructible
{
public:
    template<typename Source_t> static void set_source() = delete;
    template<typename Source_t> static bool set_source(Milliseconds a_timeout) = delete;

    template<typename Source_t, auto prescaler> static void set_source() = delete;
    template<typename Source_t, auto prescaler> static bool set_source(Milliseconds a_timeout) = delete;

    template<typename Source_t> static bool is_source() = delete;
    static std::uint32_t get_frequency_Hz()
    {
        return SystemCoreClock;
    }

    template<typename Source_t> static void set_wakeup_source() = delete;
};

template<> class sysclk<2u> : private non_constructible
{
public:
    template<typename Source> static void set_wakeup_source() = delete;
};

template<> inline void sysclk<1u>::set_source<sources::msi>()
{
    hkm_assert(true == sources::msi::is_enabled());

    bit::flag::clear(&(RCC->CFGR), RCC_CFGR_SW);
    utils::wait_until::all_bits_are_cleared(RCC->CFGR, RCC_CFGR_SWS);

    SystemCoreClock = sources::msi::get_frequency_Hz();
}
template<> inline bool sysclk<1u>::set_source<sources::msi>(Milliseconds a_timeout)
{
    hkm_assert(true == sources::msi::is_enabled());

    const std::uint64_t start = utils::tick_counter<Milliseconds>::get();

    bit::flag::clear(&(RCC->CFGR), RCC_CFGR_SW);
    if (true == utils::wait_until::all_bits_are_cleared(
                    RCC->CFGR, RCC_CFGR_SWS, a_timeout.get() - (utils::tick_counter<Milliseconds>::get() - start)))
    {
        SystemCoreClock = sources::msi::get_frequency_Hz();
        return true;
    }

    return false;
}
template<> inline bool sysclk<1u>::is_source<sources::msi>()
{
    return false == bit::flag::is(RCC->CFGR, RCC_CFGR_SWS);
}

template<> inline void sysclk<1u>::set_source<sources::hsi16>()
{
    hkm_assert(true == sources::hsi16::is_enabled());

    bit::flag::set(&(RCC->CFGR), RCC_CFGR_SW, RCC_CFGR_SW_0);
    utils::wait_until::all_bits_are_set(RCC->CFGR, RCC_CFGR_SWS_0);

    SystemCoreClock = sources::hsi16::get_frequency_Hz();
}
template<> inline bool sysclk<1u>::set_source<sources::hsi16>(Milliseconds a_timeout)
{
    hkm_assert(true == sources::hsi16::is_enabled());

    const std::uint64_t start = utils::tick_counter<Milliseconds>::get();

    bit::flag::set(&(RCC->CFGR), RCC_CFGR_SW, RCC_CFGR_SW_0);
    if (true == utils::wait_until::all_bits_are_set(
                    RCC->CFGR, RCC_CFGR_SWS_0, a_timeout.get() - (utils::tick_counter<Milliseconds>::get() - start)))
    {
        SystemCoreClock = sources::hsi16::get_frequency_Hz();
        return true;
    }

    return false;
}
template<> inline bool sysclk<1u>::is_source<sources::hsi16>()
{
    return RCC_CFGR_SWS_0 == bit::flag::get(RCC->CFGR, RCC_CFGR_SWS);
}

template<> inline void sysclk<1u>::set_source<sources::pll>()
{
    hkm_assert(true == sources::pll::is_enabled());
    hkm_assert(sources::pll::r::Enable_config::Output::enabled == sources::pll::r::get_Enable_config().output);

    bit::flag::set(&(RCC->CFGR), RCC_CFGR_SW_0 | RCC_CFGR_SW_1);
    utils::wait_until::all_bits_are_set(RCC->CFGR, RCC_CFGR_SWS_0 | RCC_CFGR_SWS_1);

    SystemCoreClock = sources::pll::r::get_frequency_Hz();
}
template<> inline bool sysclk<1u>::set_source<sources::pll>(Milliseconds a_timeout)
{
    hkm_assert(true == sources::pll::is_enabled() &&
               sources::pll::p::Enable_config::Output::enabled == sources::pll::p::get_Enable_config().output);

    const std::uint64_t start = utils::tick_counter<Milliseconds>::get();

    bit::flag::set(&(RCC->CFGR), RCC_CFGR_SW, RCC_CFGR_SW_0 | RCC_CFGR_SW_1);
    if (true ==
        utils::wait_until::all_bits_are_set(RCC->CFGR,
                                            RCC_CFGR_SWS_0 | RCC_CFGR_SWS_1,
                                            a_timeout.get() - (utils::tick_counter<Milliseconds>::get() - start)))
    {
        SystemCoreClock = sources::pll::r::get_frequency_Hz();
        return true;
    }

    return false;
}
template<> inline bool sysclk<1u>::is_source<sources::pll>()
{
    return true == bit::flag::is(RCC->CFGR, RCC_CFGR_SWS);
}

template<> inline void sysclk<1u>::set_source<sources::hse, sources::hse::Prescaler::_1>()
{
    hkm_assert(true == sources::hse::is_enabled());

    bit::flag::clear(&(RCC->CR), RCC_CR_HSEPRE);
    bit::flag::set(&(RCC->CFGR), RCC_CFGR_SW, RCC_CFGR_SW_1);
    utils::wait_until::all_bits_are_set(RCC->CFGR, RCC_CFGR_SWS_1);

    SystemCoreClock = sources::hse::get_frequency_Hz();
}
template<> inline void sysclk<1u>::set_source<sources::hse, sources::hse::Prescaler::_2>()
{
    hkm_assert(true == sources::hse::is_enabled());

    bit::flag::set(&(RCC->CR), RCC_CR_HSEPRE);
    bit::flag::set(&(RCC->CFGR), RCC_CFGR_SW, RCC_CFGR_SW_1);
    utils::wait_until::all_bits_are_set(RCC->CFGR, RCC_CFGR_SWS_1);

    SystemCoreClock = sources::hse::get_frequency_Hz() / 2u;
}
template<> inline bool sysclk<1u>::set_source<sources::hse, sources::hse::Prescaler::_1>(Milliseconds a_timeout)
{
    hkm_assert(true == sources::hse::is_enabled());

    const std::uint64_t start = utils::tick_counter<Milliseconds>::get();

    bit::flag::clear(&(RCC->CR), RCC_CR_HSEPRE);
    bit::flag::set(&(RCC->CFGR), RCC_CFGR_SW, RCC_CFGR_SW_1);
    if (true == utils::wait_until::all_bits_are_set(
                    RCC->CFGR, RCC_CFGR_SWS_1, a_timeout.get() - (utils::tick_counter<Milliseconds>::get() - start)))
    {
        SystemCoreClock = sources::hse::get_frequency_Hz();
        return true;
    }

    return false;
}
template<> inline bool sysclk<1u>::set_source<sources::hse, sources::hse::Prescaler::_2>(Milliseconds a_timeout)
{
    hkm_assert(true == sources::hse::is_enabled());

    const std::uint64_t start = utils::tick_counter<Milliseconds>::get();

    bit::flag::set(&(RCC->CR), RCC_CR_HSEPRE);
    bit::flag::set(&(RCC->CFGR), RCC_CFGR_SW, RCC_CFGR_SW_1);
    if (true == utils::wait_until::all_bits_are_set(
                    RCC->CFGR, RCC_CFGR_SWS_1, a_timeout.get() - (utils::tick_counter<Milliseconds>::get() - start)))
    {
        SystemCoreClock = sources::hse::get_frequency_Hz() / 2u;
        return true;
    }

    return false;
}
template<> inline bool sysclk<1u>::is_source<sources::hse>()
{
    return RCC_CFGR_SWS_1 == bit::flag::get(RCC->CFGR, RCC_CFGR_SWS_0);
}

template<> inline void sysclk<1u>::set_wakeup_source<sources::msi>()
{
    bit::flag::clear(&(RCC->CFGR), RCC_CFGR_STOPWUCK);
}
template<> inline void sysclk<1u>::set_wakeup_source<sources::hsi16>()
{
    bit::flag::set(&(RCC->CFGR), RCC_CFGR_STOPWUCK, RCC_CFGR_STOPWUCK);
}

template<> inline void sysclk<2u>::set_wakeup_source<sources::lse>()
{
    bit::flag::set(&(RCC->CSR), RCC_CSR_RFWKPSEL, RCC_CSR_RFWKPSEL_0);
}
template<> inline void sysclk<2u>::set_wakeup_source<sources::hse>()
{
    bit::flag::set(&(RCC->CSR), RCC_CSR_RFWKPSEL_0 | RCC_CSR_RFWKPSEL_1);
}
} // namespace xmcu::soc::st::arm::m4::wb::rm0434::clocks