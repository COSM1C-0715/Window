#include"Device.h"
#include<d3d12.h>
#pragma once
class Root_Signature
{
public:
	ID3D12RootSignature* rootSignature;
public:
	Root_Signature() = default;
	~Root_Signature();

	bool Create(Device& device);
	ID3D12RootSignature* GetSignature();
};

