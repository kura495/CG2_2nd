#pragma once
#include"Base/DirectXCommon.h"
#include"Base/TextureManager.h"
#include"IncludeStruct/Transform.h"
#include"IncludeStruct/VertexData.h"
#include"IncludeStruct/Material.h"
#include"IncludeStruct/TransformationMatrix.h"
#include"Math/MatrixCalc.h"
#include<wrl.h>
class Sprite
{
public:
	void Initialize(const Vector4& LeftTop, const Vector4& LeftBottom, const Vector4& RightTop, const Vector4& RightBottom);
	void DrawSprite(const Vector4& color, const uint32_t TextureHandle);
	void ImGui(const char* Title);
private:
	DirectXCommon* directX_ = nullptr;
	TextureManager* textureManager_ = nullptr;
	//Sprite用頂点データ
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResourceSprite = nullptr;
	//Sprite用頂点データ
	VertexData* vertexDataSprite = nullptr;
	//Sprite用バーテックスバッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSprite{};
	//マテリアルリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResourceSprite = nullptr;
	//色データ
	Material* materialDataSprite = nullptr;
	//Sprite用WVPリソース
	Microsoft::WRL::ComPtr<ID3D12Resource>transformationMatrixResourceSprite = nullptr;
	//Sprite用WVPデータ
	TransformationMatrix* transformationMatrixDataSprite = nullptr;
	//Index用
	Microsoft::WRL::ComPtr<ID3D12Resource>indexResourceSprite = nullptr;
	//Index用頂点データ
	uint32_t* indexDataSprite = nullptr;
	//Index用バッファビュー
	D3D12_INDEX_BUFFER_VIEW indexBufferViewSprite{};
	Transform transformSprite{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	Transform uvTranformSprite{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};
	void MakeVertexBufferViewSprite();
	void MakeIndexBufferViewSprite();
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(size_t sizeInBytes);
};
