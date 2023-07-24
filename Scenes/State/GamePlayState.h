#pragma once
#include"IgameState.h"
#include"Base/MyEngine.h"
#include"GameObject/Camera/Camera.h"
#include"IncludeStruct/Sphere.h"
#include"IncludeStruct/ModelData.h"
#include"Audio/XAudio2.h"
#include"Input/Input.h"
#define DIRECTINPUT_VERSION 0x0800//DirectInputのバージョン指定
#include<dinput.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

class GamePlayState :public GameState
{
public:
	//GamePlayState();
	void Initialize();
	void Update();
	void Draw();

private:

	MyEngine* myEngine = nullptr;
	Camera* camera_ = nullptr;
	Vector4 Left[3] = {
	 {-0.5f,-0.5f,0.0f,1.0f}
	,{-0.5f,-1.5f,0.0f,1.0f}
	,{1.0f,-0.5f,0.0f,1.0f} };
	Vector4 Top[3] = {
	 {0.0f,0.5f,0.0f,1.0f}
	,{0.0f,-0.5f,0.0f,1.0f}
	,{1.5f,0.5f,0.0f,1.0f} };
	Vector4 Right[3] = {
	 {0.5f,-0.5f,0.0f,1.0f}
	,{0.5f,-1.5f,0.0f,1.0f}
	,{2.0f,-0.5f,0.0f,1.0f} };
	Vector4 Color[2] = { 1.0f,1.0f,1.0f,1.0f };
	//Sprite
	Vector4 LeftTop[2] = {
		{ 0.0f,0.0f,0.0f,1.0f },
		{ 640.0f,0.0f,0.0f,1.0f }
	};
	Vector4 LeftBottom[2] = {
		{ 0.0f,360.0f,0.0f,1.0f },
		{ 640.0f,360.0f,0.0f,1.0f }
	};
	Vector4 RightTop[2] = {
		{ 640.0f,0.0f,0.0f,1.0f },
		{ 1280.0f,0.0f,0.0f,1.0f }

	};
	Vector4 RightBottom[2] = {
		{ 640.0f,360.0f,0.0f,1.0f },
		{ 1280.0f,360.0f,0.0f,1.0f }
	};
	Sphere sphere{
		{0.0f,0.0f,0.0f},
		16
	};
	int UV;
	int Ball;
	int Base;
	int Max;
	bool useMonsterBall = true;
	int SphereTexture = 0;
	Transform Box = {
		{2.0f,2.0f,2.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	Transform Box2 = {
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,10.0f},
	};
	ModelData modelData;
	ModelData modelData2;

	Input* input = nullptr;
	std::array<BYTE, 256> keys;
	std::array<BYTE, 256> preKeys;
	XAudio2* Audio=nullptr;
	int mokugyo;
};