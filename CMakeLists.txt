cmake_minimum_required (VERSION 3.8)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project (Alloc VERSION ${PROJECT_VESRION})
find_package(GTest)
configure_file(version.h.in version.h)

add_executable (Allocate Allocate.cpp)
add_executable(Allocate_gtest test/Alloc_gtest.cpp)

target_include_directories(
    Allocate
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
    )

target_include_directories(
    Allocate
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Conteiners
    )

target_include_directories(
    Allocate
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Allocator
    )

target_include_directories(
    Allocate_gtest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/test
)
target_include_directories(
    Allocate_gtest PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_include_directories(
    Allocate_gtest PRIVATE
    ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(
    Allocate_gtest PRIVATE
    ${GTEST_BOTH_LIBRARIES}
)

set_target_properties(Allocate PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(Allocate PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(Allocate PRIVATE
        /EHsc
        /W4
        /WX
    )
endif()

install(TARGETS Allocate RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()


add_test(Allocate_gtest Allocate_gtest)