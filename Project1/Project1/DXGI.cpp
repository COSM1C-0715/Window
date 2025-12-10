#include<Windows.h>
#include<d3d12.h>
#include<string>
#include <dxgi1_4.h>
#include "DXGI.h"
#include<cassert>
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxguid.lib")
DXGI::~DXGI()
{
    if (factory)
    {
        factory->Release();
        factory = nullptr;
    }
    if (Getadapter)
    {
        Getadapter->Release();
        Getadapter = nullptr;
    }
}

bool DXGI::SetDisplayAdapter()
{
    enabledebugLayer();

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
    }
    {
        auto select = 0;
        IDXGIAdapter1* Getadapter_{};
        while(factory->EnumAdapters1(select,&Getadapter))
        {
            DXGI_ADAPTER_DESC1 desc;
            Getadapter->GetDesc1(&desc);
            select++;
            if (desc.Flags && DXGI_ADAPTER_FLAG_SOFTWARE)
            {
                Getadapter->Release();
                continue;
            }

            if (FAILED(D3D12CreateDevice(Getadapter, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr)))
            {
                continue;
            }
            Getadapter = Getadapter_;

            break;
        }
        if (!Getadapter)
        {
            assert(false&& "アダプターがなーーい");
            return false;
        }
    }
    return true;
}
IDXGIFactory4* DXGI::FActroy()
{
    if (!factory)
    {
        assert(false && "ファクトリーがない");
        return nullptr;
    }
    return factory;
}

IDXGIAdapter1* DXGI::adapter()
{
    if (!Getadapter)
    {
        assert(false && "アダプターがない");
        return nullptr;
    }
    return Getadapter;
}
void DXGI::enabledebugLayer()
{
    ID3D12Debug* debugController1;

    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController1))))
    {
        debugController1->EnableDebugLayer();
    }
}


