#include<d3d12.h>
#include<wrl/client.h>
#include"Device.h"
#include"Descriptor_Heap.h"
#pragma once
class Constant_buffer
{
private:
	Microsoft::WRL::ComPtr<ID3D12Resource> constantBuffer{};
	UINT descriptorIndex_{};
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle;
public:
	Constant_buffer() = default;
	~Constant_buffer();
	bool Createcostantbuffer(UINT bufferSize);
	ID3D12Resource* ConstantBuffer();
	D3D12_GPU_DESCRIPTOR_HANDLE getGpuDescriptorHandle();
};

