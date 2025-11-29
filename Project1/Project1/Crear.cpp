#include "Crear.h"
#include"Device.h"
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

bool Crear::Create(Device& device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors)
{
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = 2;
	rtvHeapDesc.Type = type;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	_type = type;

	HRESULT hr = device.GetDevice()->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));
	if (FAILED(hr))
	{
		assert(false && "作成失敗");
	}
	return true;
}
bool Crear::CreateBckBffr(Device& device, Swapchain& swapchain, Crear& heap)
{
	auto& Desc = swapchain.GetDesc();
	rn_tgt.resize(Desc.BufferCount);

	auto handle = heap.GetHeap()->GetCPUDescriptorHandleForHeapStart();

	auto type = heap.gettype();

	for (uint8_t i = 0;i < Desc.BufferCount; ++i)
	{
		auto ht = swapchain.GetSwapChain()->GetBuffer(i, IID_PPV_ARGS(&rn_tgt[i]));

		device.GetDevice()->CreateRenderTargetView(rn_tgt[i], nullptr, handle);

		handle.ptr += device.GetDevice()->GetDescriptorHandleIncrementSize(type);
	}
	return true;
}

ID3D12Resource* Crear::GetResource(uint32_t index)
{
	if (index >= rn_tgt.size()||!rn_tgt[index])
	{
		assert(false && "それは違うよ");
		return nullptr;
	}
	return rn_tgt[index];
}

ID3D12DescriptorHeap* Crear::GetHeap()
{
	if (!rtvHeap)
	{
		assert(false && "ヒープがない");
		return nullptr;
	}
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
D3D12_CPU_DESCRIPTOR_HANDLE Crear::gethandle(Device& device, Crear& heap, UINT index)
{
	if (index >= rn_tgt.size() || !rn_tgt[index])
	{
		assert(false && "不正なレンダーターゲットです");
	}

	auto handle = heap.GetHeap()->GetCPUDescriptorHandleForHeapStart();

	auto heapType = gettype();

	assert(heapType == D3D12_DESCRIPTOR_HEAP_TYPE_RTV && "ディスクリプターのヒープがRTVではありません");

	handle.ptr += index * device.GetDevice()->GetDescriptorHandleIncrementSize(heapType);

	return handle;
}
