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

bool Descriptor_Heap::Create(Device& device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors)
{
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = 2;
	rtvHeapDesc.Type = type;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	_type = type;

	HRESULT hr = device.GetDevice()->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));
	if (FAILED(hr))
	{
		assert(false && "ì¬¸”s");
	}
	return true;
}

ID3D12DescriptorHeap* Descriptor_Heap::GetHeap()
{
	if (!rtvHeap)
	{
		assert(false && "ƒq[ƒv‚ª‚È‚¢");
		return nullptr;
	}
	return rtvHeap;
}

D3D12_DESCRIPTOR_HEAP_TYPE Descriptor_Heap::gettype()
{
	if (!rtvHeap)
	{
		return;
	}
	return _type;
}
