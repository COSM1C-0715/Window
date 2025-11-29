#include "CommandQueue.h"
#include<d3d12.h>
#include<dxgi1_4.h>
#include<cassert>
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
bool CommandQueue::CreateCommandQueue(Device& device)
{
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    queueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.NodeMask = 0;

    HRESULT hr = device.GetDevice()->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue));

    if (FAILED(hr))
    {
        OutputDebugString("Failed to create Command Queue\n");
        return false;
    }
    return true;
}
ID3D12CommandQueue* CommandQueue::Getcommandqueue()
{
    if (!commandQueue)
    {
        assert(false && "コマンドキューがないですよ！！");
    }
    return commandQueue;
}

D3D12_COMMAND_QUEUE_DESC& CommandQueue::GetQueueDesc() 
{
    if (!commandQueue)
    {
        assert(false && "コマンドキューがなーい");
    }
    return queueDesc;
}
