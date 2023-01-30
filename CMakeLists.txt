cmake_minimum_required(VERSION 3.20)
project(Satoshi_2 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SATOSHI_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "Satoshi/src/include/*.hpp")
file(GLOB_RECURSE SATOSHI_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "Satoshi/src/lib/*.cpp")
file(GLOB_RECURSE SANDBOX_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "Sandbox/src/include/*.hpp")
file(GLOB_RECURSE SANDBOX_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "Sandbox/src/lib/*.cpp")

set(SATOSHI_LIBS 
    spdlogd
    glad
)

set(WIN32_ARG)

if(WIN32)
set(SATOSHI_LIBS
${SATOSHI_LIBS}
d3d11
d3d12
dxgi
dxguid
d3dcompiler
opengl32
)

set(WIN32_ARG WIN32)
endif()

add_library(Satoshi SHARED ${SATOSHI_HEADERS} ${SATOSHI_SOURCES})
target_include_directories(Satoshi PRIVATE "Satoshi/src/include" "Satoshi/vendor/spdlog/include" "./install/include")
target_link_directories(Satoshi PRIVATE "./install/lib")
target_link_libraries(Satoshi PRIVATE ${SATOSHI_LIBS})
target_compile_definitions(Satoshi PRIVATE ST_BUILD_DLL)

add_executable(Sandbox ${WIN32_ARG} ${SANDBOX_HEADERS} ${SANDBOX_SOURCES})

if(WIN32)
    
    target_compile_definitions(Satoshi PRIVATE ST_PLATFORM_WINDOWS)
    target_precompile_headers(Satoshi PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Satoshi/src/include/stpch.hpp")
    target_compile_definitions(Sandbox PRIVATE ST_PLATFORM_WINDOWS)
endif()
target_include_directories(Sandbox PRIVATE "Satoshi/src/include" "Sandbox/src/include" "./install/include")

target_link_libraries(Sandbox PRIVATE Satoshi)