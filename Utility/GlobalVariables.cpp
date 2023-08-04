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
	//メニューバーを作る
	if (!ImGui::Begin("GlobalVariables", nullptr, ImGuiWindowFlags_MenuBar)) {
		ImGui::End();
		return;
	}
	if (!ImGui::BeginMenuBar())return;
	//各グループごとに行う処理をfor文でdatas_が終わりにつくまでやる
	for (std::map<std::string, Group>::iterator itGroup = datas_.begin(); itGroup != datas_.end(); ++itGroup) {
		//グループ名を取得 itGroup->first = キー
		const std::string& groupName = itGroup->first;
		//グループの参照を取得　itGroup->second = 値
		Group& group = itGroup->second;
		//グループのメニューを追加する処理
		if (!ImGui::BeginMenu(groupName.c_str()))continue;

		//各グループの各項目ごとに行う処理をfor文でやる
		for (std::map<std::string, Item>::iterator itItem = group.items.begin(); itItem != group.items.end(); ++itItem) {
			//項目名を取得(floatやVector3などの名前)
			const std::string& itemName = itItem->first;
			//項目の値を取得
			Item& item = itItem->second;

			//項目名によって分岐する
			//int32_t型の値を所持していたら
			if (std::holds_alternative<int32_t>(item.value)) {
					int32_t* ptr = std::get_if<int32_t>(&item.value);
					ImGui::SliderInt(itemName.c_str(), ptr, 0, 100);
				}
			//float型の値を所持していたら
			else if (std::holds_alternative<float>(item.value)) {
					float* ptr = std::get_if<float>(&item.value);
					ImGui::SliderFloat(itemName.c_str(), ptr, 0, 100);
				}
			//Vector3型の値を所持していたら
			else if (std::holds_alternative<Vector3>(item.value)) {
					Vector3* ptr = std::get_if<Vector3>(&item.value);
					ImGui::SliderFloat3(itemName.c_str(), reinterpret_cast<float*>(ptr), -10, 10);
				}
			//読み込んだ型がItem構造体にない時とか
			else {
					assert(false);
				}
		}
		ImGui::EndMenu();
	}
	ImGui::EndMenuBar();
	ImGui::End();
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
void GlobalVariables::SabeFile(const std::string& groupName)
{
	//グループを検索する
	std::map<std::string, Group>::iterator itGroup = datas_.find(groupName);
	//グループが存在するかどうかチェック
	assert(itGroup != datas_.end());
	//変数
	json root;
	//json::objectはstd::mapみたいなもの
	root = json::object();
	//jsonオブジェクト登録する
	root[groupName] = json::object();
	//各グループの各項目ごとに行う処理をfor文でやる
	for (std::map<std::string, Item>::iterator itItem = itGroup->second.items.begin(); itItem != itGroup->second.items.end(); ++itItem) {
		//項目名を取得(floatやVector3などの名前)
		const std::string& itemName = itItem->first;
		//項目の値を取得
		Item& item = itItem->second;
		//項目名によって分岐する
		//int32_t型の値を所持していたら
		if (std::holds_alternative<int32_t>(item.value)) {
			//int32_t型の値を登録
			root[groupName][itemName] = std::get<int32_t>(item.value);
		}
		//float型の値を所持していたら
		else if (std::holds_alternative<float>(item.value)) {
			//float型の値を登録
			root[groupName][itemName] = std::get<float>(item.value);
		}
		//Vector3型の値を所持していたら
		else if (std::holds_alternative<Vector3>(item.value)) {
			//float型のjson配列登録をする
			Vector3 value = std::get<Vector3>(item.value);
			root[groupName][itemName] = json::array({ value.x, value.y, value.z });
		}
		//ディレクトリのパス
		std::filesystem::path dir(kDirectoryPath);
		//ディレクトリがなければ作成する
		if (!std::filesystem::exists(dir)) {
			std::filesystem::create_directory(dir);
		}
		//書き込むjsonファイルのフルパスを合成する
		std::string filePath = kDirectoryPath + groupName + ".json";
		//書き込み用ファイルストリーム
		std::ofstream ofs;
		//ファイルを書き込み用に開く
		ofs.open(filePath);
	}
}