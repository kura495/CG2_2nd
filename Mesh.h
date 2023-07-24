#pragma once
#include"DirectXCommon.h"
class Mesh
{
public:
	void Initialize(DirectXCommon* directX,Vector4 Leftbottom,Vector4 top,Vector4 Rightbottom);
	void Draw();
	void Release();
private:
	HRESULT hr;
	DirectXCommon* directX_=nullptr;
	//バーテックスリソース
	ID3D12Resource* vertexResource = nullptr;
	//バーテックスバッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	Vector4* vertexData=nullptr;
	void MakeVertexResource();
	void MakeVertexBufferView();
};
