#include "vertex.hlsli"

// 像素着色器
float4 PS(VertexOut_pos_color pIn) : SV_Target
{
    return pIn.color;
}