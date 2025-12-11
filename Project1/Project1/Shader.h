#include<d3d12.h>
#include"Device.h"
#pragma once
class Shader
{
public:
	ID3DBlob* VertexShader;
	ID3DBlob* PixcelShader;
public:
	Shader() = default;
	~Shader();

	bool Create(Device& device);
	ID3DBlob* vertexShader();
	ID3DBlob* pixcelShader();
};

