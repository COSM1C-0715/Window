#include "Render_Target.h"
#include<cassert>
Render_Target::~Render_Target()
{
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

bool Render_Target::CreateBckBffr(Device& device, Swapchain& swapchain, Descriptor_Heap& heap)
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

D3D12_CPU_DESCRIPTOR_HANDLE Render_Target::gethandle(Device& device, Descriptor_Heap& heap, UINT index) 
{
	if (index >= rn_tgt.size() || !rn_tgt[index])
	{
		assert(false && "不正なレンダーターゲットです");
	}

	auto handle = heap.GetHeap()->GetCPUDescriptorHandleForHeapStart();

	auto heapType = heap.gettype();

	assert(heapType == D3D12_DESCRIPTOR_HEAP_TYPE_RTV && "ディスクリプターのヒープがRTVではありません");

	handle.ptr += index * device.GetDevice()->GetDescriptorHandleIncrementSize(heapType);

	return handle;
}

ID3D12Resource* Render_Target::GetResource(uint32_t index)
{
	if(index >= rn_tgt.size() || !rn_tgt[index]) {
		assert(false && "不正なレンダーターゲットです");
		return nullptr;
	}
	return rn_tgt[index];
}
