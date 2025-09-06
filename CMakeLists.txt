cmake_minimum_required(VERSION 3.13)

project(engine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)
add_compile_options(-nostdinc++ -fno-rtti -fno-exceptions)

add_link_options(-nostdlib++)

if (DEFINED EMSCRIPTEN)
set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

#musl?

add_library(engine)

target_include_directories(engine PUBLIC include)

target_link_libraries(engine PUBLIC c++abi)

add_subdirectory(src)

add_subdirectory(example)
