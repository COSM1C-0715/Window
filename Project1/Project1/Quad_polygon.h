#include<d3d12.h>
#include <dxgi1_4.h>
#include"Device.h"
#include"Command_List.h"
#include <wrl/client.h>
#include<DirectXMath.h>
#include"About_GameObject.h"
#include"Shape.h"
#pragma once
class Quad_polygon : public Shape
{
public:
	Quad_polygon() = default;
	~Quad_polygon() = default;
private:
	virtual bool CreateVertexBuffer() override;
	bool CreateIndexBuffer() override;
	ID3D12CommandList* Draw(Command_List& commandlist);
};