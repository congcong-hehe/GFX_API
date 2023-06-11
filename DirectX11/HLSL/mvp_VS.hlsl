#include "vertex.hlsli"

// 顶点着色器
VertexOut_pos VS(VertexIn_pos vIn)
{
    VertexOut_pos vOut;
    vOut.posH = float4(vIn.pos, 1.0f);
    return vOut;
}