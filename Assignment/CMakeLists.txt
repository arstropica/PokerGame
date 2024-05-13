file(GLOB_RECURSE LIBRARY_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp"
     )

add_library(assignment_lib ${LIBRARY_SOURCES})


target_include_directories(assignment_lib PUBLIC
     "${CMAKE_CURRENT_SOURCE_DIR}/src"
     "${CMAKE_CURRENT_SOURCE_DIR}/utils"
     "${spdlog_SOURCE_DIR}/include"
)

target_link_libraries(assignment_lib PUBLIC 
)

add_subdirectory(test)