cmake_minimum_required(VERSION 3.19.0)
file(GLOB_RECURSE XMCU_SOC_SRC "${CMAKE_CURRENT_LIST_DIR}/*.cpp" "${CMAKE_CURRENT_LIST_DIR}/*.c" "${CMAKE_CURRENT_LIST_DIR}/*.asm")
add_library(XMCU_SOC OBJECT ${XMCU_SOC_SRC})
target_include_directories(XMCU_SOC PRIVATE
                                    ${XMCU_PATH}
                                    ${CMAKE_CURRENT_LIST_DIR}/soc/ST/arm/CMSIS/Include
                                    ${CMAKE_CURRENT_LIST_DIR}/soc/ST/arm/CMSIS/Device/ST/STM32WBxx/Include)
