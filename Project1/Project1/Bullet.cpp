#include "Bullet.h"
#include<cassert>
#include<DirectXMath.h>
namespace
{
	struct vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT4 color;
	};
}

bool Bullet::createvertex(Device& device)
{
	vertex bulletvertex[] =
	{
		{{0.1f,0.8f,0.0f},{0.1f,0.1f,0.1f,1.0f}},
		{{0.1f,0.4f,0.0f},{0.1f,0.1f,0.1f,1.0f}},
		{{0.8f,-0.9f,0.0f},{0.1f,0.1f,0.1f,1.0f}}
	};

	auto bullet_size = sizeof(bulletvertex);

	D3D12_HEAP_PROPERTIES heappros{};
	heappros.Type = D3D12_HEAP_TYPE_UPLOAD;
	heappros.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heappros.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heappros.CreationNodeMask = 1;
	heappros.VisibleNodeMask = 1;

	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Alignment = 0;
	resDesc.Width = bullet_size;
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.Format = DXGI_FORMAT_UNKNOWN;
	resDesc.SampleDesc.Count = 1;
	resDesc.SampleDesc.Quality = 0;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

	auto res = device.GetDevice()->CreateCommittedResource(&heappros, D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&bullet_vertexbuffer));

	if (FAILED(res))
	{
		assert(false && "頂点バッファがないぞー？");
		return false;
	}

	vertex* data{};

	res = bullet_vertexbuffer->Map(0, nullptr, reinterpret_cast<void**>(&data));

	if (FAILED(res))
	{
		assert(false && "頂点バッファのマップがないぞー？");
		return false;
	}

	memcpy_s(data, bullet_size, bulletvertex, bullet_size);

	bullet_vertexbuffer->Unmap(0, nullptr);

	bullet_vbv.BufferLocation = bullet_vertexbuffer->GetGPUVirtualAddress();
	bullet_vbv.SizeInBytes = bullet_size;
	bullet_vbv.StrideInBytes = sizeof(vertex);
}

bool Bullet::createindex(Device& device)
{
	uint16_t Bullet_Index[]
	{
		0,1,2
	};

	auto Bullet_Index_Buffer_Size = sizeof(Bullet_Index);

	D3D12_HEAP_PROPERTIES heappros{};
	heappros.Type = D3D12_HEAP_TYPE_UPLOAD;
	heappros.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heappros.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heappros.CreationNodeMask = 1;
	heappros.VisibleNodeMask = 1;

	D3D12_RESOURCE_DESC HeapDesc{};
	HeapDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	HeapDesc.Alignment = 0;
	HeapDesc.Width = Bullet_Index_Buffer_Size;
	HeapDesc.Height = 1;
	HeapDesc.DepthOrArraySize = 1;
	HeapDesc.MipLevels = 1;
	HeapDesc.Format = DXGI_FORMAT_UNKNOWN;
	HeapDesc.SampleDesc.Count = 1;
	HeapDesc.SampleDesc.Quality = 0;
	HeapDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	HeapDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

	auto res = device.GetDevice()->CreateCommittedResource(&heappros,D3D12_HEAP_FLAG_NONE,&HeapDesc,D3D12_RESOURCE_STATE_GENERIC_READ,nullptr,IID_PPV_ARGS(&bullet_indexbuffer));

	if (FAILED(res))
	{
		assert(false && "インデックスバッファがないぞー？");
		return false;
	}

	uint16_t* data{};

	res = bullet_indexbuffer->Map(0, nullptr, reinterpret_cast<void**>(&data));
	if (FAILED(res))
	{
		assert(false && "インデックスバッファのマップがないぞー？");
		return false;
	}

	memcpy_s(data, Bullet_Index_Buffer_Size, Bullet_Index, Bullet_Index_Buffer_Size);

	bullet_indexbuffer->Unmap(0, nullptr);

	bullet_ibv.BufferLocation = bullet_indexbuffer->GetGPUVirtualAddress();
	bullet_ibv.SizeInBytes = Bullet_Index_Buffer_Size;
	bullet_ibv.Format = DXGI_FORMAT_R16_UINT;
}

void Bullet::BulletDraw(Command_List& C_List)
{
	C_List.GetCommandList()->IASetVertexBuffers(0, 1, &bullet_vbv);

	C_List.GetCommandList()->IASetIndexBuffer(&bullet_ibv);

	C_List.GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	C_List.GetCommandList()->DrawIndexedInstanced(3,1,0,0,0);
}
