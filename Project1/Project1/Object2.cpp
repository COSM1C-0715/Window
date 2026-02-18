#include "Object2.h"

void Object2::initialize(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT4 color_)
{
	world = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);

	color = color_;
}

void Object2::update()
{

}

DirectX::XMMATRIX Object2::World()
{
	return world;
}

DirectX::XMFLOAT4 Object2::Color()
{
	return color;
}
