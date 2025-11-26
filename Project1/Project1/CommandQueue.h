#include<d3d12.h>
#include<dxgi1_4.h>
#pragma once
class CommandQueue
{
public:
	ID3D12CommandQueue* commandQueue;
public:
	CommandQueue();
	~CommandQueue();
	ID3D12CommandQueue* CreateCommandQueue(ID3D12Device* device);
};

