#pragma once
#include"IncludeStruct/VertexData.h"
#include"IncludeStruct/Material.h"
#include<vector>
struct ModelData {
	std::vector<VertexData> vertices;
	MaterialData material;
	int TextureIndex;
};