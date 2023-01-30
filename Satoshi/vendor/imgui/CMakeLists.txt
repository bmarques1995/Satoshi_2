cmake_minimum_required(VERSION 3.20)

project(imgui LANGUAGES CXX)

set(BUILD_IMGUI_FILES 
    ./imgui/imgui_demo.cpp
    ./imgui/imgui_draw.cpp
    ./imgui/imgui_tables.cpp
    ./imgui/imgui_widgets.cpp
    ./imgui/imgui.cpp

    ./imgui/backends/imgui_impl_vulkan.cpp
    ./imgui/backends/imgui_impl_opengl3.cpp 
)

if(WIN32)

set(BUILD_IMGUI_FILES ${BUILD_IMGUI_FILES}
    ./imgui/backends/imgui_impl_win32.cpp 
    ./imgui/backends/imgui_impl_dx11.cpp 
    ./imgui/backends/imgui_impl_dx12.cpp 
)

endif()

add_library(imgui STATIC ${BUILD_IMGUI_FILES})

target_include_directories(imgui PUBLIC ./imgui ./imgui/backends ${CMAKE_INSTALL_PREFIX}/include)

install(DIRECTORY imgui/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include/imgui FILES_MATCHING
PATTERN imgui.h 
PATTERN imconfig.h 
PATTERN imgui_internal.h 
PATTERN imstb_rectpack.h 
PATTERN imstb_textedit.h
PATTERN imstb_truetype.h)

install(DIRECTORY imgui/backends/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include/imgui/backends FILES_MATCHING
PATTERN imgui_impl_vulkan.h
PATTERN imgui_impl_opengl3.h)

if(WIN32)
    install(DIRECTORY imgui/backends/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include/imgui/backends FILES_MATCHING
    PATTERN imgui_impl_win32.h
    PATTERN imgui_impl_dx11.h
    PATTERN imgui_impl_dx12.h)
endif()

install(TARGETS imgui RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})