cmake_minimum_required (VERSION 3.14)

# ------------------------------------------------------------------------------
# 用户配置
# ------------------------------------------------------------------------------
# 设置解决方案名
project("DirectX11 Test")
# 设置项目名(不能有空格) 
set(TARGET_NAME "DirectX11_Test")

# ------------------------------------------------------------------------------
# 项目细节配置(需熟悉CMake)
# ------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17) 
add_compile_definitions(UNICODE _UNICODE)

file(COPY ${HLSL_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(GLOB HLSL_FILES ${HLSL_DIR}/*.hlsl)
file(GLOB HEADER_FILES ./*.h)

aux_source_directory(. DIR_SRCS)

add_executable(${TARGET_NAME} WIN32 ${DIR_SRCS} ${HEADER_FILES})
target_link_libraries(${TARGET_NAME} d3d11.lib dxgi.lib dxguid.lib D3DCompiler.lib winmm.lib d2d1.lib dwrite.lib)

# 输出文件名
set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME ${TARGET_NAME})
set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
