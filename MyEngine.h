#pragma once
#include"DirectXCommon.h"
#include"MatrixCalc.h"
#include"Matrix4x4.h"
#include"Transform.h"
#include"VertexData.h"
#include"Sphere.h"
#include<numbers>
#include"externals/DirectXTex/DirectXTex.h"
class MyEngine
{
public:
	void Initialize(DirectXCommon* directX, int32_t kClientWidth, int32_t kClientHeight);
	void ImGui();
	void Release();
	void Draw(const Vector4& Leftbottom, const Vector4& top, const Vector4& Rightbottom, const Vector4& color, const Matrix4x4& ViewMatrix);
	void DrawSprite(const Vector4& LeftTop, const Vector4& LeftBottom, const Vector4& RightTop, const Vector4& RightBottom);
	void DrawSphere(const Sphere& sphere, const Matrix4x4& ViewMatrix);
	
	void LoadTexture(const std::string& filePath);


	
private:
	const int kSubdivision = 16;
	int32_t kClientWidth_;
	int32_t kClientHeight_;
	Transform transform{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	Transform transformSprite{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	Transform transformSphere{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};

	HRESULT hr;
	DirectXCommon* directX_=nullptr;

	#pragma region TriAngle
	//バーテックスリソース
	ID3D12Resource* vertexResource = nullptr;
	//頂点データ
	VertexData* vertexData = nullptr;
	//バーテックスバッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	//マテリアルリソース
	ID3D12Resource* materialResource = nullptr;
	//色データ
	Vector4* materialData = nullptr;
	//WVPリソース
	ID3D12Resource* wvpResource = nullptr;
	//WVPデータ
	Matrix4x4* wvpData = nullptr;
	//テクスチャデータ
	ID3D12Resource* textureResource=nullptr;
	#pragma endregion 三角形
	
	#pragma region sprite
	//Sprite用頂点データ
	ID3D12Resource* vertexResourceSprite = nullptr;
	//Sprite用頂点データ
	VertexData* vertexDataSprite = nullptr;
	//Sprite用バーテックスバッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSprite{};
	//Sprite用WVPリソース
	ID3D12Resource* transformationMatrixResourceSprite = nullptr;
	//Sprite用WVPデータ
	Matrix4x4* transformationMatrixDataSprite = nullptr;
	#pragma endregion スプライト

	#pragma region Sphere
	//Sphere用頂点データ
	ID3D12Resource* vertexResourceSphere = nullptr;
	//Sphere用頂点データ
	VertexData* vertexDataSphere=nullptr;
	//Sphere用バーテックスバッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSphere{};
	//Sphere用WVPリソース
	ID3D12Resource* transformationMatrixResourceSphere = nullptr;
	//Sphere用WVPデータ
	Matrix4x4* transformationMatrixDataSphere = nullptr;
	#pragma endregion 球
	
	//中間リソース
	ID3D12Resource* intermediateResource = nullptr;
	//descriptorHandle
	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU;
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU;

	void MakeVertexBufferView();
	void MakeVertexBufferViewSprite();
	void MakeVertexBufferViewSphere();
	ID3D12Resource* CreateBufferResource(size_t sizeInBytes);

#pragma region ImageLoad
	DirectX::ScratchImage ImageFileOpen(const std::string& filePath);
	ID3D12Resource* CreateTextureResource(ID3D12Device*device,const DirectX::TexMetadata& metadata);
	ID3D12Resource* UploadTextureData(ID3D12Resource* texture,const DirectX::ScratchImage&mipImages);
#pragma endregion 画像読み込み
};