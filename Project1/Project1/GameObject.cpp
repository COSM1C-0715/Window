#include "GameObject.h"
#include"ShapeContainer.h"
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
	CreateDrawBuffer();
}

void GameObject::SetDrawCommand(Command_List& commandList, UINT slot)
{
	Objects::SetDrawCommand(commandList,slot);
	ShapeContainer::instance().Draw(commandList,ShapeId_);
}

void GameObject::CreateDrawBuffer()
{
	if (!ConstantBuffer_.Createcostantbuffer(sizeof(ConstBufferData)));
	{
		assert(false && "GameObject コンスタントバッファの作成に失敗しました");
	}
}
