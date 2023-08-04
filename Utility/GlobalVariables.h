#pragma once
#include"IncludeStruct/Vector3.h"
#include"Utility/ImGuiManager.h"
#include"externals/nlohmann/json.hpp"
#include<variant>
#include<map>
#include<string>
#include<fstream>
struct Item {
	//項目の値
	std::variant<int32_t, float, Vector3> value;
};
struct Group {
	std::map<std::string, Item> items;
};
using json = nlohmann::json;
class GlobalVariables
{
public:
	static GlobalVariables* GetInstance();
	void CreateGroup(const std::string& groupName);
	//毎フレーム処理
	void Update();
	//値のセット(int)
	void SetValue(const std::string& groupName, const std:: string& key, int32_t value);
	//値のセット(float)
	void SetValue(const std::string& groupName, const std:: string& key, float value);
	//値のセット(Vector3)
	void SetValue(const std::string& groupName, const std:: string& key, const Vector3& value);
	//ファイルにデータを保存
	void SabeFile(const std::string& groupName);
private:
	GlobalVariables()=default;
	~GlobalVariables()=default;
	GlobalVariables(const GlobalVariables& ch) = delete;
	GlobalVariables& operator=(const GlobalVariables& ch) = delete;
	//全データ
	std::map<std::string, Group> datas_;
	//jsonファイルの保存先のパス
	const std::string kDirectoryPath = "resources/GlobalVariables/";
};

