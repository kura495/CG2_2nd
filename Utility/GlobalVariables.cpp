#include"GlobalVariables.h"
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
void GlobalVariables::Update()
{
	if (!ImGui::Begin("GlobalVariables", nullptr, ImGuiWindowFlags_MenuBar)) {
		ImGui::End();
		return;
	}
	if (!ImGui::BeginMenuBar())return;

	for (std::map<std::string, Group>::iterator itGroup = datas_.begin(); itGroup != datas_.end(); ++itGroup) {
		//グループ名を取得
		const std::string& groupName = itGroup->first;
		//グループの参照を取得
		Group& group = itGroup->second;

	}

}
#pragma region SetValue
void GlobalVariables::SetValue(const std::string& groupName, const std::string& key, int32_t value)
{
	//グループの参照を取得
	Group& group = datas_[groupName];
	//新しい項目のデータを設定
	Item newItem{};
	newItem.value = value;
	//設定した項目をstd::mapに追加
	group.items[key] = newItem;
}
void GlobalVariables::SetValue(const std::string& groupName, const std::string& key, float value)
{
	//グループの参照を取得
	Group& group = datas_[groupName];
	//新しい項目のデータを設定
	Item newItem{};
	newItem.value = value;
	//設定した項目をstd::mapに追加
	group.items[key] = newItem;
}
void GlobalVariables::SetValue(const std::string& groupName, const std::string& key,const Vector3& value)
{
	//グループの参照を取得
	Group& group = datas_[groupName];
	//新しい項目のデータを設定
	Item newItem{};
	newItem.value = value;
	//設定した項目をstd::mapに追加
	group.items[key] = newItem;
}
#pragma endregion  SetValue