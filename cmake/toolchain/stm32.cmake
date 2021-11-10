####
# Template toolchain.cmake.template: 
#
# This file acts as a template for the cmake toolchains. These toolchain files
# specify what tools to use when performing the build as part of CMake. This
# file can be used to quickly set one up.
#
# Follow all the steps in this template to create a toolchain file. Ensure
# to remove the template-failsafe (step 1) and fill in all <SOMETHING> tags.
#
# **Note:** this file should follow the standard CMake toolchain format. See:
# https://cmake.org/cmake/help/v3.12/manual/cmake-toolchains.7.html
#
# **Note:** If the user desires to set compile flags, or F prime specific build options, a platform
#           file should be constructed. See: [platform.md](platform.md)
#
# ### Filling In CMake Toolchain by Example ###
#
# CMake Toolchain files, at the most basic, define the system name and C and C++ compilers. In
# addition, a find path can be set to search for other utilities. This example will walk through
# setting these values using the appropriate variables. These can be specified using the following
# CMake setting flags:
#
# ```
# CMAKE_SYSTEM_NAME "RaspberryPI"
# # specify the cross compiler
# set(CMAKE_C_COMPILER "/opt/rpi/bin/arm-linux-gnueabihf-gcc")
# set(CMAKE_CXX_COMPILER "/opt/rpi/bin/arm-linux-gnueabihf-g++")
# # where is the target environment
# set(CMAKE_FIND_ROOT_PATH  "/opt/rpi")
# ```
#
# **Note:** if copying the template, delete the message with FATAL_ERROR line. This is a fail-safe
#           to prevent a raw-copy from being treated as a valid toolchain file. 
####

## STEP 1: DELETE the following fail-safe line

## STEP 2: Specify the target system's name. i.e. raspberry-pi-3
set(CMAKE_SYSTEM_NAME "freertos")
set(CMAKE_SYSTEM_PROCESSOR arm)

SET(STM32_BSP_PATH "${CMAKE_CURRENT_LIST_DIR}/../../NucleoH7_freeRTOS" CACHE PATH "Path to STM32 BSP")
set(STM32_CORE_SRC "${STM32_BSP_PATH}/Core/Src")
set(STM32_CORE_INC "${STM32_BSP_PATH}/Core/Inc")
set(STM32_HAL_SRC "${STM32_BSP_PATH}/Drivers/STM32H7xx_HAL_Driver/Src")
set(STM32_HAL_INC "${STM32_BSP_PATH}/Drivers/STM32H7xx_HAL_Driver/Inc")
set(STM32_HAL_INC_LEGACY "${STM32_BSP_PATH}/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy")
set(FREERTOS_PATH_SRC "${STM32_BSP_PATH}/Middlewares/Third_Party/FreeRTOS/Source")
set(FREERTOS_CMSIS "${FREERTOS_PATH_SRC}/CMSIS_RTOS_V2")
set(FREERTOS_PATH_INC "${FREERTOS_PATH_SRC}/include")

# STEP 3: Specify the path to C and CXX cross compilers
set(CMAKE_C_COMPILER "/home/rawinza555/gcc-arm-none-eabi-10.3-2021.07/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "/home/rawinza555/gcc-arm-none-eabi-10.3-2021.07/bin/arm-none-eabi-g++")
set(CMAKE_CXX_LINK_EXECUTABLE "${STM32_BSP_PATH}/STM32H743ZITx_FLASH.ld -o <TARGET> <OBJECTS> <LINK_LIBRARIES>")
set(COMPILER_COMMON_FLAGS
    "-DTGT_OS_TYPE_FREERTOS \
    -D__FREERTOS__ \
    -D__ELF__  \
    -mcpu=cortex-m7 \
    -mfpu=fpv5-d16 \
    -mfloat-abi=hard \
    -DUSE_HAL_DRIVER \
    -DSTM32H743xx \
    -Wall \
    -fdata-sections \
    -ffunction-sections \
    -mthumb "
    )    
set(CMAKE_C_FLAGS
    "${COMPILER_COMMON_FLAGS} \
    -std=c99"
    )  
set(CMAKE_CXX_FLAGS
    "${COMPILER_COMMON_FLAGS} \
    -std=c++14"
    )
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections --specs=nano.specs --specs=nosys.specs -mthumb -mabi=aapcs -Wl,-Map=${CMAKE_PROJECT_NAME}.map" CACHE INTERNAL "Linker options")
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_ASM_COMPILER_WORKS 1)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")


# STEP 4: Specify paths to root of toolchain package, for searching for
#         libraries, executables, etc.
set(CMAKE_FIND_ROOT_PATH  "/home/rawinza555/gcc-arm-none-eabi-10.3-2021.07/")

# DO NOT EDIT: F prime searches the host for programs, not the cross
# compile toolchain
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# DO NOT EDIT: F prime searches for libs, includes, and packages in the
# toolchain when cross-compiling.
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
