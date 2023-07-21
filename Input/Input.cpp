#include"Input.h"

void Input::Initialize(WinApp*winApp_){
	//DirectInput�̃I�u�W�F�N�g���쐬
	hr = DirectInput8Create(winApp_->GetHINSTANCE(),DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&directInput,nullptr);
	assert(SUCCEEDED(hr));
	//�L�[�{�[�h�f�o�C�X�𐶐�
	hr = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(hr));
	//���̓f�[�^�`���̃Z�b�g

	hr = keyboard->SetDataFormat(&c_dfDIKeyboard);
	assert(SUCCEEDED(hr));

}
