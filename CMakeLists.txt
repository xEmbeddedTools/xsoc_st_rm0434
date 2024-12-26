#
# Copyright (c) xEmbeddedTools team and contributors.
# Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
#

cmake_minimum_required(VERSION 3.19.0)

if (XMCU_SOC_MODEL STREQUAL "XMCU_SOC_MODEL_STM32WB35CEU6A")
    file(GLOB_RECURSE XMCU_SOC_SRC 
            "${CMAKE_CURRENT_LIST_DIR}/rm0434/*.cpp" 
            "${CMAKE_CURRENT_LIST_DIR}/rm0434/*.c" 
            "${CMAKE_CURRENT_LIST_DIR}/rm0434/*.asm" 
            "${CMAKE_CURRENT_LIST_DIR}/rm0434/*.hpp"
            "${CMAKE_CURRENT_LIST_DIR}/rm0434/*.h"
            "${XMCU_PATH}/soc/ST/arm/CMSIS/Device/ST/STM32WBxx/Source/Templates/gcc/startup_stm32wb35xx_cm4.s"
            "${XMCU_PATH}/soc/ST/arm/CMSIS/Device/ST/STM32WBxx/Source/Templates/system_stm32wbxx.c")
    set(XMCU_LD_SCRIPT "${XMCU_PATH}/soc/ST/arm/CMSIS/Device/ST/STM32WBxx/Source/Templates/gcc/linker/stm32wb35xx_flash_cm4.ld")
    add_library(XMCU_SOC OBJECT ${XMCU_SOC_SRC})
    add_compile_definitions(XMCU_SOC PUBLIC "XMCU_SOC_MODEL_STM32WB35CEU6A" "STM32WB35xx")
endif()

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -mcpu=cortex-m4)
set(CMAKE_STATIC_LINKER_FLAGS ${CMAKE_STATIC_LINKER_FLAGS} -mcpu=cortex-m4 -mthumb)

include_directories(XMCU_SOC PUBLIC
                    ${XMCU_PATH}
                    ${CMAKE_CURRENT_LIST_DIR}
                    ${XMCU_PATH}/soc/ST/arm/CMSIS/Include ${XMCU_PATH}/soc/ST/arm/CMSIS/Device/ST/STM32WBxx/Include)
