#include<d3d12.h>
#include<dxgi1_4.h>
#include"Device.h"
#pragma once
class CommandQueue
{
public:
	ID3D12CommandQueue* commandQueue{};

	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
public:
	CommandQueue() = default;
	~CommandQueue();
	bool CreateCommandQueue(Device& device);
	ID3D12CommandQueue* Getcommandqueue();
	D3D12_COMMAND_QUEUE_DESC& GetQueueDesc();
};

