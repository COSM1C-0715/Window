#include "Shader.h"
#include<cassert>
#include<string>
#include<D3Dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

Shader::~Shader()
{
	if (VertexShader)
	{
		VertexShader->Release();
		VertexShader = nullptr;
	}
	if (PixcelShader)
	{
		PixcelShader->Release();
		PixcelShader = nullptr;
	}
}

bool Shader::Create(Device& device)
{
	std::string filepath = "VertexShader.hlsl";
	std::wstring temp = std::wstring(filepath.begin(), filepath.end());

	ID3DBlob* error{};

	auto res = D3DCompileFromFile(temp.data(), nullptr, nullptr, "vs", "vs_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &VertexShader, &error);

	if (FAILED(res))
	{
		char* p = static_cast<char*>(error->GetBufferPointer());
		assert(false&&"ピクセルシェーダのコンパイルに失敗しちゃった");
	}

	if (error)
	{
		error->Release();
	}

	return true;
}

ID3DBlob* Shader::vertexShader()
{
	if (!VertexShader)
	{
		assert(false && "頂点シェーダがなーい");
	}

	return VertexShader;
}

ID3DBlob* Shader::pixcelShader()
{
	if (!PixcelShader)
	{
		assert(false && "ピクセルシェーダがなーい");
	}

	return PixcelShader;
}