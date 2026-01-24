#include "Object.h"
#include "Input.h"
#include<cmath>

void Object::initialize(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT4 color_)
{
	world = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);

	color = color_;
}

void Object::update()
{
	DirectX::XMFLOAT3 pos{};

	if (Input::instance().getKey('W'))
	{
		pos.z += move;
	}
	else if(Input::instance().getKey('A'))
	{
		pos.x -= move;
	}
	else if(Input::instance().getKey('S'))
	{
		pos.z -= move;
	}
	else if(Input::instance().getKey('D'))
	{
		pos.x += move;
	}

	DirectX::XMVECTOR temp = DirectX::XMVectorSet(pos.x,pos.y,pos.z,0.0f);
	world.r[3] = DirectX::XMVectorAdd(world.r[3],temp);

	/*move += 0.02f;
	world = DirectX::XMMatrixTranslation(0.0f, std::sinf(move) * 1.5f, 0.0f);*/

	/*if (Input::instance().getKey('B'))
	{
		
	}*/

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
