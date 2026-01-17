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

	D3D12_HEAP_PROPERTIES heappros;
	heappros.Type = D3D12_HEAP_TYPE_UPLOAD;
}
