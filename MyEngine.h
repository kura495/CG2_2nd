#pragma once
#include"DirectXCommon.h"
#include"MatrixCalc.h"
#include"Matrix4x4.h"
#include"Transform.h"
#include"externals/DirectXTex/DirectXTex.h"
class MyEngine
{
public:
	void Initialize(DirectXCommon* directX);

	void Draw(const Vector4& Leftbottom, const Vector4& top, const Vector4& Rightbottom, const Vector4& color, const Transform& transform,const Matrix4x4& ViewMatrix);

	void Release();

	DirectX::ScratchImage LoadTexture(const std::string& filePath);
	ID3D12Resource* CreateTextureResource(ID3D12Device*device,const DirectX::TexMetadata& metadata);
	void UploadTextureData(ID3D12Resource* texture,const DirectX::ScratchImage&mipImages);
private:
	HRESULT hr;
	DirectXCommon* directX_=nullptr;
	//バーテックスリソース
	ID3D12Resource* vertexResource = nullptr;
	//頂点データ
	Vector4* vertexData;
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
	
	void MakeVertexResource();
	void MakeVertexBufferView();

	ID3D12Resource* CreateBufferResource(size_t sizeInBytes);
};
