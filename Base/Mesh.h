#pragma once
#include"Base/DirectXCommon.h"
#include"Base/TextureManager.h"
#include"IncludeStruct/Transform.h"
#include"IncludeStruct/VertexData.h"
#include"IncludeStruct/Material.h"
#include"IncludeStruct/TransformationMatrix.h"
#include"Math/MatrixCalc.h"
#include<wrl.h>
class Mesh
{
public:
	void Initialize();
	void Draw(const Matrix4x4& ViewMatrix, const uint32_t textureHandle);
	void ImGui(const char* Title);
private:
	Vector4 color_ = {1.0f,1.0f,1.0f,1.0f};
	DirectXCommon* directX_ = nullptr;
	TextureManager* textureManager_ = nullptr;
	Transform transform{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	Transform uvTranformTriAngle{
	{1.0f,1.0f,1.0f},
	{0.0f,0.0f,0.0f},
	{0.0f,0.0f,0.0f}
	};

	//バーテックスリソース
	Microsoft::WRL::ComPtr<ID3D12Resource>vertexResource = nullptr;
	//頂点データ
	VertexData* vertexData = nullptr;
	//バーテックスバッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	//マテリアルリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource = nullptr;
	//色データ
	Material* materialData = nullptr;
	//WVPリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> wvpResource = nullptr;
	//WVPデータ
	Matrix4x4* wvpData = nullptr;
	static const int kMaxTexture = 10;
	bool IsusedTextureIndex[kMaxTexture];
	//descriptorHandle
	/*D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU[kMaxTexture];
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU[kMaxTexture];*/
	void MakeVertexBufferView();
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(size_t sizeInBytes);
};
