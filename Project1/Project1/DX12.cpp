#include<Windows.h>
#include<d3d12.h>
#include<string>
#include <dxgi1_4.h>
#include "DX12.h"
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxguid.lib")


DX12::~DX12()
{
    if (factory)
    {
        factory->Release();
        factory = nullptr;
    }
    if (adapter)
    {
        adapter->Release();
        adapter = nullptr;
    }
}

IDXGIFactory4* DX12::CreateDXGIFactory()
{
    IDXGIFactory4* factory;
    UINT createFactoryFlags = 0;

#if defined(_DEBUG)
    // デバッグビルドではデバッグフラグを設定
    createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif

    HRESULT hr = CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&factory));
    if (FAILED(hr))
    {
        // エラーハンドリング：ファクトリー作成失敗
        OutputDebugString("Failed to create DXGI Factory\n");
        return nullptr;
    }

    return factory;
}

IDXGIAdapter* DX12::GetHardwareAdapter(IDXGIFactory4* factory)
{
    IDXGIAdapter1* adapter;
    for (UINT adapterIndex = 0; ; ++adapterIndex)
    {
        adapter = nullptr;
        if (DXGI_ERROR_NOT_FOUND == factory->EnumAdapters1(adapterIndex, &adapter))
        {
            break;
        }

        DXGI_ADAPTER_DESC1 desc;
        adapter->GetDesc1(&desc);

        if (&desc.Flags && DXGI_ADAPTER_FLAG_SOFTWARE)
        {
            adapter->Release();
            continue;
        }

        if (SUCCEEDED(D3D12CreateDevice(adapter,D3D_FEATURE_LEVEL_11_0,__uuidof(ID3D12Device),nullptr)))
        {
            return adapter;
        }

        adapter->Release();
    }

    return nullptr;
}

ID3D12Device* DX12::CreateD3D12Device(IDXGIAdapter1* adapter)
{
    ID3D12Device* device;
    HRESULT hr = D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));

    if (FAILED(hr))
    {
        hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));

        if (FAILED(hr))
        {
            OutputDebugString("Failed to create D3D12 Device\n");
            return nullptr;
        }
        OutputDebugString("Using software adapter (WARP)\n");
    }
    return device;
}
ID3D12CommandQueue* DX12::CreateCommandQueue(ID3D12Device* device)
{
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.NodeMask = 0;

    ID3D12CommandQueue* commandQueue;
    HRESULT hr = device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue));

    if(FAILED(hr))
    { 
        OutputDebugString("Failed to create Command Queue\n");
        return nullptr;
    }
    return commandQueue;
}

IDXGISwapChain3* DX12::CreateSwapChain(IDXGIFactory4* factory,ID3D12CommandQueue* commandQueue,HWND hwnd)
{
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.BufferCount = 2;
    swapChainDesc.Width = 1280;
    swapChainDesc.Height = 720;
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.SampleDesc.Count = 1;

    IDXGISwapChain1* swapChain1;
    HRESULT hr = factory->CreateSwapChainForHwnd(commandQueue, hwnd, &swapChainDesc, nullptr, nullptr, &swapChain1);

    if (FAILED(hr))
    {
        OutputDebugString("Failed to create Swap Chain\n");
        return nullptr;
    }

    IDXGISwapChain3* swapChain;
    hr = swapChain1->QueryInterface(IID_PPV_ARGS(&swapChain));
    swapChain1->Release();

    if (FAILED(hr))
    {
        OutputDebugString("Failed to cast to SwapChain3\n");
        return nullptr;
    }

    return swapChain;
}

void DX12::EnableDebugLayer()
{
    ID3D12Debug* debugController1;

    if (SUCCEEDED(debugController1->QueryInterface(IID_PPV_ARGS(&debugController1))))
    {
        
    }
}


