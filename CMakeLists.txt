cmake_minimum_required(VERSION 3.14)

# 设置解决方案名
project("GFX_API Learn")
# 设置项目名(不能有空格) 
set(TARGET_NAME "GFX_API")

# ------------------------------------------------------------------------------
# 项目细节配置(需熟悉CMake)
# ------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17) 
add_compile_definitions(UNICODE _UNICODE)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_subdirectory("DirectX11")