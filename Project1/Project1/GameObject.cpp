#include "GameObject.h"
#include<DirectXMath.h>
namespace
{
	struct ConstBufferData
	{
		DirectX::XMMATRIX World{};
		DirectX::XMFLOAT4 Color{};
	};
}

void GameObject::Initialize()
{

}
