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
    FreeConsole(); // 关闭控制台
    ShowWindow(GetConsoleWindow(), SW_HIDE); // 隐藏控制台窗口
#endif // win32

    std::string myString = generate_key();
    std::cout << myString << std::endl;

    {
        // 获取exe文件的路径
        std::filesystem::path exe_path = argv[0];
        //std::filesystem::path exe_path = std::filesystem::current_path().append("GeneralDogKey.exe");

        // 定义文件名和后缀名
        std::string file_name = "GeneralDog.key";

        // 将文件保存在exe相同路径下
        std::filesystem::path file_path = exe_path.parent_path().append(file_name);

        // 打开文件并写入字符串
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


    int chat = getchar();
    return 0;
}