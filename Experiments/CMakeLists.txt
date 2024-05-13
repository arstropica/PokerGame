# Add executable and specify source files
add_executable(PokerDemo
    PokerDemo.cpp
)

# Link libraries
target_link_libraries(PokerDemo PRIVATE
    assignment_lib
)
