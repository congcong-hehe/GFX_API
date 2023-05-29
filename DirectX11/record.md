# D3D initializetion
https://zh.wikipedia.org/wiki/DirectX

DirectX是微软开发的一个API，包括多个部分， 例如
* DXGI
* Direct3D
* Direct2D
* DirectCompute
* DirectXMath
* ...


为了创建一个D3D的application, 我们需要:
* 创建一个window: CreateWindow()
* 创建一个device和对应的immediate context：D3D11CreateDevice()
    * 可以理解为一个虚拟的显卡
    * 主要用于创建各种资源, 例如资源类、视图类、着色器类
* 创建一个swapChain：CreateSwapChainForHwnd()
    * 使用DXGI的函数创建，创建之前需要构造一个dxgiFactory
    * swap chain包含一个back buffer和front buffer，front buffer用来显示，back buffer用来作为渲染的输出
* 获取swapChain的backbuffer， 创建一个renderTargetView: CreateRenderTargetView， 将backbuffer和renderTargetView绑定在一起
* 创建一个depthStencilBuffer：CreateTexture2D()， 创建一个depthStencilView:CreateDepthStencilView(), 将其与depthStencilBuffer绑定（depth信息和stencil信息存储在一个texture中）
* 将renderTargetView和depthStencilView绑定到OM(output-merge)阶段
* 设置视口变换：RSSetViewPorts()

# Render pipeline
https://learn.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-graphics-pipeline

### IA(input Assembler, 输入组装)：
two purposes:
* read primitive data from use-filed buffers(index buffer or index & vertex buffer?), and assemble the data into primitives
    * <b>这里我觉得可能和具体的GPU实现有关，上传的vertex buffer不需要全部使用，只需要使用index包含的。但是我觉得这里不需要组装片元，只需要将index对应的vertex fetch到，随后送到vs中计算即可，vs计算结束之后再进行primitive（contain vertex data)的assemble
    * 对于没有index buffer类型的数据，需要产生index buffer，对于powervr架构是这样的（在IA阶段），但是对于其他的架构不知道是否需要产生index buffer，且在哪一个阶段</b>
* attach system-generated value to help make shader more efficient

# 问题
* immediate context 和 defer context
* IA阶段是包含硬件，驱动、软件的操作吗