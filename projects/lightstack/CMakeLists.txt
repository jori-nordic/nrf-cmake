cmake_minimum_required(VERSION 3.15.0)

project(lightstack)

# Set sources for the project
# We can specify build dependencies later with target_link_libraries
# Ninja will then rebuild them when necessary.
set(SOURCES src/main.c)

add_executable(${PROJECT_NAME} ${SOURCES})

# Add the `hello` library, it will be built automatically as a dependency
# `LINK_PUBLIC` is needed to retrieve the headers of `hello` APIs
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC hello)

# Include all the necessary paths for headers used in src/
# Other sources will include their own dirs automatically when they are built.
target_include_directories(${PROJECT_NAME} PRIVATE include)
