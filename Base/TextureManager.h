#pragma once
#include"DirectXCommon.h"
#include"externals/DirectXTex/DirectXTex.h"
#include<wrl.h>
#include<array>
class TextureManager
{
public:
	// �f�X�N���v�^�[�̐�
	static const size_t kMaxTexture = 256;

	/// <summary>
	/// �e�N�X�`��
	/// </summary>
	struct Texture {
		// �e�N�X�`�����\�[�X
		Microsoft::WRL::ComPtr<ID3D12Resource> textureResource;
		// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
		CD3DX12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU;
		// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
		CD3DX12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU;
		// ���O
		std::string name;
	};

	static TextureManager* GetInstance();
	void Initialize(DirectXCommon* directX);
	uint32_t LoadTexture(const std::string& filePath);

	/// <summary>
	/// GPUHandle���擾
	/// </summary>
	/// <param name="textureHandle">�e�N�X�`���n���h��</param>
	/// <returns>���\�[�X���</returns>
	const CD3DX12_GPU_DESCRIPTOR_HANDLE& GetGPUHandle(uint32_t textureHandle);
private:

	HRESULT hr;
	
	bool IsusedTextureIndex[kMaxTexture];
	DirectXCommon* directX_ = nullptr;
	// �e�N�X�`���R���e�i
	std::array<Texture, kMaxTexture> textures_;
	//���ԃ��\�[�X
	Microsoft::WRL::ComPtr<ID3D12Resource> intermediateResource[kMaxTexture];
	
	DirectX::ScratchImage ImageFileOpen(const std::string& filePath);
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateTextureResource(Microsoft::WRL::ComPtr<ID3D12Device>device, const DirectX::TexMetadata& metadata);
	Microsoft::WRL::ComPtr<ID3D12Resource> UploadTextureData(Microsoft::WRL::ComPtr<ID3D12Resource> texture, const DirectX::ScratchImage& mipImages);

#pragma region descriptorHeap
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap, uint32_t descriptorSize, uint32_t index);
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap, uint32_t descriptorSize, uint32_t index);
	uint32_t descriptorSizeSRV;
	uint32_t descriptorSizeRTV;
	uint32_t descriptorSizeDSV;
#pragma endregion �f�X�N���v�^
};

