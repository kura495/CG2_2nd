#include"WinApp.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//ウィンドウクラス
	WinApp* window = nullptr;
	int32_t kClientWidth = 1280;
	int32_t kClientHeight = 720;
	window->Initialize(kClientWidth, kClientHeight);

	MSG msg{};

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//ゲームループ



		}
	}

}