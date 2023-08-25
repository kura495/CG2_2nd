#pragma once
#include "Base/DirectXCommon.h"
#include "Base/TextureManager.h"
#include "Base/WorldTransform.h"
#include "Base/ViewProjection.h"
#include "IncludeStruct/Transform.h"
#include "IncludeStruct/VertexData.h"
#include "IncludeStruct/Material.h"
#include "IncludeStruct/TransformationMatrix.h"
#include "Math/MatrixCalc.h"
#include <wrl.h>
class Mesh
{
public:
	void Initialize();
	void Draw(const WorldTransform& transform, const ViewProjection& viewProjection, const uint32_t textureHandle);
private:

	Vector4 color_ = {1.0f,1.0f,1.0f,1.0f};
	DirectXCommon* directX_ = nullptr;
	TextureManager* textureManager_ = nullptr;

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

	void MakeVertexBufferView();

};
