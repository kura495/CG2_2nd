#include"Utility/LoadCSV.h"
std::stringstream LoadCSVData(const std::string& filename)
{
	std::ifstream file;
	file.open(filename);
	assert(file.is_open());
	// �t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
	std::stringstream Commands;
	Commands << file.rdbuf();
	// �t�@�C�������
	file.close();
	return Commands;
}
