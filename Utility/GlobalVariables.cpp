#include"GlobalVariables.h"
GlobalVariables::GlobalVariables()
{

}

GlobalVariables::~GlobalVariables()
{
}

GlobalVariables* GlobalVariables::GetInstance()
{
	static GlobalVariables instance;
	return &instance;
}

void GlobalVariables::CreateGroup(const std::string& groupName)
{
	//�w�薼�̃I�u�W�F�N�g���Ȃ���Βǉ�����
	datas_[groupName];
}
