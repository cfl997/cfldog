#include <GenerateDog.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <cstring>
#include <array>

#include "cflMD5.h"

#define cfl_dog_20230511	20230511
#define cfl_dog_20230512	cfl_dog_20230511+1
#define cfl_dog				cfl_dog_20230512


//--------------------------------------CryptoPP------------------------------------------------

#include <iomanip>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/base64.h>

using namespace CryptoPP;

void encryptMessage(const std::string& plainText, const byte key[], const byte iv[], std::string& encodedCipherText)
{
	// Encrypt the message using AES in CBC mode with padding
	CBC_Mode<AES>::Encryption encryptor(key, AES::DEFAULT_KEYLENGTH, iv);
	std::string cipherText;
	StringSource(plainText, true, new StreamTransformationFilter(encryptor, new StringSink(cipherText)));

	// Base64 encode the encrypted data
	StringSource(cipherText, true, new Base64Encoder(new StringSink(encodedCipherText)));
}

void decryptMessage(const std::string& encodedCipherText, const byte key[], const byte iv[], std::string& decryptedText)
{
	// Base64 decode the encrypted data
	std::string decodedCipherText;
	StringSource(encodedCipherText, true, new Base64Decoder(new StringSink(decodedCipherText)));

	// Decrypt the message
	CBC_Mode<AES>::Decryption decryptor(key, AES::DEFAULT_KEYLENGTH, iv);
	StringSource(decodedCipherText, true, new StreamTransformationFilter(decryptor, new StringSink(decryptedText)));
}

#if  (cfl_dog == cfl_dog_20230511)
// 128-bit AES key
byte key[AES::DEFAULT_KEYLENGTH] = { 0x7c, 0x5c, 0xc5, 0x53, 0x0f, 0x61, 0x97, 0xc4, 0x3a, 0x42, 0x5d, 0x5f, 0x5d, 0xcb, 0xcb, 0x98 };
// 16-byte initialization vector
byte iv[AES::BLOCKSIZE] = { 0x39, 0x5a, 0x5e, 0x09, 0xa4, 0x11, 0x2f, 0x8e, 0x90, 0x31, 0x8c, 0x42, 0x11, 0xa8, 0xf7, 0x10 };
#endif // (cfl_dog == cfl_dog_20230511)
#if  (cfl_dog == cfl_dog_20230512)
byte key[AES::DEFAULT_KEYLENGTH] = { 0x7c, 0x5c, 0xc5, 0x53, 0x0f, 0x61, 0x97, 0xc4, 0x3a, 0x42, 0x5d, 0x5f, 0x5d, 0xcb, 0xcb, 0x97 };
byte iv[AES::BLOCKSIZE] = { 0x39, 0x5a, 0x5e, 0x09, 0xa4, 0x11, 0x2f, 0x8e, 0x90, 0x31, 0x8c, 0x42, 0x11, 0xa8, 0xf7, 0x10 };
#endif // (cfl_dog == cfl_dog_20230511) 

std::string getAES(const std::string& srcSecret)
{
	// Encrypt the message
	std::string encodedCipherText;
	encryptMessage(srcSecret, key, iv, encodedCipherText);
	return encodedCipherText;

}
std::string returnAES(const std::string& srcAES)
{
	// Decrypt the message
	std::string decryptedText;
	decryptMessage(srcAES, key, iv, decryptedText);
	return decryptedText;
}


//--------------------------------------CryptoPP------------------------------------------------


#ifdef unix
std::string get_cpu_id()
{
	std::string cpu_id;
	std::ifstream cpuinfo("/proc/cpuinfo");
	if (cpuinfo.is_open()) {
		std::string line;
		while (std::getline(cpuinfo, line)) {
			if (line.substr(0, 3) == "cpu") {
				auto colon_pos = line.find(':');
				if (colon_pos != std::string::npos) {
					auto cpu_id_substr = line.substr(colon_pos + 2);
					cpu_id_substr.erase(std::remove_if(cpu_id_substr.begin(), cpu_id_substr.end(),
						[](char c) { return std::isspace(static_cast<unsigned char>(c)); }), cpu_id_substr.end());
					cpu_id = cpu_id_substr;
					break;
				}
			}
		}
	}
	return cpu_id;
}
#else
#include <Windows.h>
#include <intrin.h>
std::string get_cpu_id()
{

	std::string cpu_id;
	std::string cmd = "wmic cpu get processorid";
	std::array<char, 128> buffer;
	std::shared_ptr<FILE> pipe(_popen(cmd.c_str(), "r"), _pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), 128, pipe.get()) != nullptr) {
		cpu_id += buffer.data();
	}
	// Remove whitespace and newline characters from the string
	cpu_id.erase(std::remove_if(cpu_id.begin(), cpu_id.end(), [](char c) { return std::isspace(c) || c == '\n'; }), cpu_id.end());
	cpu_id.erase(0, 11);
	if (cpu_id.size() == 32)
		cpu_id.erase(0, 16);
	if (cpu_id.size() < 16)
		std::cout << "id is small 16" << std::endl;
	return cpu_id;

}
#endif

