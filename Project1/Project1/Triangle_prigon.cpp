#include"Triangle_prigon.h"
namespace
{
	struct vertex
	{
		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT4 Color;
	};
}

bool Triangle_prigon::Create(Device& device)
{
	if (!CreateVertexBuffer())
	{
		return false;
	}
	if (!CreateIndexBuffer())
	{
		return false;
	}
	return true;
}

bool Triangle_prigon::CreateVertexBuffer()
{
	vertex TriangleVertex[]
	{
		{{0.5f,-0.2f,0.0f},{0.1f,0.4f,0.5f,0.4f}},
		{{0.3f,-0.4f,0.0f},{0.1f,0.4f,0.5f,0.4f}},
		{{-0.3f,-0.6f,0.0f},{0.1f,0.4f,0.5f,0.4f}}
	};

	auto Triangle_Vertex_size = sizeof(TriangleVertex);

	D3D12_HEAP_PROPERTIES Triangle_Props{};
	Triangle_Props.Type = D3D12_HEAP_TYPE_UPLOAD;
	Triangle_Props.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	Triangle_Props.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	Triangle_Props.CreationNodeMask = 1;
	Triangle_Props.VisibleNodeMask = 1;

	D3D12_RESOURCE_DESC Triangle_Resource_Desc{};
	Triangle_Resource_Desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	Triangle_Resource_Desc.Alignment = 0;
	Triangle_Resource_Desc.Width = Triangle_Vertex_size;
	Triangle_Resource_Desc.Height = 1;
	Triangle_Resource_Desc.DepthOrArraySize = 1;
	Triangle_Resource_Desc.MipLevels = 1;
	Triangle_Resource_Desc.Format = DXGI_FORMAT_UNKNOWN;
	Triangle_Resource_Desc.SampleDesc.Count = 1;
	Triangle_Resource_Desc.SampleDesc.Quality = 0;
	Triangle_Resource_Desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	Triangle_Resource_Desc.Flags = D3D12_RESOURCE_FLAG_NONE;

	auto res = Device::instance().GetDevice()->CreateCommittedResource(&Triangle_Props, D3D12_HEAP_FLAG_NONE, &Triangle_Resource_Desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&TriangleVertexBuffer));

	if (FAILED(res))
	{
		assert(false && "ちょうてんバッファがないぞー？");
		return false;
	}

	vertex* data{};

	TriangleVertexBuffer->Map(0, nullptr, reinterpret_cast<void**>(&data));

	memcpy_s(data, Triangle_Vertex_size, TriangleVertex, Triangle_Vertex_size);

	TriangleVertexBuffer->Unmap(0, nullptr);

	VBV_.BufferLocation = TriangleVertexBuffer->GetGPUVirtualAddress();
	VBV_.SizeInBytes = Triangle_Vertex_size;
	VBV_.StrideInBytes = sizeof(vertex);

	return true;
}

bool Triangle_prigon::CreateIndexBuffer()
{
	uint16_t Triangle_Index[]
	{
		0,1,2
	};

	auto TriangleIndex_size = sizeof(Triangle_Index);

	D3D12_HEAP_PROPERTIES TriangleProps;
	TriangleProps.Type = D3D12_HEAP_TYPE_UPLOAD;
	TriangleProps.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	TriangleProps.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	TriangleProps.CreationNodeMask = 1;
	TriangleProps.VisibleNodeMask = 1;

	D3D12_RESOURCE_DESC Triangle_Resource_Desc{};
	Triangle_Resource_Desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	Triangle_Resource_Desc.Alignment = 0;
	Triangle_Resource_Desc.Width = TriangleIndex_size;
	Triangle_Resource_Desc.Height = 1;
	Triangle_Resource_Desc.DepthOrArraySize = 1;
	Triangle_Resource_Desc.MipLevels = 1;
	Triangle_Resource_Desc.Format = DXGI_FORMAT_UNKNOWN;
	Triangle_Resource_Desc.SampleDesc.Count = 1;
	Triangle_Resource_Desc.SampleDesc.Quality = 0;
	Triangle_Resource_Desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	Triangle_Resource_Desc.Flags = D3D12_RESOURCE_FLAG_NONE;

	auto res = Device::instance().GetDevice()->CreateCommittedResource(&TriangleProps, D3D12_HEAP_FLAG_NONE, &Triangle_Resource_Desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&TriangleIndexBuffer));

	uint16_t* data{};

	TriangleIndexBuffer->Map(0, nullptr, reinterpret_cast<void**>(&data));

	memcpy_s(data, TriangleIndex_size, Triangle_Index, TriangleIndex_size);

	TriangleIndexBuffer->Unmap(0,nullptr);

	IBV_.BufferLocation = TriangleIndexBuffer->GetGPUVirtualAddress();
	IBV_.SizeInBytes = TriangleIndex_size;
	IBV_.Format = DXGI_FORMAT_R16_UINT;
	return true;
}