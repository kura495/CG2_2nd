#pragma once
#include<Vector>
#include"VertexData.h"
#include"Material.h"
struct ModelData {
	std::vector<VertexData> vertices;
	MaterialData material;
	int TextureIndex;
};
