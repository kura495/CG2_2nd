#pragma once
#include"DirectXCommon.h"
#include"externals/DirectXTex/DirectXTex.h"
#include<wrl.h>
class TextureManager
{
public:
	static TextureManager* GetInstance();
	void Initialize(DirectXCommon* directX);
	uint32_t LoadTexture(const std::string& filePath);
private:
	HRESULT hr;
	static const int kMaxTexture = 10;
	bool IsusedTextureIndex[kMaxTexture];
	DirectXCommon* directX_ = nullptr;
	//テクスチャデータ
	Microsoft::WRL::ComPtr<ID3D12Resource> textureResource[kMaxTexture] = { nullptr };
	//中間リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> intermediateResource[kMaxTexture];
	//descriptorHandle
	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU[kMaxTexture];
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU[kMaxTexture];

	DirectX::ScratchImage ImageFileOpen(const std::string& filePath);
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateTextureResource(Microsoft::WRL::ComPtr<ID3D12Device>device, const DirectX::TexMetadata& metadata);
	Microsoft::WRL::ComPtr<ID3D12Resource> UploadTextureData(Microsoft::WRL::ComPtr<ID3D12Resource> texture, const DirectX::ScratchImage& mipImages);

#pragma region descriptorHeap
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap, uint32_t descriptorSize, uint32_t index);
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap, uint32_t descriptorSize, uint32_t index);
	uint32_t descriptorSizeSRV;
	uint32_t descriptorSizeRTV;
	uint32_t descriptorSizeDSV;
#pragma endregion デスクリプタ
};

