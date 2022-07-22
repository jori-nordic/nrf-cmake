cmake_minimum_required(VERSION 3.15.0)

# Tell cmake our compiler is working. We need to do this because else
# it will try to compile a basic C program, and will fail at the linking step.
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

# Top-level project
project(emb-cmake)

# Setup the path to nrfx and the MDK (that has the device headers)
if (NOT NRFX_PATH)
  if (DEFINED ENV{NRFX_PATH})
    set(NRFX_PATH $ENV{NRFX_PATH})
  else()
    message(FATAL_ERROR
      "NRFX not found. Please specify its path with -DNRFX_PATH=[path] or
       the NRFX_PATH environment variable.")
  endif()
endif()

message(STATUS "Using nrfx at ${NRFX_PATH}")
set(MDK_PATH ${NRFX_PATH}/mdk)

# Do the same for CMSIS headers (dependency of nrfx)
if (NOT CMSIS_PATH)
  if (DEFINED ENV{CMSIS_PATH})
    set(CMSIS_PATH $ENV{CMSIS_PATH})
  else()
    message(FATAL_ERROR
      "CMSIS not found. Please specify its path with -DCMSIS_PATH=[path] or
       the CMSIS_PATH environment variable.")
  endif()
endif()

message(STATUS "Using CMSIS at ${CMSIS_PATH}")
set(CMSIS_INCLUDE_PATH ${CMSIS_PATH}/Include)

## Setup the tool paths
# Select the toolchain
# Multiple choices here:
# - use the zephyr toolchain, passing the path through the SDK_PATH cmake variable
# - use the zephyr toolchain, passing the path from the ZEPHYR_SDK_INSTALL_DIR env variable
# - use another ARM GCC toolchain, passing the path through the GCC_PATH cmake variable
if (NOT GCC_PATH)
  if (NOT SDK_PATH)
    if (NOT (DEFINED ENV{ZEPHYR_SDK_INSTALL_DIR} AND DEFINED ENV{ZEPHYR_SDK_VERSION}))
      message(FATAL_ERROR
        "Zephyr toolchain not found, please specify using -DSDK_PATH=[path] or
         the ZEPHYR_SDK_INSTALL_DIR and ZEPHYR_SDK_VERSION env vars")
    endif()

    set(SDK_PATH $ENV{ZEPHYR_SDK_INSTALL_DIR}/zephyr-sdk-$ENV{ZEPHYR_SDK_VERSION})
  endif()

  set(GCC_PATH ${SDK_PATH}/arm-zephyr-eabi)
  set(GCC_VARIANT "arm-zephyr-eabi")
  message(STATUS "Using the zephyr toolchain: ${SDK_PATH}")
else()
  message(STATUS "Using a custom toolchain: ${GCC_PATH}")
  # Assuming arm-none-eabi-gcc
  set(GCC_VARIANT "arm-none-eabi")
endif()

# Include the std headers everywhere
include_directories(BEFORE ${GCC_PATH}/${GCC_VARIANT}/include)

## Compiler & linker

# Tell cmake we're cross-compiling
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSSCOMPILING 1)

# Set the compiler
set(CMAKE_C_COMPILER ${GCC_PATH}/bin/${GCC_VARIANT}-gcc CACHE PATH "" FORCE)

# Set the compiler flags
#
# Note: originally copied from build.ninja when building the
# peripheral_hr zephyr sample for nrf5340dk_nrf5340_cpunet target
set(C_FLAGS_DEVICE
  "-DNRF5340_XXAA_NETWORK -mcpu=cortex-m33+nodsp -mthumb -mabi=aapcs -mfp16-format=ieee ")

# Use string(CONCAT) for multiple flag lines
string(CONCAT C_FLAGS_WARNINGS
  "-Wall -Wformat -Wformat-security -Wno-format-zero-length -Wno-main "
  "-Wno-pointer-sign -Wpointer-arith -Wexpansion-to-defined "
  "-Wno-unused-but-set-variable -Werror=implicit-int ")

string(CONCAT C_FLAGS_MISC
  "-fno-asynchronous-unwind-tables -fno-pie -fno-pic -fno-reorder-functions "
  "-fno-defer-pop -ffreestanding -fno-common -ffunction-sections -fdata-sections "
  "-ffreestanding -fno-common  -fdiagnostics-color=always -std=c99 -nostdinc ")

# This can be overridden later per-library if desired
set(C_OPT_LVL "-Os")

# -ggdb allows inspecting macros in GDB
set(C_FLAGS_DEBUG "-g3 -ggdb -gdwarf-4")

# I think we could also use list(JOIN)
string(CONCAT CMAKE_C_FLAGS
  ${C_FLAGS_DEVICE}
  ${C_FLAGS_WARNINGS}
  ${C_FLAGS_MISC}
  ${C_OPT_LVL})

set(CMAKE_C_FLAGS_RELEASE "")
set(CMAKE_C_FLAGS_DEBUG ${C_FLAGS_DEBUG})

# If we were setting up a final application, we'd need the setup the
# linker flags & script here.

add_subdirectory(libs/hello)
add_subdirectory(projects/lightstack)
