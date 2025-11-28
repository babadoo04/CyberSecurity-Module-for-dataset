cmake_minimum_required(VERSION 3.14)

project(SecurityModule)

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE  
            CPPS "src/*.cpp")

file(GLOB_RECURSE  
            HPPS "include/*.hpp")

add_executable(${PROJECT_NAME} ${CPPS} ${HPPS} main.cpp)

target_include_directories(${PROJECT_NAME}
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_precompile_headers(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/pch.hpp
)

find_package(cryptopp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE cryptopp::cryptopp)


# ------------------------
# ==== Google Tests ======
# ------------------------

enable_testing()
find_package(GTest CONFIG REQUIRED)

file(GLOB TESTS 
                "tests/*.cpp")
file(GLOB SRCS 
                "src/*.cpp")

if(TESTS)
    add_executable(${PROJECT_NAME}Tests ${TESTS} ${SRCS})

    target_include_directories(${PROJECT_NAME}Tests 
        PRIVATE 
            ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    target_link_libraries(${PROJECT_NAME}Tests
        PRIVATE
            GTest::gtest
            GTest::gtest_main
    )

    add_test(NAME ${PROJECT_NAME}Tests COMMAND ${PROJECT_NAME}Tests)
endif()