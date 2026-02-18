#include "Quad_polygon.h"
#include<cassert>
namespace 
{
	struct Vertex
	{
		DirectX::XMFLOAT3 postion;
		DirectX::XMFLOAT4 color;
	};
}

bool Quad_polygon::CreateVertexBuffer()
{
	Vertex triangleVertices[] = 
	{
		{{-0.5f,0.5f,0.0f},{1.0f,0.0f,1.0f,1.0f}},
		{{0.5f,0.5f,0.0f},{0.0f,1.0f,1.0f,1.0f}},
		{{-0.5f,-0.5f,0.0f},{0.0f,0.0f,1.0f,1.0f}},
		{{0.5f,-0.5f,0.0f},{0.0f,0.0f,1.0f,1.0f}}
	};

	auto vertexBufferSize = sizeof(triangleVertices);

	D3D12_HEAP_PROPERTIES heapProperty{};
	heapProperty.Type = D3D12_HEAP_TYPE_UPLOAD;
	heapProperty.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heapProperty.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heapProperty.CreationNodeMask = 1;
	heapProperty.VisibleNodeMask = 1;

	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resourceDesc.Alignment = 0;
	resourceDesc.Width = vertexBufferSize;
	resourceDesc.Height = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.MipLevels = 1;
	resourceDesc.Format = DXGI_FORMAT_UNKNOWN;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.SampleDesc.Quality = 0;
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

	auto res = Device::instance().GetDevice()->CreateCommittedResource(&heapProperty, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&VertexBuffer));

	if (FAILED(res))
	{
		assert(false&& "頂点バッファがないぞー？");
		return false;
	}

	Vertex* data{};

	res = VertexBuffer->Map(0, nullptr, reinterpret_cast<void**>(&data));

	if (FAILED(res))
	{
		assert(false && "頂点バッファのマップがないぞー？");
		return false;
	}

	memcpy_s(data, vertexBufferSize, triangleVertices, vertexBufferSize);

	VertexBuffer->Unmap(0, nullptr);

	VertexBufferView.BufferLocation = VertexBuffer->GetGPUVirtualAddress();
	VertexBufferView.SizeInBytes = vertexBufferSize;
	VertexBufferView.StrideInBytes = sizeof(Vertex);

	Toporogy_ = porigon::type.Strip;

	return true;
}

bool Quad_polygon::CreateIndexBuffer()
{
	uint16_t quadIndices[] = 
	{
			0,1,2,3
	};

	auto indexBufferSize = sizeof(quadIndices);

	D3D12_HEAP_PROPERTIES heapProperty{};
	heapProperty.Type = D3D12_HEAP_TYPE_UPLOAD;
	heapProperty.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heapProperty.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heapProperty.CreationNodeMask = 1;
	heapProperty.VisibleNodeMask = 1;

	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resourceDesc.Alignment = 0;
	resourceDesc.Width = indexBufferSize;
	resourceDesc.Height = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.MipLevels = 1;
	resourceDesc.Format = DXGI_FORMAT_UNKNOWN;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.SampleDesc.Quality = 0;
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

	auto res = Device::instance().GetDevice()->CreateCommittedResource(&heapProperty, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&IndexBuffer));

	if (FAILED(res))
	{
		assert(false&&"インデックスバッファがないぞー？");
		return false;
	}

	uint16_t* data{};
	res = IndexBuffer->Map(0, nullptr, reinterpret_cast<void**>(&data));

	if (FAILED(res))
	{
		assert(false && "インデックスバッファのマップがないぞー？");
		return false;
	}

	memcpy_s(data, indexBufferSize, quadIndices, indexBufferSize);

	IndexBuffer->Unmap(0, nullptr);

	IndexBufferView.BufferLocation = IndexBuffer->GetGPUVirtualAddress();
	IndexBufferView.SizeInBytes = indexBufferSize;
	IndexBufferView.Format = DXGI_FORMAT_R16_UINT;

	IndexCount_ = _countof(quadIndices);

	return true;
}

ID3D12CommandList* Quad_polygon::Draw(Command_List& commandlist)
{
	commandlist.GetCommandList()->IASetVertexBuffers(0, 1, &VertexBufferView);
	commandlist.GetCommandList()->IASetIndexBuffer(&IndexBufferView);

	commandlist.GetCommandList()->IASetPrimitiveTopology(porigon::type.Strip);

	commandlist.GetCommandList()->DrawIndexedInstanced(4, 1, 0, 0, 0);
	return commandlist.GetCommandList();
}