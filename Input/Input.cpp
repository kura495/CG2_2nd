#include"Input.h"

void Input::Initialize(WinApp*winApp_){
	hr = DirectInput8Create(winApp_->GetHINSTANCE(),DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&directInput,nullptr);
	assert(SUCCEEDED(hr));
	hr = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
}
