#include<d3d12.h>
#include<dxgi1_4.h>
#include"Device.h"
#pragma once
class CommandQueue
{
public:
	ID3D12CommandQueue* commandQueue;
public:
	CommandQueue() = default;
	~CommandQueue();
	ID3D12CommandQueue* CreateCommandQueue(Device& device);
};

