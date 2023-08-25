#pragma once
#include "Mesh.h"
#include "ModelData.h"
#include "Base/Light.h"
#include <numbers>
#include <fstream>


class MyEngine
{
public:
	static MyEngine* GetInstance();
	void Initialize(DirectXCommon* directX);

private:
	MyEngine() = default;
	~MyEngine() = default;
	MyEngine(const MyEngine& obj) = delete;
	MyEngine& operator=(const MyEngine& obj) = delete;

	static const int kMaxTexture=10;
	bool IsusedTextureIndex[kMaxTexture];

	int32_t kClientWidth_;
	int32_t kClientHeight_;

	HRESULT hr;
	DirectXCommon*directX_=nullptr;

};