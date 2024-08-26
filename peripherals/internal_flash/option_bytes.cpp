/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// this
#include <xmcu/soc/ST/arm/m4/stm32wb/rm0434/peripherals/internal_flash/option_bytes.hpp>

// externals
#pragma GCC diagnostic ignored "-Wvolatile"
#include <stm32wbxx.h>
#pragma GCC diagnostic pop

// xmcu
#include <xmcu/bit.hpp>
#include <xmcu/soc/ST/arm/m4/nvic.hpp>
#include <xmcu/soc/ST/arm/m4/stm32wb/rm0434/peripherals/internal_flash/internal_flash.hpp>
#include <xmcu/soc/ST/arm/m4/stm32wb/rm0434/system/hsem/hsem.hpp>
#include <xmcu/soc/ST/arm/m4/stm32wb/rm0434/utils/tick_counter.hpp>
#include <xmcu/soc/ST/arm/m4/stm32wb/rm0434/utils/wait_until.hpp>
#include <xmcu/soc/Scoped_guard.hpp>

namespace xmcu {
namespace soc {
namespace m4 {
namespace stm32wb {
namespace rm0434 {
namespace peripherals {
using namespace xmcu;
using namespace xmcu::soc::m4::stm32wb::rm0434::utils;
using namespace xmcu::soc::m4::stm32wb::rm0434::system;

void option_bytes::unlocker::unlock()
{
    wait_until::all_bits_are_cleared(FLASH->SR, FLASH_SR_BSY);

    if (true == bit::flag::is(FLASH->CR, FLASH_CR_OPTLOCK))
    {
        Scoped_guard<nvic> interrupt_guard;

        FLASH->OPTKEYR = 0x08192A3Bu;
        FLASH->OPTKEYR = 0x4C5D6E7Fu;
    }
}
bool option_bytes::unlocker::unlock(Milliseconds a_timeout)
{
    if (true == wait_until::all_bits_are_cleared(FLASH->SR, FLASH_SR_BSY, a_timeout))
    {
        if (true == bit::flag::is(FLASH->CR, FLASH_CR_OPTLOCK))
        {
            Scoped_guard<nvic> interrupt_guard;

            FLASH->OPTKEYR = 0x08192A3Bu;
            FLASH->OPTKEYR = 0x4C5D6E7Fu;

            return true;
        }
    }

    return false;
}
void option_bytes::unlocker::lock()
{
    bit::flag::set(&(FLASH->CR), FLASH_CR_OPTLOCK);
}

std::uint32_t option_bytes::secure_flash::get_start_address()
{
    Scoped_guard<internal_flash::unlocker> flash_guard;
    Scoped_guard<unlocker> ob_guard;

    return bit::flag::get(FLASH->SFR, FLASH_SFR_SFSA) * internal_flash::s::page_size_in_bytes +
           internal_flash::s::start;
}
std::uint32_t option_bytes::secure_flash::get_start_address(Milliseconds a_timeout)
{
    const std::uint64_t start = tick_counter<Milliseconds>::get();

    Scoped_guard<internal_flash::unlocker> flash_guard(a_timeout.get() - (tick_counter<Milliseconds>::get() - start));

    if (true == flash_guard.is_unlocked())
    {
        Scoped_guard<unlocker> ob_guard(a_timeout.get() - (tick_counter<Milliseconds>::get() - start));

        if (true == ob_guard.is_unlocked())
        {
            return bit::flag::get(FLASH->SFR, FLASH_SFR_SFSA);
        }
    }

    return 0x0u;
}

bool option_bytes::BOR::set(Level a_level)
{
    Scoped_guard<hsem::_1_step> sem2_guard(0x2u);
    Scoped_guard<internal_flash::unlocker> flash_guard;

    if (true == flash_guard.is_unlocked())
    {
        Scoped_guard<option_bytes::unlocker> ob_guard;

        if (true == ob_guard.is_unlocked())
        {
            bit::flag::set(&(FLASH->OPTR), FLASH_OPTR_BOR_LEV, (static_cast<std::uint32_t>(a_level)));

            bit::flag::set(&(FLASH->CR), FLASH_CR_OPTSTRT);
            wait_until::all_bits_are_cleared(FLASH->SR, FLASH_SR_BSY);

            if (false == bit::flag::is(FLASH->SR, FLASH_SR_PESD))
            {
                bit::flag::set(&(FLASH->CR), FLASH_CR_OBL_LAUNCH);

                return true;
            }
        }
    }

    return false;
}

option_bytes::BOR::Level option_bytes::BOR::get()
{
    Scoped_guard<hsem::_1_step> sem2_guard(0x2u);
    Scoped_guard<internal_flash::unlocker> flash_guard;

    return static_cast<Level>(bit::flag::get(FLASH->OPTR, FLASH_OPTR_BOR_LEV));
}
} // namespace peripherals
} // namespace rm0434
} // namespace stm32wb
} // namespace m4
} // namespace soc
} // namespace xmcu