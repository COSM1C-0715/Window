#include "Constant_buffer.h"
#include"Descriptor_Heap.h"
#include<cassert>
#include<DirectXMath.h>
namespace
{
	auto heapType_ = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
}
Constant_buffer::~Constant_buffer()
{
	if (constantBuffer)
	{
		constantBuffer->Release();
		constantBuffer = nullptr;
	}
}
bool Constant_buffer::Createcostantbuffer(UINT bufferSize)
{
	auto size = (sizeof(bufferSize) + 255) & ~255;

	D3D12_HEAP_PROPERTIES heapProps{};
	heapProps.Type = D3D12_HEAP_TYPE_UPLOAD;
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resourceDesc.Width = size;
	resourceDesc.Height = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.MipLevels = 1;
	resourceDesc.Format = DXGI_FORMAT_UNKNOWN;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	auto res = Device::instance().GetDevice()->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&constantBuffer));

	if (FAILED(res))
	{
		assert(false && "コンスタントバッファ作れなかっちゃ");
		return false;
	}

	auto descriptorIndex = DescriptorHeapContainer::instance().AllocateDescriptor(heapType_);

	if (heapType_ != D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)
	{
		assert(false&&"ディスクリプターヒープのタイプがCBV_SRV_UAVではありませーん");
		return false;
	}

	descriptorIndex_ = descriptorIndex.value();

	auto heap = DescriptorHeapContainer::instance().GetHeap(heapType_);

	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvdesc{};
	cbvdesc.BufferLocation = constantBuffer->GetGPUVirtualAddress();
	cbvdesc.SizeInBytes = size;

	UINT cbvDescriptorSize = Device::instance().GetDevice()->GetDescriptorHandleIncrementSize(heapType_);

	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = heap->GetCPUDescriptorHandleForHeapStart();

	cpuHandle.ptr += descriptorIndex_ * cbvDescriptorSize;

	Device::instance().GetDevice()->CreateConstantBufferView(&cbvdesc, cpuHandle);

	gpuHandle = heap->GetGPUDescriptorHandleForHeapStart();

	gpuHandle.ptr += descriptorIndex_ * cbvDescriptorSize;

	return true;
}
ID3D12Resource* Constant_buffer::ConstantBuffer()
{
	assert(constantBuffer && "コンスタントバッファ作れてへん");
	return constantBuffer.Get();
}
D3D12_GPU_DESCRIPTOR_HANDLE Constant_buffer::getGpuDescriptorHandle()
{
	return gpuHandle;
}
