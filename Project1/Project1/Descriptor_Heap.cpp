#include "Descriptor_Heap.h"
#include<cassert>
Descriptor_Heap::~Descriptor_Heap()
{
	if (rtvHeap)
	{
		rtvHeap->Release();
		rtvHeap = nullptr;
	}
}

bool Descriptor_Heap::Create(Device& device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors,bool shaderVisible)
{
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = numDescriptors;
	rtvHeapDesc.Type = type;
	rtvHeapDesc.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	_type = type;

	HRESULT hr = device.GetDevice()->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));
	if (FAILED(hr))
	{
		assert(false && "作成失敗");
	}
	return true;
}

ID3D12DescriptorHeap* Descriptor_Heap::GetHeap()
{
	if (!rtvHeap)
	{
		assert(false && "ヒープがない");
		return nullptr;
	}
	return rtvHeap;
}

D3D12_DESCRIPTOR_HEAP_TYPE Descriptor_Heap::gettype()
{
	if (!rtvHeap)
	{
		assert(false&&"ヒープタイプがなーい");
	}
	return _type;
}
