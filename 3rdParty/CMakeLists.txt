cmake_minimum_required(VERSION 3.14)

file(GLOB IMGUI_DIR_SRCS
    Imgui/*.cpp
    Imgui/backends/imgui_impl_dx11.cpp
    Imgui/backends/imgui_impl_win32.cpp
)
add_library(ImGui STATIC ${IMGUI_DIR_SRCS})

target_include_directories(ImGui PUBLIC ./Imgui)