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
	//どのライトを使うか
	int32_t lightFlag = Lighting::NotDo;
	//
	//Sphere用頂点データ
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource = nullptr;
	VertexData* vertexData = nullptr;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource = nullptr;
	Material* materialData = nullptr;
	Vector4 color_ = { 1.0f,1.0f,1.0f,1.0f };

	Microsoft::WRL::ComPtr<ID3D12Resource> indexResource = nullptr;
	uint32_t* indexData = nullptr;
	D3D12_INDEX_BUFFER_VIEW indexBufferView{};

	void MakeVertexBufferView();
	void MakeIndexBufferView();
	
};
