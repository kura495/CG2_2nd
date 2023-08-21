#pragma once
#pragma once
#include"Base/DirectXCommon.h"
#include"Base/TextureManager.h"
#include"Base/Light.h"
#include"IncludeStruct/Transform.h"
#include"IncludeStruct/VertexData.h"
#include"IncludeStruct/Material.h"
#include"IncludeStruct/TransformationMatrix.h"
#include"Math/MatrixCalc.h"
#include<wrl.h>
#include<numbers>
class Sphere
{
public:

	void Initialize();
	void DrawSphere(const Matrix4x4& ViewMatrix, const uint32_t& TextureHandle);
	void ImGui(const char* Title);
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
	//Sphere用WVPリソース
	Microsoft::WRL::ComPtr<ID3D12Resource>transformationMatrixResourceSphere = nullptr;
	//Sphere用WVPデータ
	TransformationMatrix* transformationMatrixDataSphere = nullptr;
	//Index用
	Microsoft::WRL::ComPtr<ID3D12Resource> indexResourceSphere = nullptr;
	//Index用頂点データ
	uint32_t* indexDataSphere = nullptr;
	//Index用バッファビュー
	D3D12_INDEX_BUFFER_VIEW indexBufferViewSphere{};

	Transform transformSphere{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};

	//イニシャライズで呼び出す
	void MakeVertexBufferViewSphere();
	void MakeIndexBufferViewSphere();
	//
	
};
