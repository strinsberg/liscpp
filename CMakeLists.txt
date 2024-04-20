cmake_minimum_required(VERSION 3.16)

project(liscpp VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# NOTE **This is a hack for lsp only and is not needed for compilation to succeed**
# Should probably be commented out for serious compilation.
# clangs lsp will not find the headers for zlib and gtest. The linking below
# is not enough to add include info on the headers to the compile commands.
# It is possible this has something to do with nix. However nix stores the
# paths to these includes in the below environment variable and they can be
# added to the compile commands. I should probably find a different way, but I
# have been messing with this for several hours and need to work on my code
# not fiddle with tools.
set(CMAKE_CXX_FLAGS_DEBUG $ENV{NIX_CFLAGS_COMPILE})

# Add additional libraries
find_package(GTest REQUIRED)

# Add the source files
file(GLOB_RECURSE LISCPP_SOURCES src/*.cpp)
file(GLOB_RECURSE LISCPP_INCLUDES include/*.h)
file(GLOB_RECURSE LISCPP_TESTS test/*.cpp)

# Add the sources as a lib
add_library(${PROJECT_NAME} STATIC ${LISCPP_SOURCES} ${LISCPP_INCLUDES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add testing
enable_testing()
add_executable(test_${PROJECT_NAME} ${LISCPP_TESTS})
target_link_libraries(test_${PROJECT_NAME} ${PROJECT_NAME})
target_link_libraries(test_${PROJECT_NAME} gtest gmock gtest_main)
set_target_properties(test_${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_test(NAME ${PROJECT_NAME} COMMAND test_${PROJECT_NAME})
include(GoogleTest)
