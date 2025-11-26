#include "CommandQueue.h"
#include "Adapter.h"
#include<d3d12.h>
#include<dxgi1_4.h>
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxguid.lib")
CommandQueue::~CommandQueue()
{
	if (commandQueue)
	{
		commandQueue->Release();
		commandQueue = nullptr;
	}
}
ID3D12CommandQueue* CommandQueue::CreateCommandQueue(ID3D12Device* device) 
{
    HRESULT hr = D3D12CreateDevice(Getadapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));

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
