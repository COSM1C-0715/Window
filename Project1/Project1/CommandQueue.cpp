#include "CommandQueue.h"
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
ID3D12CommandQueue* CommandQueue::CreateCommandQueue(Device& device)
{
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.NodeMask = 0;

    HRESULT hr = device.GetDevice()->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue));

    if (FAILED(hr))
    {
        OutputDebugString("Failed to create Command Queue\n");
        return nullptr;
    }
    return commandQueue;
}
