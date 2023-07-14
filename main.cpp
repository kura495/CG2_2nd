#include"GameManager.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	GameManager* gameManager=new GameManager();
	gameManager->Initialize();
	gameManager->Gameloop();
}
