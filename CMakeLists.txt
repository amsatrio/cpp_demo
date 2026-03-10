cmake_minimum_required(VERSION 3.20)
project(HelloWorldCpp23 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Hello World Library & Test
add_library(hello_lib src/hello_world/hello_world.cpp)
target_include_directories(hello_lib PUBLIC src/hello_world)

add_executable(hello_test src/hello_world/hello_world_test.cpp)
target_link_libraries(hello_test PRIVATE hello_lib)

# Animal Library & Test
add_library(animal_lib src/animal/animal.cpp)
target_include_directories(animal_lib PUBLIC src/animal)

add_executable(animal_test src/animal/animal_test.cpp)
target_link_libraries(animal_test PRIVATE animal_lib)

# Cache Library & Test
add_library(cache_lib src/cache/cache.cpp)
target_include_directories(cache_lib PUBLIC src/cache)

add_executable(cache_test src/cache/cache_test.cpp)
target_link_libraries(cache_test PRIVATE cache_lib)

# Testing Configuration
enable_testing()
add_test(NAME HelloWorldTest COMMAND hello_test)
add_test(NAME AnimalTest COMMAND animal_test)
add_test(NAME CacheTest COMMAND cache_test)