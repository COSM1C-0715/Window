#include "Object_Bullet.h"

void Object_Bullet::initialize(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT4 color_)
{
	world = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);

	color = color_;
}

void Object_Bullet::update()
{
	DirectX::XMFLOAT3 pos{};

	pos.z -= 0.02f;

	DirectX::XMVECTOR temp = DirectX::XMVectorSet(pos.x,pos.y,pos.z,0.0f);

	DirectX::XMVectorAdd(world.r[3],temp);

	color = DirectX::XMFLOAT4(0.1f, 1.0f, 1.0f, 1.0f);
}

DirectX::XMMATRIX Object_Bullet::World()
{
	return world;
}

DirectX::XMFLOAT4 Object_Bullet::Color()
{
	return color;
}
