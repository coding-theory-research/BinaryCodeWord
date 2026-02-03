include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(bcw_tests test_BinaryCodeWord.cpp)
target_link_libraries(bcw_tests PRIVATE BinaryCodeWord::BinaryCodeWord GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(bcw_tests)
