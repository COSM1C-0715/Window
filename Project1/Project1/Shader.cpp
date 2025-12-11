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