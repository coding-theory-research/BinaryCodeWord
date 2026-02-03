cmake_minimum_required(VERSION 3.20)

project(BinaryCodeWord VERSION 0.1.0 LANGUAGES CXX)

option(BCW_BUILD_TESTS "Build unit tests" OFF)
option(BCW_BUILD_EXAMPLES "Build examples" OFF)

add_library(BinaryCodeWord
    src/BinaryCodeWord.cpp
)
add_library(BinaryCodeWord::BinaryCodeWord ALIAS BinaryCodeWord)

target_compile_features(BinaryCodeWord PUBLIC cxx_std_20)

target_include_directories(BinaryCodeWord
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Helpful warnings (kept mild and portable)
if (MSVC)
    target_compile_options(BinaryCodeWord PRIVATE /W4)
else()
    target_compile_options(BinaryCodeWord PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(BCW_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(BCW_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# ---- Optional: install + package config (for find_package) ----
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS BinaryCodeWord
    EXPORT BinaryCodeWordTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT BinaryCodeWordTargets
    FILE BinaryCodeWordTargets.cmake
    NAMESPACE BinaryCodeWord::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BinaryCodeWord
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/BinaryCodeWordConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/BinaryCodeWordConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BinaryCodeWord
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/BinaryCodeWordConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/BinaryCodeWordConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/BinaryCodeWordConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BinaryCodeWord
)
