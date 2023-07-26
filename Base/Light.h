#pragma once
#include"IncludeStruct/StructLight.h"
#include"Utility/ImGuiManager.h"
#include<d3d12.h>
#include<wrl.h>

class Light
{
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

