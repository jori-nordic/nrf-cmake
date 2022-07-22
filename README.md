
This is intended to be a skeleton CMake Project for bare-metal nRF MCU apps.
It cross-compiles a library, to be linked in a Zephyr RTOS application.

Configuring
-----------

Run at the project root:

``` sh
cmake -GNinja -B build -S .
```

The configuration step is only necessary when the environment changes or CMake files are modified.
Out-of-tree builds (as done here) should be preferred as they don't litter the
project folder with build artifacts.

This assumes the environment has some environment variables defined:
- ZEPHYR_SDK_VERSION
- ZEPHYR_SDK_INSTALL_DIR
Example:
``` sh
export ZEPHYR_SDK_VERSION=0.14.2
export ZEPHYR_SDK_INSTALL_DIR=/home/myuser/sdk/zephyr
export CMSIS_PATH=/home/myuser/cmsis
export NRFX_PATH=/home/myuser/nrfx
```

One can also manually specify the Zephyr SDK toolchain path directly:
``` sh
cmake -GNinja -B build -S . -DSDK_PATH=/home/myuser/sdk/zephyr/zephyr-sdk-0.14.2
```

Or directly specify a custom GCC toolchain, e.g. gcc-arm-none-eabi:
``` sh
cmake -GNinja -B build -S . -DGCC_PATH=/home/myuser/gnuarmemb/gcc-arm-none-eabi-10.3-2021.10
```

The same can be done for nrfx and CMSIS:
``` sh
cmake -GNinja -B build -S . -DNRFX_PATH=/home/myuser/sdk/nrfx -DCMSIS_PATH=/home/myuser/sdk/CMSIS/Core
```

A command manually specifying every path might look like this:
``` sh
cmake -GNinja -B build -S . \
  -DNRFX_PATH=/home/myuser/sdk/nrfx \
  -DCMSIS_PATH=/home/myuser/sdk/CMSIS/Core \
  -DSDK_PATH=/home/myuser/sdk/zephyr/zephyr-sdk-0.14.2
```

Building the library
--------------------

Run at the project root:

``` sh
ninja -C build hello
```

This will result in a build/libs/hello/libhello.a library that can then be
exported and used in a Zephyr project.
