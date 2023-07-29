#include "Light.h"

Light* Light::GetInstance()
{
	static Light instance;
	return &instance;
}

void Light::Initialize()
{
	directX_ = DirectXCommon::GetInstance();

	directionalLightResource = CreateBufferResource(sizeof(DirectionalLight));
	directionalLightResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&directionalLightData));
	directionalLightData->color = { 1.0f,1.0f,1.0f,1.0f };
	directionalLightData->direction = { 0.0f,-1.0f,0.0f };
	directionalLightData->intensity = 1.0f;
}

void Light::ImGui(const char* Title)
{
	ImGui::Begin(Title);
	ImGui::SliderFloat3("LightColor", &directionalLightData->color.x, 0, 1, "%.3f");
	ImGui::SliderFloat3("Lightpotision", &directionalLightData->direction.x, -10, 10, "%.3f");
	ImGui::End();
}
Microsoft::WRL::ComPtr<ID3D12Resource> Light::CreateBufferResource(size_t sizeInBytes)
{
	Microsoft::WRL::ComPtr<ID3D12Resource> Resource = nullptr;
	D3D12_HEAP_PROPERTIES uploadHeapProperties{};
	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
	D3D12_RESOURCE_DESC ResourceDesc{};
	ResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	ResourceDesc.Width = sizeInBytes;
	ResourceDesc.Height = 1;
	ResourceDesc.DepthOrArraySize = 1;
	ResourceDesc.MipLevels = 1;
	ResourceDesc.SampleDesc.Count = 1;
	ResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	//頂点リソースを作る
	HRESULT hr = directX_->GetDevice()->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE, &ResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&Resource));
	assert(SUCCEEDED(hr));
	return Resource;
}