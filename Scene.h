#pragma once
#include"Mesh.h"
class Scene
{
public:
	void Initialize(DirectXCommon* directX);
	void Draw();
	void Release();
private:
	Mesh* mesh[10];
};