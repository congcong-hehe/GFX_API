#pragma once

#include <d3d11_3.h>
#include <DirectXMath.h>

struct VertexPos
{
    DirectX::XMFLOAT3 pos;
    static const D3D11_INPUT_ELEMENT_DESC inputLayout[1];
};

const D3D11_INPUT_ELEMENT_DESC VertexPos::inputLayout[1] = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

struct VertexPosColor
{
    DirectX::XMFLOAT3 pos;
    DirectX::XMFLOAT4 color;
    static const D3D11_INPUT_ELEMENT_DESC inputLayout[2];
};

const D3D11_INPUT_ELEMENT_DESC VertexPosColor::inputLayout[2] = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};