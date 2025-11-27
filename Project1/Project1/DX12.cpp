#include<Windows.h>
#include<d3d12.h>
#include<string>
#include <dxgi1_4.h>
#include "DX12.h"
#include<cassert>
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
}

bool DX12::CreateDXGIFactory()
{
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
        return false;
    }

    return true;
}
IDXGIFactory4* DX12::Factory()
{
    if (!factory)
    {
        assert(false && "ファクトリーがない");
        return nullptr;
    }
    return factory;
}
void DX12::EnableDebugLayer()
{
    ID3D12Debug* debugController1;

    if (SUCCEEDED(debugController1->QueryInterface(IID_PPV_ARGS(&debugController1))))
    {
        
    }
}


