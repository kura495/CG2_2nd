#pragma once
#include"DirectX.h"
class DrawEngine
{
public:
	void Initialize(DirectX* directX);

	void Draw(Vector4 Leftbottom,Vector4 top,Vector4 Rightbottom, Vector4 color);

	void Release();

private:
	HRESULT hr;
	DirectX* directX_=nullptr;
	//バーテックスリソース
	ID3D12Resource* vertexResource = nullptr;
	//バーテックスバッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	ID3D12Resource* materialResource = nullptr;
	//色データ
	Vector4* materialData = nullptr;
	//頂点データ
	Vector4* vertexData=nullptr;
	void MakeVertexResource();
	void MakeVertexBufferView();
	ID3D12Resource* CreateBufferResource(size_t sizeInBytes);
};
