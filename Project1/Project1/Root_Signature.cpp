#include "Root_Signature.h"
#include<cassert>
Root_Signature::~Root_Signature()
{
	if (rootSignature)
	{
		rootSignature->Release();
		rootSignature = nullptr;
	}
}

bool Root_Signature::Create(Device& device) 
{
	D3D12_DESCRIPTOR_RANGE r0{};
	r0.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	r0.NumDescriptors = 1;
	r0.BaseShaderRegister = 0;
	r0.RegisterSpace = 0;
	r0.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	D3D12_DESCRIPTOR_RANGE r1{};
	r1.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	r1.NumDescriptors = 1;
	r1.BaseShaderRegister = 1;
	r1.RegisterSpace = 0;
	r1.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	constexpr auto paramNum = 2;
	D3D12_ROOT_PARAMETER rootParameters[paramNum]{};
	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rootParameters[0].DescriptorTable.NumDescriptorRanges = 1;
	rootParameters[0].DescriptorTable.pDescriptorRanges = &r0;
	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	rootParameters[1].DescriptorTable.NumDescriptorRanges = 1;
	rootParameters[1].DescriptorTable.pDescriptorRanges = &r1;

	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	rootSignatureDesc.NumParameters = paramNum;
	rootSignatureDesc.pParameters = rootParameters;
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	ID3DBlob* signature{};
	auto res = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, nullptr);

	bool success = SUCCEEDED(res);
	if (!success)
	{
		assert(false && "ルートシグネチャのシリアライズ無理だったー");
	}
	else 
	{
		res = device.GetDevice()->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&rootSignature));

		success &= SUCCEEDED(res);
		if (!success)
		{
			assert(false&&"ルートシグネチャの作成にしっぱーい");
		}
	}
	if (signature)
	{
		signature->Release();
	}
	return success;
}

ID3D12RootSignature* Root_Signature::GetSignature()
{
	if (!rootSignature)
	{
		assert(false&&"ルートシグネチャ作れてなくねー？");
	}

	return rootSignature;
}
