#include "vertex.hlsli"

// 顶点着色器
VertexOut_pos_color VS(VertexIn_pos_color vIn)
{
    VertexOut_pos_color vOut;
    vOut.posH = float4(vIn.pos, 1.0f);
    vOut.color = vIn.color; // 这里alpha通道的值默认为1.0
    return vOut;
}