cmake_minimum_required(VERSION 3.14)

# 设置解决方案名
project("GFX_API Learn")

# ------------------------------------------------------------------------------
# 项目细节配置(需熟悉CMake)
# ------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17) 
add_compile_definitions(UNICODE _UNICODE)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_subdirectory("3rdParty")
set_target_properties(ImGui PROPERTIES FOLDER "ImGui")

add_subdirectory("DirectX11")
set_target_properties(DirectX11 PROPERTIES FOLDER "DirectX11")