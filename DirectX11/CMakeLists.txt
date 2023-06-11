cmake_minimum_required (VERSION 3.14)

# 设置项目名(不能有空格) 
set(TARGET_NAME "DirectX11")

file(GLOB HLSL_FILES 
    HLSL/*.hlsl
    HLSL/*.hlsli
)

# message("HLSL_FILES: ${HLSL_FILES}")

file(GLOB SOURCE_FILES
    Common/*.cpp
    Main.cpp
    Predicate.cpp
)

file(COPY ${HLSL_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/HLSL)

foreach(HLSL_FILE ${HLSL_FILES})
    # message(${HLSL_FILE})

    get_filename_component(HLSL_FDIR ${HLSL_FILE} DIRECTORY)
    # message("HLSL_FDIR: ${HLSL_FDIR}")
    get_filename_component(HLSL_FBASENAME_WE ${HLSL_FILE} NAME_WE)
    # message("HLSL_FBASENAME: ${HLSL_FBASENAME}")
    string(CONCAT HLSL_FNAME_WE ${HLSL_FDIR} / ${HLSL_FBASENAME_WE})
    # message("HLSL_FNAME_WE: ${HLSL_FNAME_WE}")

    string(LENGTH ${HLSL_FBASENAME_WE} LEN_FNAME_WE)
    
    math(EXPR LEN_FNAME_WE "${LEN_FNAME_WE}-2")
    # message(${LEN_FNAME_WE})
    string(SUBSTRING ${HLSL_FBASENAME_WE} ${LEN_FNAME_WE} 2 ENTRY_POINT)
    # message(${ENTRY_POINT})
    string(TOLOWER ${ENTRY_POINT} SHADER_TYPE)

    if ("${SHADER_TYPE}" STREQUAL "vs") 
        set(SHADER_TYPE "Vertex")
    elseif("${SHADER_TYPE}" STREQUAL "hs") 
        set(SHADER_TYPE "Hull")
    elseif("${SHADER_TYPE}" STREQUAL "ds") 
        set(SHADER_TYPE "Domain")
    elseif("${SHADER_TYPE}" STREQUAL "gs") 
        set(SHADER_TYPE "Geometry")
    elseif("${SHADER_TYPE}" STREQUAL "ps")
        set(SHADER_TYPE "Pixel")
    elseif("${SHADER_TYPE}" STREQUAL "cs")
        set(SHADER_TYPE "Compute")
    endif()
    set_source_files_properties(${HLSL_FILE} PROPERTIES
                                VS_SHADER_OBJECT_FILE_NAME HLSL/${HLSL_FBASENAME_WE}.cso
                                VS_SHADER_TYPE ${SHADER_TYPE}
                                VS_SHADER_MODEL 5.0
                                VS_SHADER_ENTRYPOINT ${ENTRY_POINT}
                                VS_SHADER_DISABLE_OPTIMIZATIONS $<$<CONFIG:Debug>:true>
                                VS_SHADER_ENABLE_DEBUG $<$<CONFIG:Debug>:true>)
endforeach()

add_executable(${TARGET_NAME} WIN32 ${SOURCE_FILES})
target_link_libraries(${TARGET_NAME} d3d11.lib dxgi.lib dxguid.lib D3DCompiler.lib winmm.lib d2d1.lib dwrite.lib)

target_link_libraries(${TARGET_NAME} ImGui)
file(COPY imgui.ini DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# 输出文件名
set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME ${TARGET_NAME})
set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
