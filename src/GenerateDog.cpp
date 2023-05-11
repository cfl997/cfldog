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

#define cfl_dog_20230511 "cfl_dog_20230511"
#define cfl_dog	cfl_dog_20230511


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

// 128-bit AES key
byte key[AES::DEFAULT_KEYLENGTH] = { 0x7c, 0x5c, 0xc5, 0x53, 0x0f, 0x61, 0x97, 0xc4, 0x3a, 0x42, 0x5d, 0x5f, 0x5d, 0xcb, 0xcb, 0x98 };
// 16-byte initialization vector
byte iv[AES::BLOCKSIZE] = { 0x39, 0x5a, 0x5e, 0x09, 0xa4, 0x11, 0x2f, 0x8e, 0x90, 0x31, 0x8c, 0x42, 0x11, 0xa8, 0xf7, 0x10 };

std::string getAES(const std::string& srcSecret)
{

	//// The plaintext message to be encrypted
	//std::string plainText = "This is a secret message!";

	//// Print the plaintext message
	//std::cout << "Plain text: " << plainText << std::endl;

	// Encrypt the message
	std::string encodedCipherText;
	encryptMessage(srcSecret, key, iv, encodedCipherText);
	// Print the encrypted message
	//std::cout << "Encrypted text: " << encodedCipherText << std::endl;
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
	cpu_id.erase(0, 16);
	return cpu_id;

}
#endif
//std::string generate_key()
//{
//	std::string cpu_id = get_cpu_id();
//	if (cpu_id.empty()) {
//		return "";
//	}
//	std::string salt = cfl_dog;
//	std::string str = cpu_id + salt;
//	std::string hash = md5(str);
//	return hash;
//}

//int main()
//{
//	std::string key = generate_key();
//	std::cout << "key: " << key << std::endl;
//	return 0;
//}


GeneralDOG_API std::string generate_key()
{
	std::string cpu_id = get_cpu_id();
	if (cpu_id.empty()) {
		return "";
	}
	std::string salt = cfl_dog;
	std::string str = cpu_id + salt;
	std::string hashkey = md5(str);

	//std::string key = getAES(hash);
	//std::string key1 = getAES(key);
	//std::string oldHash= returnAES(key1);
	return hashkey;
}

GeneralDOG_API std::string getLicenseByKey(const std::string& key)
{
	return getAES(key);
}

GeneralDOG_API bool isSame(const std::string& DogData)
{
	std::string oldHash = returnAES(DogData);

	std::string cpu_id = get_cpu_id();
	if (cpu_id.empty()) {
		std::cout << "dog key is error" << std::endl;
		return false;
	}
	std::string salt = cfl_dog;
	std::string str = cpu_id + salt;
	std::string hash = md5(str);

	return hash == oldHash;
}
