#pragma once

/*
 *  Copyright (c) xEmbeddedTools team and contributors.
 *  Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
 */

// std
#include <cstdint>

// CMSIS
#include <stm32wbxx.h>

// xmcu
#include <rm0434/rcc.hpp>
#include <xmcu/non_constructible.hpp>

// debug
#include <xmcu/assertion.hpp>

namespace xmcu::soc::st::arm::m4::wb::rm0434::peripherals {
template<std::size_t length_t = 0x0u> class crc : private xmcu::non_constructible
{
public:
    enum class Input_data_format : std::uint32_t
    {
        unmodified = 0x0u,
        reversed_by_byte = CRC_CR_REV_IN_0,
        reversed_by_half_word = CRC_CR_REV_IN_1,
        reversed_by_word = CRC_CR_REV_IN_0 | CRC_CR_REV_IN_1
    };

    enum class Output_data_format_flag : std::uint32_t
    {
        unmodified = 0x0u,
        inverted = 0x1u,
        reversed_by_bit = 0x2u
    };

    enum class Polynomial_flag : std::uint64_t
    {
        unmodified = 0x1,
        custom = 0x2
    };
};

template<> class crc<7u> : private xmcu::non_constructible
{
public:
    static void start(crc<>::Input_data_format a_input_data_format,
                      crc<>::Output_data_format_flag a_output_data_format,
                      crc<>::Polynomial_flag a_polynomial,
                      std::uint8_t a_init_value = 0xFFu);

    static void update(const std::uint8_t* a_p_data, std::size_t a_data_legth_in_bytes);
    static std::uint32_t get();
};

template<> class crc<8u> : private xmcu::non_constructible
{
public:
    static void start(crc<>::Input_data_format a_input_data_format,
                      crc<>::Output_data_format_flag a_output_data_format,
                      crc<>::Polynomial_flag a_polynomial,
                      std::uint8_t a_init_value = 0xFFu);

    static void update(const std::uint8_t* a_p_data, std::size_t a_data_legth_in_bytes);
    static std::uint32_t get();
};

template<> class crc<16u> : private xmcu::non_constructible
{
public:
    static void start(crc<>::Input_data_format a_input_data_format,
                      crc<>::Output_data_format_flag a_output_data_format,
                      crc<>::Polynomial_flag a_polynomial,
                      std::uint16_t a_init_value = 0xFFFFu);

    static void update(const std::uint8_t* a_p_data, std::size_t a_data_legth_in_bytes);
    static std::uint32_t get();
};

template<> class crc<32u> : private xmcu::non_constructible
{
public:
    static void start(crc<>::Input_data_format a_input_data_format,
                      crc<>::Output_data_format_flag a_output_data_format,
                      crc<>::Polynomial_flag a_polynomial,
                      std::uint32_t a_init_value = 0xFFFFFFFFu);

    static void update(const std::uint8_t* a_p_data, std::size_t a_data_legth_in_bytes);
    static std::uint32_t get();
};

constexpr crc<>::Output_data_format_flag operator|(crc<>::Output_data_format_flag a_f1,
                                                   crc<>::Output_data_format_flag a_f2)
{
    return static_cast<crc<>::Output_data_format_flag>(static_cast<std::uint32_t>(a_f1) |
                                                       static_cast<std::uint32_t>(a_f2));
}

constexpr crc<>::Output_data_format_flag operator&(crc<>::Output_data_format_flag a_f1,
                                                   crc<>::Output_data_format_flag a_f2)
{
    return static_cast<crc<>::Output_data_format_flag>(static_cast<std::uint32_t>(a_f1) &
                                                       static_cast<std::uint32_t>(a_f2));
}

constexpr crc<>::Output_data_format_flag operator|=(crc<>::Output_data_format_flag& a_f1,
                                                    crc<>::Output_data_format_flag a_f2)
{
    a_f1 = a_f1 | a_f2;
    return a_f1;
}

constexpr crc<>::Polynomial_flag operator|(crc<>::Polynomial_flag a_f1, crc<>::Polynomial_flag a_f2)
{
    return static_cast<crc<>::Polynomial_flag>(static_cast<std::uint32_t>(a_f1) | static_cast<std::uint32_t>(a_f2));
}

constexpr crc<>::Polynomial_flag operator&(crc<>::Polynomial_flag a_f1, crc<>::Polynomial_flag a_f2)
{
    return static_cast<crc<>::Polynomial_flag>(static_cast<std::uint32_t>(a_f1) & static_cast<std::uint32_t>(a_f2));
}

constexpr crc<>::Polynomial_flag operator|=(crc<>::Polynomial_flag& a_f1, crc<>::Polynomial_flag a_f2)
{
    a_f1 = a_f1 | a_f2;
    return a_f1;
}

constexpr crc<>::Polynomial_flag operator|(crc<>::Polynomial_flag a_f1, std::uint32_t a_f2)
{
    hkm_assert(crc<>::Polynomial_flag::custom == a_f1);
    hkm_assert(a_f2 != 0x0u);

    return static_cast<crc<>::Polynomial_flag>(
        (static_cast<std::uint64_t>(a_f1) | (static_cast<std::uint64_t>(a_f2) << 32u)));
}
} // namespace xmcu::soc::st::arm::m4::wb::rm0434::peripherals

namespace xmcu::soc::st::arm::m4::wb::rm0434 {
template<> class rcc<peripherals::crc<>> : private xmcu::non_constructible
{
public:
    static void enable(bool a_enable_in_lp);
    static void disable();
};
} // namespace xmcu::soc::st::arm::m4::wb::rm0434