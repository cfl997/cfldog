#pragma once
#include <string>

#ifdef WIN32
	#ifdef GeneralDOG_EXPORTS
		//#define GeneralDOG_API __declspec(dllexport)
	//#else
		//#define GeneralDOG_API __declspec(dllimport)
		#define GeneralDOG_API //¾²Ì¬¿â
	#else
		#define GeneralDOG_API //¾²Ì¬¿â
	#endif
#else// WIN32
	#define GeneralDOG_API
#endif // WIN32

#include "cflTime.hpp"

//#ifdef GeneralDOG_EXPORTS
GeneralDOG_API std::string generate_key();

GeneralDOG_API std::string getLicenseByKey(const std::string& key);

struct KeyTimeData
{
	KeyTimeType keyTimeType = KeyTimeType::KEYTIME_NULL;
	int keytimenum = 1;
	bool isAdd = true;
};
GeneralDOG_API std::string getLicenseByKey(const std::string& key, KeyTimeData keyTimeData);

GeneralDOG_API bool isSameLicense(const std::string& licenseKey);

//#else
//std::string generate_key();
//
//std::string getLicenseByKey(const std::string& key);
//
//bool isSameLicense(const std::string& DogData);
//#endif
