#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "GenerateDog.h"


#ifdef WIN32
#include <Windows.h>
#endif // win32



int main(int argc, char* argv[])
{
#ifdef WIN32
	FreeConsole(); // �رտ���̨
	ShowWindow(GetConsoleWindow(), SW_HIDE); // ���ؿ���̨����
#endif // win32

	std::string key = "";
	{
		// ��ȡexe�ļ���·��
		std::filesystem::path exe_path = argv[0];
		//std::filesystem::path exe_path = std::filesystem::current_path().append("GeneralDogKey.exe");

		// �����ļ����ͺ�׺��
		std::string file_name = "GeneralDog.key";

		// ���ļ�������exe��ͬ·����
		std::filesystem::path file_path = exe_path.parent_path().append(file_name);

		// ���ļ�����ȡ�ַ���
		std::ifstream myfile(file_path);

		if (myfile.is_open()) {
			// ���ļ����ݶ�ȡ��һ���ַ�����
			std::string file_content((std::istreambuf_iterator<char>(myfile)),
				std::istreambuf_iterator<char>());
			key = file_content;

			// �����ȡ�����ַ���
			//std::cout << "File content:" << std::endl << file_content << std::endl;
			myfile.close();
		}
		else {
			std::cout << "Unable to open file." << std::endl;
		}
	}
	std::string licensekey = "";
	{
		KeyTimeData keyTimeData;
		keyTimeData.keyTimeType = KeyTimeType::KEYTIME_Mouth;
		keyTimeData.keytimenum = 1;
		licensekey = getLicenseByKey(key, keyTimeData);
	}
	bool same = false;
	{
		same = isSameLicense(licensekey);
		if (!same)
		{
			std::cout << "error not same , need fixed same()" << std::endl;
		}
	}
	if(same)
	{
		// ��ȡexe�ļ���·��
		std::filesystem::path exe_path = argv[0];
		//std::filesystem::path exe_path = std::filesystem::current_path().append("GeneralDogKey.exe");

		// �����ļ����ͺ�׺��
		std::string file_name = "cflLisence.key";

		// ���ļ�������exe��ͬ·����
		std::filesystem::path file_path = exe_path.parent_path().append(file_name);

		// ���ļ���д���ַ���
		std::ofstream myfile(file_path);
		if (myfile.is_open()) {
			myfile << licensekey;
			myfile.close();
			std::cout << "File saved successfully." << std::endl;
		}
		else {
			std::cout << "Unable to open file." << std::endl;
		}
	}

	int chat = getchar();
	return 0;
}