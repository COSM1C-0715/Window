#include<d3d12.h>
#include<dxgi1_4.h>
#include"Device.h"
#pragma once
class Descriptor_Heap
{
public:
	ID3D12DescriptorHeap* rtvHeap;

	D3D12_DESCRIPTOR_HEAP_TYPE _type;
public:
	Descriptor_Heap() = default;
	~Descriptor_Heap();
	bool Create(Device& device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors);
	ID3D12DescriptorHeap* GetHeap();
	D3D12_DESCRIPTOR_HEAP_TYPE gettype();
};

