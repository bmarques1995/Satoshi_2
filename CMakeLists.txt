cmake_minimum_required(VERSION 3.20)
project(Satoshi_2 LANGUAGES C CXX)

file(GLOB_RECURSE SATOSHI_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "Satoshi/src/include/*.hpp")
file(GLOB_RECURSE SATOSHI_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "Satoshi/src/lib/*.cpp")
file(GLOB_RECURSE SANDBOX_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "Sandbox/src/include/*.hpp")
file(GLOB_RECURSE SANDBOX_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "Sandbox/src/lib/*.cpp")



add_library(Satoshi SHARED ${SATOSHI_HEADERS} ${SATOSHI_SOURCES})
target_include_directories(Satoshi PRIVATE "Satoshi/src/include")
target_compile_definitions(Satoshi PRIVATE ST_BUILD_DLL)
add_executable(Sandbox ${SANDBOX_HEADERS} ${SANDBOX_SOURCES})
if(WIN32)
    target_compile_definitions(Satoshi PRIVATE ST_PLATFORM_WINDOWS)
    target_compile_definitions(Sandbox PRIVATE ST_PLATFORM_WINDOWS)
endif()
target_include_directories(Sandbox PRIVATE "Satoshi/src/include" "Sandbox/src/include")
target_link_libraries(Sandbox PRIVATE Satoshi)