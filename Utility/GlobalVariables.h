#pragma once
#include"IncludeStruct/Vector3.h"
#include<variant>
#include<map>
#include<string>
struct Item {
	//���ڂ̒l
	std::variant<int32_t, float, Vector3> value;
};
struct Group {
	std::map<std::string, Item> items;
};

class GlobalVariables
{
public:
	static GlobalVariables* GetInstance();
	void CreateGroup(const std::string& groupName);
private:
	GlobalVariables()=default;
	~GlobalVariables()=default;
	GlobalVariables(const GlobalVariables& ch) = delete;
	GlobalVariables& operator=(const GlobalVariables& ch) = delete;
	//�S�f�[�^
	std::map<std::string, Group> datas_;
};

