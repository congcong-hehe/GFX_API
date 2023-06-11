#include "vertex.hlsli"

cbuffer ConstantBuffer  : register(b0)
{
    flaot4 color;
};

// 像素着色器
float4 PS(VertexOut_pos pIn) : SV_Target
{
    return color;
}