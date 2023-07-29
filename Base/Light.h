#pragma once
#include"IncludeStruct/Vector4.h"
#include"IncludeStruct/Vector3.h"
#include"Utility/ImGuiManager.h"
#include<d3d12.h>
#include<wrl.h>
//namespace Lighting{
	enum Lighting {
		NotDo = false,
		harfLambert = 1,
		Lambert = 2,
	};

class Light
{
	struct DirectionalLight {
	Vector4 color;//ライトの色
	Vector3 direction;//ライトの向き
	float intensity;//ライトの輝度
};
public:
	static Light* GetInstance();
	void Initialize();
	void ImGui(const char* Title);
	ID3D12Resource* GetDirectionalLight()const {
		return directionalLightResource.Get(); }
private:
	DirectXCommon* directX_ = nullptr;

	Microsoft::WRL::ComPtr<ID3D12Resource>directionalLightResource = nullptr;
	DirectionalLight* directionalLightData = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(size_t sizeInBytes);
};

