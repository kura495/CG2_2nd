#pragma once
#pragma once
#include "DirectXCommon.h"
#include "TextureManager.h"
#include "Light.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Transform.h"
#include "VertexData.h"
#include "Material.h"
#include "MatrixCalc.h"
#include <wrl.h>
#include <numbers>
class Sphere
{
public:

	void Initialize();
	void Draw(const WorldTransform& transform, const ViewProjection& viewProjection, const uint32_t& TextureHandle);
private:
	DirectXCommon* directX_ = nullptr;
	TextureManager* textureManager_ = nullptr;
	Light* light_ = nullptr;
	//分割数
	const int kSubdivision = 16;
	//
	//フラグたち
	int32_t lightFlag = Lighting::NotDo;
	//
	//Sphere用頂点データ
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResourceSphere = nullptr;
	//Sphere用頂点データ
	VertexData* vertexDataSphere = nullptr;
	//Sphere用バーテックスバッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSphere{};
	//マテリアルリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResourceSphere = nullptr;
	//色データ
	Material* materialDataSphere = nullptr;
	Vector4 color_ = { 1.0f,1.0f,1.0f,1.0f };
	//Index用
	Microsoft::WRL::ComPtr<ID3D12Resource> indexResourceSphere = nullptr;
	//Index用頂点データ
	uint32_t* indexDataSphere = nullptr;
	//Index用バッファビュー
	D3D12_INDEX_BUFFER_VIEW indexBufferViewSphere{};

	//イニシャライズで呼び出す
	void MakeVertexBufferViewSphere();
	void MakeIndexBufferViewSphere();
	//
	
};
