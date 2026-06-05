cmake_minimum_required(VERSION 3.19)
project(CrossLevelVisit VERSION 1.0.0)

# Set C++ standard to C++17 (required for Geode)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Geode SDK CMake modules to path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libs/geode-sdk/cmake")

# Find and include Geode package
find_package(Geode REQUIRED)

# Define the mod as a shared library
add_library(${PROJECT_NAME} SHARED
    # Source files
    src/main.cpp
    src/Trigger.cpp
    src/Teleport.cpp
    
    # Header files (for better IDE support)
    src/Trigger.h
    src/Teleport.h
)

# Include directories for this target
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${GEODE_INCLUDE_DIR}
)

# Link with Geode loader and dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE
    geode-sdk
)

# Setup Geode-specific build configuration
# This macro handles platform-specific settings, mod installation paths, etc.
geode_setup(${PROJECT_NAME})

# Optional: Set output directory for the compiled mod
set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/mods"
)

# Platform-specific compiler flags
if(MSVC)
    # Visual Studio specific settings
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    # GCC/Clang specific settings
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
endif()

# Add compiler definition for debug logging
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG_MODE=1)
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG_MODE=0)
endif()

# Ensure geode.json is in the output directory
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/geode.json
    ${CMAKE_CURRENT_BINARY_DIR}/geode.json
    COPYONLY
)

# Print build information
message(STATUS "====================================")
message(STATUS "Configuring ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "====================================")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "====================================")
