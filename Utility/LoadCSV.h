#pragma once
#include<string>
#include<sstream>
#include<fstream>
#include<cassert>
/// <summary>
	/// CSV��ǂݍ���
	/// </summary>
	/// <param name="filename">�t�@�C����</param>
	/// <returns></returns>
std::stringstream LoadCSVData(const std::string& filename);
