add_executable(assignment_tests PokerGameUnitTest.cpp)
add_executable(module05_tests PokerHandUnitTest.cpp)

target_include_directories(assignment_tests PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}")

target_link_libraries(assignment_tests PUBLIC
    assignment_lib
    Catch2::Catch2WithMain
    spdlog::spdlog
)

target_include_directories(module05_tests PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}")

target_link_libraries(module05_tests PUBLIC
    assignment_lib
    Catch2::Catch2WithMain
    spdlog::spdlog
)

# Enable CTest for running the tests
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(assignment_tests)
catch_discover_tests(module05_tests)