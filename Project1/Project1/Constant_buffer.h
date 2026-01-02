#include<d3d12.h>
#include"Device.h"
#include"Descriptor_Heap.h"
#pragma once
class Constant_buffer
{
public:
	ID3D12Resource* constantBuffer;
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle;
public:
	Constant_buffer() = default;
	~Constant_buffer();
	bool Createcostantbuffer(Device& device, Descriptor_Heap& heap,UINT buffersize,UINT descriptorIndex);
	ID3D12Resource* ConstantBuffer();
	D3D12_GPU_DESCRIPTOR_HANDLE getGpuDescriptorHandle();
};