std::string addMySelfStr(const std::string& cpu_id)
{
	std::string salt = std::to_string(cfl_dog);
	std::string str = cpu_id + salt;
	return std::move(str);
}

static int layerKeyNums = 2;

GeneralDOG_API std::string generate_key()
{
	std::string cpu_id = get_cpu_id();
	if (cpu_id.empty()) {
		std::cout << "id is empty" << std::endl;
		return "";
	}
	std::string str = addMySelfStr(cpu_id);
	return getLicenseByKey(str);
}

GeneralDOG_API std::string getLicenseByKey(const std::string& key)
{
	std::string str = key;
	for (UINT16 i = 0; i < layerKeyNums; i++)
	{
		str = getAES(str);
	}
	return std::move(str);
}


GeneralDOG_API std::string getLicenseByKey(const std::string& key, KeyTimeData keyTimeData)
{
	std::string srcKey = key;
	{
		//这里先returnaes这个层数和generate_key的层数一致
		for (UINT16 i = 0; i < layerKeyNums; i++)
		{
			srcKey = returnAES(srcKey);
		}
	}
	std::string timeStr = "";
	if (keyTimeData.keyTimeType != KeyTimeType::KEYTIME_NULL)
	{
		KeyTimer keytimer;
		timeStr = keytimer.getTimeByType(keyTimeData.keyTimeType, keyTimeData.keytimenum, keyTimeData.isAdd);
	}
	srcKey += KeyTimerStr;

	if (timeStr != "")
	{
		srcKey += HasKeyTimeStr;
		srcKey += KeyTimeTypeStr + ":" + std::to_string(static_cast<int>(keyTimeData.keyTimeType)) + " ";
		srcKey += KeyTimeNumStr + ":" + std::to_string(keyTimeData.keytimenum) + " ";
		srcKey += KeyTimerStr;
		srcKey += ":";
	}

	srcKey += timeStr;

	return getLicenseByKey(srcKey);
}

/*
* oldkey key值
* return 根据license的时间类型，往回推导的时间
*/
std::string getValidTimeStr(const std::string& oldkey)
{
	KeyTimeData keyTimeData;
	int TimeTyp = getTimeType(oldkey);
	int TimeNum = getKeyTimeNum(oldkey);
	//std::string oldTime = getKeyTimer(oldkey);

	keyTimeData.keyTimeType = KeyTimeType(TimeTyp);
	keyTimeData.keytimenum = TimeNum;
	keyTimeData.isAdd = false;

	KeyTimer keytimer;
	std::string timeStr = keytimer.getTimeByType(keyTimeData.keyTimeType, keyTimeData.keytimenum, keyTimeData.isAdd);
	return timeStr;
}

static int flag = 100;
GeneralDOG_API bool isSameLicense(const std::string& licenseKey)
{
	std::string oldLicensekey = returnAES(licenseKey);
	while (oldLicensekey.find(KeyTimerStr) == std::string::npos&& --flag>0)
	{
		oldLicensekey = returnAES(oldLicensekey);
	}
	bool isTimeValid = true;
	{
		//获得之前的key应该是多少
		//如果比原本的时间小 
		if (oldLicensekey.find(HasKeyTimeStr) != std::string::npos)
		{
			KeyTimer keyTimer;
			std::string validTime = getValidTimeStr(oldLicensekey);
			auto  validTime_t = keyTimer.getTime_tByStr(validTime);

			std::string oldTime = getKeyTimer(oldLicensekey);
			auto  oldTime_t = keyTimer.getTime_tByStr(oldTime);

			isTimeValid = validTime_t <= oldTime_t;
		}
	}
	std::string cpu_id = get_cpu_id();
	if (cpu_id.empty()) {
		std::cout << "dog key is error" << std::endl;
		return false;
	}

	std::string str = addMySelfStr(cpu_id);
	std::string hash = getLicenseByKey(str);

	std::string oldkey = oldLicensekey.substr(0, oldLicensekey.find(KeyTimerStr));
	std::string oldhash = getLicenseByKey(oldkey);


	return hash == oldhash && isTimeValid;
}
