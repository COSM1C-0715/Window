#include "Object.h"
#include<cmath>

void Object::update()
{
	move += 0.02f;
	world = DirectX::XMMatrixTranslation(0.0f, std::sinf(move) * 1.5f, 0.0f);

	color = DirectX::XMFLOAT4(0.1f, 1.0f, 1.0f, 1.0f);
}

DirectX::XMMATRIX Object::World()
{
	return world;
}

DirectX::XMFLOAT4 Object::Color()
{
	return color;
}
