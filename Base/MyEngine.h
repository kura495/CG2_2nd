#pragma once
#include"Mesh.h"
#include"IncludeStruct\Sphere.h"
#include"IncludeStruct\ModelData.h"
#include"IncludeStruct\StructLight.h"
#include<numbers>
#include<fstream>
#include<sstream>

class MyEngine
{
public:
	static MyEngine* GetInstance();
	void Initialize(DirectXCommon* directX, int32_t kClientWidth, int32_t kClientHeight);
	void ImGui();

	//void VertexReset();
	//void DrawSprite(const Vector4& LeftTop, const Vector4& LeftBottom, const Vector4& RightTop, const Vector4& RightBottom,const Vector4& color, const int Index);
	//void DrawSphere(const Sphere& sphere, const Matrix4x4& ViewMatrix, const Vector4& color, const int Index);
	//void DrawBox(const float& width, const float& hight, const float& depth, const Transform& transform,const Matrix4x4& ViewportMatrix, const Vector4& color, const int Index);
	//void DrawModel(const ModelData& modelData, const Vector3& position, const Matrix4x4& ViewMatrix, const Vector4& color);
	//ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);
	//MaterialData LoadMaterialTemplateFile(const std::string& directoryPath,const std::string&filename);

private:
	const int kSubdivision = 16;

	static const int kMaxTexture=10;
	bool IsusedTextureIndex[kMaxTexture];

	int32_t kClientWidth_;
	int32_t kClientHeight_;

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
	Transform transformSphere{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	Transform transformObj{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	
	HRESULT hr;
	DirectXCommon*directX_=nullptr;


	#pragma region sprite
	static const int kMaxSprite=3;
	static const int kMaxSpriteVertex= kMaxSprite *6;
	bool IsusedSpriteIndex[kMaxSprite];
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
	//void MakeVertexBufferViewSprite();
	//void MakeIndexBufferViewSprite();
	#pragma endregion スプライト
	#pragma region Sphere
	//Sphere用頂点データ
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResourceSphere = nullptr;
	//Sphere用頂点データ
	VertexData* vertexDataSphere=nullptr;
	//Sphere用バーテックスバッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSphere{};
	//マテリアルリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResourceSphere = nullptr;
	//色データ
	Material* materialDataSphere = nullptr;
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
	void MakeVertexBufferViewSphere();
	void MakeIndexBufferViewSphere();

	#pragma endregion 球
	#pragma region Light
	Microsoft::WRL::ComPtr<ID3D12Resource>directionalLightResource = nullptr;
	DirectionalLight* directionalLightData = nullptr;
	#pragma endregion ライト
	#pragma region Box
	static const int kMaxBox = 3;
	static const int kMaxBoxVertex = kMaxBox * 36;
	bool IsusedBoxIndex[kMaxBox];
	//Box用頂点データ
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResourceBox = nullptr;
	//Box用頂点データ
	VertexData* vertexDataBox = nullptr;
	//Box用バーテックスバッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewBox{};
	//マテリアルリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResourceBox = nullptr;
	//色データ
	Material* materialDataBox = nullptr;
	//Box用WVPリソース
	Microsoft::WRL::ComPtr<ID3D12Resource>transformationMatrixResourceBox = nullptr;
	//Box用WVPデータ
	TransformationMatrix* transformationMatrixDataBox = nullptr;
	//Index用
	Microsoft::WRL::ComPtr<ID3D12Resource> indexResourceBox = nullptr;
	//Index用頂点データ
	uint32_t* indexDataBox = nullptr;
	//Index用バッファビュー
	D3D12_INDEX_BUFFER_VIEW indexBufferViewBox{};
	void MakeVertexBufferViewBox();
	void MakeIndexBufferViewBox();
#pragma endregion ボックス
	#pragma region obj

	ModelData modelData;
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResourceObj=nullptr;
	//Obj用頂点データ
	VertexData* vertexDataObj = nullptr;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewObj{};
	//マテリアルリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResourceObj = nullptr;
	//色データ
	Material* materialDataObj = nullptr;
	//Sprite用WVPリソース
	Microsoft::WRL::ComPtr<ID3D12Resource>transformationMatrixResourceObj = nullptr;
	//Sprite用WVPデータ
	TransformationMatrix* transformationMatrixDataObj = nullptr; 
#pragma endregion obj

	

#pragma region ImageLoad
	
#pragma endregion 画像読み込み
};