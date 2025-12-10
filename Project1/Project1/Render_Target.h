#include<d3d12.h>
#include<dxgi1_4.h>
#include<vector>
#include"Device.h"
#include"Descriptor_Heap.h"
#include"Swapchain.h"
#pragma once
class Render_Target
{
public:
	std::vector<ID3D12Resource*> rn_tgt;
public:
	Render_Target() = default;
	~Render_Target();
	bool CreateBckBffr(Device& device, Swapchain& swapchain, Descriptor_Heap& heap);
	ID3D12Resource* GetResource(uint32_t index);
	D3D12_CPU_DESCRIPTOR_HANDLE gethandle(Device& device, Descriptor_Heap& heap, UINT index);
};

