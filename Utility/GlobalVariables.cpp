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
	//指定名のオブジェクトがなければ追加する
	datas_[groupName];
}
