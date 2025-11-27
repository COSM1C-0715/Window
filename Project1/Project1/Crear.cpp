#include "Crear.h"
#include"DX12.h"
#include<Windows.h>
#include<d3d12.h>
#include<cassert>

Crear::~Crear()
{
	if (rtvHeap)
	{
		rtvHeap->Release();
		rtvHeap = nullptr;
	}
	for (auto& rt : rn_tgt)
	{
		if (rt)
		{
			rt->Release();
			rt = nullptr;
		}
	}
	rn_tgt.clear();
}

ID3D12DescriptorHeap* Crear::Create(Device& device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors)
{
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = 2;
	rtvHeapDesc.Type = type;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	_type = type;

	HRESULT hr = device.GetDevice()->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));
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
	if (index >= rn_tgt.size() || !rn_tgt[index])
	{
		assert(false && "不正なレンダーターゲットです");
	}

	auto handle = heap.GetCPUDescriptorHandleForHeapStart();

	auto heapType = gettype();

	assert(heapType == D3D12_DESCRIPTOR_HEAP_TYPE_RTV && "ディスクリプターのヒープがRTVではありません");

	handle.ptr += index * device.GetDescriptorHandleIncrementSize(heapType);

	for (int i = 0;i < index;i++)
	{
		
	}

	return handle;
}
