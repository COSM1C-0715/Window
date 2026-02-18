#include "ShapeContainer.h"

void ShapeContainer::Draw(Command_List& commandList,UINT64 id)
{
	auto it = shapes_.find(id);
	if (it == shapes_.end())return;

	it->second->Draw(commandList);
}
