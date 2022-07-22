cmake_minimum_required(VERSION 3.15.0)

# Create a library and set its sources.
add_library(hello src/hello.c)

# Make sure the compiler can find headers for our library when other
# libs or apps link to `hello`
target_include_directories(hello PUBLIC include)
