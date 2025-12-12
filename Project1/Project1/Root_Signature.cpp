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
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	rootSignatureDesc.NumParameters = 0;
	rootSignatureDesc.pParameters = nullptr;
	rootSignatureDesc.NumStaticSamplers = 0;
	rootSignatureDesc.pStaticSamplers = nullptr;
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
