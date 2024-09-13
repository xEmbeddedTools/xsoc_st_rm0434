/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

#if defined(STM32WB)

// this
#include <xmcu/soc/ST/arm/m4/stm32wb/rm0434/sources/hsi48.hpp>

// xmcu
#include <xmcu/bit.hpp>
#include <xmcu/soc/ST/arm/m4/stm32wb/rm0434/system/hsem/hsem.hpp>
#include <xmcu/soc/ST/arm/m4/stm32wb/rm0434/utils/tick_counter.hpp>
#include <xmcu/soc/ST/arm/m4/stm32wb/rm0434/utils/wait_until.hpp>
#include <xmcu/soc/Scoped_guard.hpp>

namespace xmcu {
namespace soc {
namespace m4 {
namespace stm32wb {
namespace rm0434 {
namespace sources {
using namespace xmcu;
using namespace xmcu::soc::m4::stm32wb::rm0434::system;
using namespace xmcu::soc::m4::stm32wb::rm0434::utils;

void hsi48::enable()
{
    Scoped_guard<hsem::_1_step> sem5_guard(0x5u);

    bit::flag::set(&(RCC->CRRCR), RCC_CRRCR_HSI48ON);
    wait_until::all_bits_are_set(RCC->CRRCR, RCC_CRRCR_HSI48RDY);
}

bool hsi48::enable(Milliseconds a_timeout)
{
    const std::uint64_t start = tick_counter<Milliseconds>::get();

    Scoped_guard<hsem::_1_step> sem5_guard(0x5u, a_timeout.get() - (tick_counter<Milliseconds>::get() - start));

    if (true == sem5_guard.is_locked())
    {
        bit::flag::set(&(RCC->CRRCR), RCC_CRRCR_HSI48ON);
        return wait_until::all_bits_are_set(
            RCC->CRRCR, RCC_CRRCR_HSI48RDY, a_timeout.get() - (tick_counter<Milliseconds>::get() - start));
    }
    return false;
}

void hsi48::disable()
{
    Scoped_guard<hsem::_1_step> sem0_guard(0x0u);

    bit::flag::clear(&(RCC->CRRCR), RCC_CRRCR_HSI48ON);
    wait_until::all_bits_are_cleared(RCC->CRRCR, RCC_CRRCR_HSI48RDY);
}

bool hsi48::disable(Milliseconds a_timeout)
{
    const std::uint64_t start = tick_counter<Milliseconds>::get();

    Scoped_guard<hsem::_1_step> sem0_guard(0x0u, a_timeout.get() - (tick_counter<Milliseconds>::get() - start));

    if (true == sem0_guard.is_locked())
    {
        bit::flag::clear(&(RCC->CRRCR), RCC_CRRCR_HSI48ON);
        return wait_until::all_bits_are_cleared(
            RCC->CRRCR, RCC_CRRCR_HSI48RDY, a_timeout.get() - (tick_counter<Milliseconds>::get() - start));
    }
    return false;
}
} // namespace sources
} // namespace rm0434
} // namespace stm32wb
} // namespace m4
} // namespace soc
} // namespace xmcu

#endif