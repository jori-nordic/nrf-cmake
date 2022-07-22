cmake_minimum_required(VERSION 3.15.0)

# Create a library and set its sources.
add_library(hello src/hello.c)

# MDK & CMSIS dependencies
target_include_directories(hello PRIVATE ${CMSIS_INCLUDE_PATH})
target_include_directories(hello PRIVATE ${MDK_PATH})

# Project-wide (public) include folder
target_include_directories(hello PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Make sure the compiler can find headers for our library when other
# libs or apps link to `hello`
target_include_directories(hello PUBLIC include)
