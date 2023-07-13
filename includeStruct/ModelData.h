#pragma once
#include<Vector>
#include"includeStruct\VertexData.h"
#include"includeStruct\Material.h"
struct ModelData {
	std::vector<VertexData> vertices;
	MaterialData material;
	int TextureIndex;
};
