#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "GenerateDog.h"

#define test_AESTime

#ifdef test_AESTime
//#include "cflTime.hpp"
#endif // test_AESTime


int main(int argc, char* argv[])
{
	std::string myString = generate_key();
    std::cout << myString << std::endl;
#ifdef test_AESTime
    KeyTimeData keyTimeData;
    keyTimeData.keyTimeType = KeyTimeType::KEYTIME_Week;
    std::string licensekey = getLicenseByKey(myString, keyTimeData);
    bool same = isSameLicense(licensekey);
    if (!same)
    {
        std::cout << "error not same , need fixed same()" << std::endl;
    }
#endif // test_AESTime


    if(0)
	{
        std::ofstream myfile("cflkey.dog");
        if (myfile.is_open()) {
            myfile << myString;
            myfile.close();
            std::cout << "File saved successfully." << std::endl;
        }
        else {
            std::cout << "Unable to open file." << std::endl;
        }
	}
    {
        // ��ȡexe�ļ���·��
        std::filesystem::path exe_path = argv[0];
        //std::filesystem::path exe_path = std::filesystem::current_path().append("GeneralDogKey.exe");

        // �����ļ����ͺ�׺��
        std::string file_name = "cflkey.dog";

        // ���ļ�������exe��ͬ·����
        std::filesystem::path file_path = exe_path.parent_path().append(file_name);

        // ���ļ���д���ַ���
        std::ofstream myfile(file_path);
        if (myfile.is_open()) {
            myfile << myString;
            myfile.close();
            std::cout << "File saved successfully." << std::endl;
        }
        else {
            std::cout << "Unable to open file." << std::endl;
        }
    }


	int chat=getchar();
	return 0;
}