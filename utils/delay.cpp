/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// this
#include <xmcu/soc/ST/arm/m4/wb/rm0434/utils/delay.hpp>

// externals
#include <stm32wbxx.h>

// soc
#include <xmcu/soc/ST/arm/m4/wb/rm0434/clocks/sysclk.hpp>
#include <xmcu/soc/ST/arm/m4/wb/rm0434/rcc.hpp>
#include <xmcu/soc/ST/arm/m4/wb/rm0434/system/mcu/mcu.hpp>
#include <xmcu/soc/ST/arm/m4/wb/rm0434/utils/tick_counter.hpp>

// debug
#include <xmcu/assertion.hpp>

namespace xmcu::soc::st::arm::m4::wb::rm0434::utils {
using namespace xmcu;
using namespace xmcu::soc::st::arm::m4::wb::rm0434::system;
using namespace xmcu::soc::st::arm::m4::wb::rm0434::clocks;

void delay::wait(Milliseconds a_time)
{
    const std::uint64_t start = tick_counter<Milliseconds>::get();
    while (tick_counter<Milliseconds>::get() - start <= a_time.get()) continue;
}

void delay::wait(Seconds a_time)
{
    const std::uint64_t start = tick_counter<Milliseconds>::get();
    while (tick_counter<Milliseconds>::get() - start <= a_time.get_in<Milliseconds>().get());
}

void delay::wait(Microseconds a_time)
{
    hkm_assert(sysclk<1u>::get_frequency_Hz() >= 1_MHz);
    hkm_assert(mcu<1u>::DWT_mode::enabled == mcu<1u>::get_DWT_mode());

    DWT->CYCCNT = 0;
    const std::uint32_t max = DWT->CYCCNT + (sysclk<1u>::get_frequency_Hz() / 1_MHz * (a_time - 1_us).get());

    while (DWT->CYCCNT < max);
}
} // namespace xmcu::soc::st::arm::m4::wb::rm0434::utils