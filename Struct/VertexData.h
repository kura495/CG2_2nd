#pragma once
#include"Vector4.h"
#include"Vector3.h"
#include"Vector2.h"
struct VertexData final {
	Vector4 position;
	Vector2 texcoord;
	Vector3 normal;
};