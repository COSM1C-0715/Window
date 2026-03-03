#pragma once
#include<d3d12.h>
namespace porigon
{
	struct DrawingType
	{
		D3D12_PRIMITIVE_TOPOLOGY Strip = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
		D3D12_PRIMITIVE_TOPOLOGY list = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	};

	DrawingType type;
}

namespace id
{
	template<class T>
	UINT64 Get()
	{
		static char val{};
		return reinterpret_cast<UINT64>(&val);
	}
}