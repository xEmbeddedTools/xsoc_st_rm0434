#pragma once

/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

#include <xmcu/non_constructible.hpp>

namespace xmcu::soc::m4::wb::rm0434::peripherals {

class iwdg : private xmcu::non_constructible
{
public:
    static void enable();
    static void feed();
    static bool is_active();

private:
    static inline bool is_wdg_active = false;
};

} // namespace xmcu::soc::m4::wb::rm0434::peripherals
