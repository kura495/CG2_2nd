#pragma once
#include"Mesh.h"
#include"IncludeStruct\ModelData.h"
#include"IncludeStruct\StructLight.h"
#include<numbers>
#include<fstream>


class MyEngine
{
public:
	static MyEngine* GetInstance();
	void Initialize(DirectXCommon* directX, int32_t kClientWidth, int32_t kClientHeight);

private:
	
	static const int kMaxTexture=10;
	bool IsusedTextureIndex[kMaxTexture];

	int32_t kClientWidth_;
	int32_t kClientHeight_;

	HRESULT hr;
	DirectXCommon*directX_=nullptr;

};