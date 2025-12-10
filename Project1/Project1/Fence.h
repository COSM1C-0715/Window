#include<Windows.h>
#include<d3d12.h>
#include<dxgi1_4.h>
#include<vector>
#include"Device.h"
#include"Swapchain.h"
#pragma once
class Fence
{
public:
	ID3D12Fence* fence;

	HANDLE waitGpuEvent;
public:
	Fence() = default;
	~Fence();
	bool CreateFence(Device& device);
	void Wait(UINT64 fenceValue);
	ID3D12Fence* GetFence();
};

