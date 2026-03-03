#include<d3d12.h>
#include<dxgi1_4.h>
#include<cassert>
#include<unordered_map>
#include<optional>
#include<memory>
#include"Device.h"
#pragma once
class Descriptor_Heap;

class DescriptorHeapContainer
{
private:
	std::unordered_map<UINT, std::unique_ptr<Descriptor_Heap>> map_{};
public:
	static DescriptorHeapContainer& instance()
	{
		static DescriptorHeapContainer instance;
		return instance;
	}
public:
	DescriptorHeapContainer();
	~DescriptorHeapContainer();
	bool Create(Device& device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors, bool shaderVisible = false);
	std::optional<UINT> AllocateDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE type);
	ID3D12DescriptorHeap* GetHeap(D3D12_DESCRIPTOR_HEAP_TYPE type);
};

