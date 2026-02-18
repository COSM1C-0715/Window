#include "Objects.h"

void Objects::SetDrawCommand(Command_List& commandList, UINT Slot)
{
	commandList.GetCommandList()->SetGraphicsRootDescriptorTable(Slot, ConstantBuffer_.getGpuDescriptorHandle());
}
