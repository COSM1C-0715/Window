#include "Crear.h"
#include<Windows.h>
#include<d3d12.h>

Crear::~Crear()
{
	if (rtvHeap)
	{
		rtvHeap->Release();
		rtvHeap = nullptr;
	}
}

ID3D12DescriptorHeap* Crear::Create(ID3D12Device& device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors)
{
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = 2;
	rtvHeapDesc.Type = type;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	_type = type;

	HRESULT hr = device.CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));
	return rtvHeap;
}
D3D12_DESCRIPTOR_HEAP_TYPE Crear::gettype()
{
	if (!rtvHeap)
	{
		return;
	}
	return _type;
}
D3D12_CPU_DESCRIPTOR_HANDLE Crear::gethandle(ID3D12Device& device, ID3D12DescriptorHeap& heap, UINT index)
{
	auto handle = heap.GetCPUDescriptorHandleForHeapStart();
}
