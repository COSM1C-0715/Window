#include"Device.h"
#include"Shader.h"
#include"Root_Signature.h"
#include<d3d12.h>
#pragma once
class Pipline_state_object
{
public:
	ID3D12PipelineState* pipelinestate;
public:
	Pipline_state_object() = default;
	~Pipline_state_object();

	bool Create(Device& device, Shader& shader, Root_Signature& rootSignature);
	ID3D12PipelineState* GetPipeline();
};

