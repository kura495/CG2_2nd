#include"Scene.h"
void Scene::Initialize(DirectXCommon*directX)
{
	for (int i = 0; i < 10; i++) {
		mesh[i] = new Mesh();
		mesh[i]->Initialize(directX);
		mesh[i]->vertexData[0] = { -0.2f,0.8f - 0.2f * i,0.0f,1.0f };
		mesh[i]->vertexData[1] = { 0.0f,1.0f - 0.2f * i,0.0f,1.0f };
		mesh[i]->vertexData[2] = { 0.2f,0.8f - 0.2f * i,0.0f,1.0f };
	}
}

void Scene::Draw()
{
	for (int i = 0; i < 10; i++) {
		mesh[i]->Draw();
	}
}

void Scene::Release()
{
	for (int i = 0; i < 10; i++) {
		mesh[i]->Release();
	}
}
