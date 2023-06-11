#include "Common/GameApp.h"
#include "Common/D3DUtil.h"
#include "Common/DXTrace.h"
#include "Common/Layout.h"
#include "Common/GeometryUtil.h"
using namespace DirectX;

ComPtr<ID3D11InputLayout> m_pVertexLayout;
ComPtr<ID3D11Buffer> m_pVertexBuffer;
ComPtr<ID3D11Buffer> m_pIndexBuffer;
ComPtr<ID3D11Buffer> m_pConstantBuffer;
ComPtr<ID3D11VertexShader> m_pVertexShader;
ComPtr<ID3D11PixelShader> m_pPixelShader;

struct ConstantBuffer
{
    XMFLOAT4 color;
};

GameApp::GameApp(HINSTANCE hInstance, const std::wstring& windowName, int initWidth, int initHeight)
    : D3DApp(hInstance, windowName, initWidth, initHeight)
{
}

GameApp::~GameApp()
{
}

void GameApp::OnUpdate(float dt)
{
    
}

void GameApp::OnDraw()
{
    assert(m_pd3dImmediateContext);
    assert(m_pSwapChain);

    static float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };	// RGBA = (0,0,0,255)
    m_pd3dImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), black);
    m_pd3dImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    // 绘制三角形
    m_pd3dImmediateContext->DrawIndexed(36, 0, 0);

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    HR(m_pSwapChain->Present(0, 0));
}

void GameApp::OnResize()
{
    D3DApp::OnResize();
}

bool GameApp::OnInit()
{
    ComPtr<ID3DBlob> blob;

    /*****************创建vertex buffer & index buffer******************/
    std::vector<XMFLOAT3> vertex_vec;
    std::vector<unsigned int> index_vec;
    CreateBox(XMFLOAT3(0.0f, 0.0f, 0.0f), 0.5f, 0.5f, 0.5f, vertex_vec, index_vec);

    // 设置顶点缓冲区描述
    D3D11_BUFFER_DESC vbd;
    ZeroMemory(&vbd, sizeof(vbd));
    vbd.Usage = D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth = (UINT)(vertex_vec.size() * sizeof(VertexPos));
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    // 新建顶点缓冲区
    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = vertex_vec.data();
    HR(m_pd3dDevice->CreateBuffer(&vbd, &InitData, m_pVertexBuffer.GetAddressOf()));

    // 设置索引缓冲区描述
    D3D11_BUFFER_DESC ibd;
    ZeroMemory(&ibd, sizeof(ibd));
    ibd.Usage = D3D11_USAGE_IMMUTABLE;
    ibd.ByteWidth = UINT(index_vec.size() * sizeof(unsigned int));
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;
    // 新建索引缓冲区
    InitData.pSysMem = index_vec.data();
    HR(m_pd3dDevice->CreateBuffer(&ibd, &InitData, m_pIndexBuffer.GetAddressOf()));

    // 设置constant buffer描述
    D3D11_BUFFER_DESC cbd;
    ZeroMemory(&cbd, sizeof(cbd));
    cbd.Usage = D3D11_USAGE_DYNAMIC;
    cbd.ByteWidth = sizeof(ConstantBuffer);
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    ConstantBuffer constantBuffer;
    constantBuffer.color = XMFLOAT4(1.0, 0.0, 0.0, 1.0);
    InitData.pSysMem = &constantBuffer;
    // 新建常量缓冲区，不使用初始数据
    HR(m_pd3dDevice->CreateBuffer(&cbd, &InitData, m_pConstantBuffer.GetAddressOf()));


    /****************************创建shader********************************/

    // 创建顶点着色器
    HR(CreateShaderFromFile(L"HLSL\\mvp_VS.cso", L"HLSL\\mvp_VS.hlsl", "VS", "vs_5_0", blob.ReleaseAndGetAddressOf()));
    HR(m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pVertexShader.GetAddressOf()));
    // 创建并绑定顶点布局, 必须要在创建vs之后
    HR(m_pd3dDevice->CreateInputLayout(VertexPos::inputLayout, ARRAYSIZE(VertexPos::inputLayout),
        blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout.GetAddressOf()));

    // 创建像素着色器
    HR(CreateShaderFromFile(L"HLSL\\mvp_PS.cso", L"HLSL\\mvp_PS.hlsl", "PS", "ps_5_0", blob.ReleaseAndGetAddressOf()));
    HR(m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pPixelShader.GetAddressOf()));
    
    /***************************设置pipeline********************************/

    // 输入装配阶段的顶点缓冲区设置
    UINT stride = sizeof(VertexPos);	// 跨越字节数
    UINT offset = 0;						// 起始偏移量

    m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
    m_pd3dImmediateContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    // 设置图元类型，设定输入布局
    m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout.Get());
    // 将着色器绑定到渲染管线
    m_pd3dImmediateContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
    m_pd3dImmediateContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);
    m_pd3dImmediateContext->VSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());

    /**************************设置调试对象名****************************/
    D3D11SetDebugObjectName(m_pVertexLayout.Get(), "VertexPosLayout");
    D3D11SetDebugObjectName(m_pVertexBuffer.Get(), "VertexBuffer");
    D3D11SetDebugObjectName(m_pVertexShader.Get(), "mvp_VS");
    D3D11SetDebugObjectName(m_pPixelShader.Get(), "mvp_PS");
    
    return true;
}