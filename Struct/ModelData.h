#pragma once
#include<Vector>
#include"Struct/VertexData.h"
#include"Struct/Material.h"
struct ModelData {
	std::vector<VertexData> vertices;
	MaterialData material;
	int TextureIndex;
};
