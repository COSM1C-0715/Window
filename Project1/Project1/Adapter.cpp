#include "Adapter.h"
#include<d3d12.h>
#include<cassert>
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxguid.lib")
Adapter::~Adapter()
{
	if (Getadapter)
	{
		Getadapter->Release();
		Getadapter = nullptr;
	}
}
bool  Adapter::GetHardwareAdapter(IDXGIFactory4* factory)
{
    for (UINT adapterIndex = 0; ; ++adapterIndex)
    {
        Getadapter = nullptr;
        if (DXGI_ERROR_NOT_FOUND == factory->EnumAdapters1(adapterIndex, &Getadapter))
        {
            break;
        }

        DXGI_ADAPTER_DESC1 desc;
        Getadapter->GetDesc1(&desc);

        if (&desc.Flags && DXGI_ADAPTER_FLAG_SOFTWARE)
        {
            Getadapter->Release();
            continue;
        }

        if (SUCCEEDED(D3D12CreateDevice(Getadapter, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr)))
        {
            return true;
        }

        Getadapter->Release();
    }

    return false;
}
IDXGIAdapter1* Adapter::adapter()
{
    if (!adapter)
    {
        assert(false && "アダプターがない");
        return nullptr;
    }
    return Getadapter;
}
