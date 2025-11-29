#include "Swapchain.h"
#include<cassert>
Swapchain::~Swapchain()
{
    if (swapChain1)
    {
        swapChain1->Release();
        swapChain1 = nullptr;
    }
    if (swapChain)
    {
        swapChain->Release();
        swapChain = nullptr;
    }
};

bool Swapchain::CreateSwapChain(DX12& factory, ID3D12CommandQueue* commandQueue, HWND hwnd)
{
    swapChainDesc.BufferCount = 2;
    swapChainDesc.Width = 1280;
    swapChainDesc.Height = 720;
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.SampleDesc.Count = 1;

    HRESULT hr = factory.Factory()->CreateSwapChainForHwnd(commandQueue, hwnd, &swapChainDesc, nullptr, nullptr, &swapChain1);

    if (FAILED(hr))
    {
        OutputDebugString("Failed to create Swap Chain\n");
        return false;
    }

    hr = swapChain1->QueryInterface(IID_PPV_ARGS(&swapChain));
    swapChain1->Release();

    if (FAILED(hr))
    {
        OutputDebugString("Failed to cast to SwapChain3\n");
        return false;
    }

    return true;
};

IDXGISwapChain3* Swapchain::GetSwapChain()
{
    if (!swapChain)
    {
        assert(false && "スワップチェインがない");
        return nullptr;
    }
    return swapChain;
}

DXGI_SWAP_CHAIN_DESC1& Swapchain::GetDesc()
{
    if (!swapChain)
    {
        assert(false && "スワップチェインがなーーい");
    }
    return swapChainDesc;
}
