#include "Constant_buffer.h"
#include<cassert>
#include<DirectXMath.h>
Constant_buffer::~Constant_buffer()
{
	if (constantBuffer)
	{
		constantBuffer->Release();
		constantBuffer = nullptr;
	}
}
bool Constant_buffer::Createcostantbuffer(Device& device, Descriptor_Heap& heap, UINT buffersize, UINT descriptorIndex)
{
	auto size = (sizeof(buffersize) + 255) & ~255;

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

	auto res = device.GetDevice()->CreateCommittedResource(&heapProps,D3D12_HEAP_FLAG_NONE,&resourceDesc,D3D12_RESOURCE_STATE_GENERIC_READ,nullptr,IID_PPV_ARGS(&constantBuffer));

	if (FAILED(res))
	{
		assert(false && "コンスタントバッファ作れなかっちゃ");
		return false;
	}

	auto heapType = heap.gettype();
	if (heapType != D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)
	{
		assert(false&&"ディスクリプターヒープのタイプがCBV_SRV_UAVではありませーん");
		return false;
	}

	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvdesc{};
	cbvdesc.BufferLocation = constantBuffer->GetGPUVirtualAddress();
	cbvdesc.SizeInBytes = size;

	UINT cbvDescriptorSize = device.GetDevice()->GetDescriptorHandleIncrementSize(heap.gettype());

	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = heap.GetHeap()->GetCPUDescriptorHandleForHeapStart();

	cpuHandle.ptr += descriptorIndex * cbvDescriptorSize;

	device.GetDevice()->CreateConstantBufferView(&cbvdesc, cpuHandle);

	gpuHandle = heap.GetHeap()->GetGPUDescriptorHandleForHeapStart();

	gpuHandle.ptr += descriptorIndex * cbvDescriptorSize;

	return true;
}
ID3D12Resource* Constant_buffer::ConstantBuffer()
{
	assert(constantBuffer && "コンスタントバッファ作れてへん");
	return constantBuffer;
}
D3D12_GPU_DESCRIPTOR_HANDLE Constant_buffer::getGpuDescriptorHandle()
{
	return gpuHandle;
}
