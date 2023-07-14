#include"GameManager.h"
#include"D3DResourceLeakChecker.h"
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	D3DResourceLeakChecker leakCheck;
	GameManager* gameManager=new GameManager();
	gameManager->Initialize();
	gameManager->Gameloop();
	return 0;
}
