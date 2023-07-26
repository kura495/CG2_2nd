#pragma once
#include"Mesh.h"
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
	
	void DrawModel(const ModelData& modelData, const Vector3& position, const Matrix4x4& ViewMatrix, const Vector4& color);
	ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);
	MaterialData LoadMaterialTemplateFile(const std::string& directoryPath,const std::string&filename);

private:
	

	static const int kMaxTexture=10;
	bool IsusedTextureIndex[kMaxTexture];

	int32_t kClientWidth_;
	int32_t kClientHeight_;

	
	Transform transformObj{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	
	HRESULT hr;
	DirectXCommon*directX_=nullptr;

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

};