#include "Shape.h"

bool Shape::Create()
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

void Shape::Draw(Command_List& commandList)
{
	commandList.GetCommandList()->IASetVertexBuffers(0, 1, &VBV_);

	commandList.GetCommandList()->IASetIndexBuffer(&IBV_);

	commandList.GetCommandList()->IASetPrimitiveTopology(Toporogy_);

	commandList.GetCommandList()->DrawIndexedInstanced(IndexCount_,1,0,0,0);
}
