#pragma once

/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// xmcu
#include <xmcu/Duration.hpp>
#include <xmcu/non_constructible.hpp>
#include <xmcu/soc/ST/arm/m4/wb/rm0434/rcc.hpp>
#include <xmcu/soc/ST/arm/m4/wb/rm0434/system/mcu/mcu.hpp>
#include <xmcu/soc/ST/arm/m4/wb/rm0434/utils/tick_counter.hpp>

// debug
#include <xmcu/assertion.hpp>

namespace xmcu::soc::st::arm::m4::wb::rm0434::utils {
class delay : private non_constructible
{
public:
    static void wait(Milliseconds a_time);
    static void wait(Seconds a_time);
    static void wait(Microseconds a_time);
};
} // namespace xmcu::soc::st::arm::m4::wb::rm0434::utils